#!/opt/local/bin/perl -Tw

# +-=-=-=-=-=-+
# |           |
# |  Headers  |
# |           |
# +-=-=-=-=-=-+

# Load needed Modules
use			5.002;	# minimum Perl version
use Net::FTP		1.00;	# Perl module for FTP client operations
use strict		1.00;	# enforces good scripting habits
use Getopt::Std		1.00;	# parses commandline options
use File::Copy		2.00;	# handles local copies

$Getopt::Std::STANDARD_HELP_VERSION = 1;

$|++;			# Disables Line buffering

our $PROGRAM_NAME	= 'ftpcp.pl';
our $VERSION		= '0.01';
our $DESCRIPTION	= 'utility to provide scp like usability via FTP';
our $AUTHOR		= 'David Syzdek <david.syzdek@acsalaska.net>';
our $PACKAGE_NAME	= 'acs-utils';

# regular expressions used within this script
our $regex_file	= '[-/_\.\w\d]+';
our $regex_host	= '[-\w\d\.]+';
our $regex_user	= '[-_\w\d\.]+';
our $regex_pass	= '[!-~]+';
our $regex_arg	= "(($regex_user@){0,1}$regex_host:){0,1}$regex_file";

# commandline options
our $opt_a	= 0;		# (bool) ASCII mode
our $opt_b	= 0;		# (bool) BIN mode
our $opt_B	= 10240;	# (int) block size
our $opt_d	= 0;		# (int) debug level
our $opt_p	= 21;		# (int) port
our $opt_P	= 0;		# (bool) passive mode
our $opt_t	= 300;		# (int) timeout
our $opt_v	= 0;		# (bool) verbose mode
our $opt_w	= '';		# (string) password
our $opt_W	= 0;		# (bool) prompt for password

our $opt_file1;			# (string) orginal file 
our $opt_file2;			# (string) new file


# +-=-=-=-=-=-=-=+
# |              |
# |  Prototypes  |
# |              |
# +-=-=-=-=-=-=-=+

sub cmdline_opts();	# parses commandline options and detaints values
sub ftp();		# sends/recieves file via FTP
sub usage();		# displays script usage info
sub version();		# displays script version info


# +-=-=-=-=-=-=-+
# |             |
# |  Functions  |
# |             |
# +-=-=-=-=-=-=-+

# parses commandline options and detaints values
sub cmdline_opts() {

   # declares local vars
   my $key;

   # checks for long args
   for $key (@ARGV) {
      if ($key =~ /^--help$/) {
         usage();
         return(1);
      } elsif ($key =~ /^--version$/) {
         version();
         return(1);
      };
   };

   # parses args
   if (! getopts('abB:d:p:Pt:vw:')) {
      usage();
      return(1);
   };

   # checks for remaining args
   if (@ARGV != 2) {
      usage();
      return(1);
   };

   # detaints data
   if ($opt_B =~ /^([\d]+)$/) {
      $opt_B = $1;
     } else {
      printf("%s: invalid characters in option -B\n", $PROGRAM_NAME);
      usage();
      return(1);
   };
   if ($opt_d =~ /^([\d]+)$/) {
      $opt_d = $1;
     } else {
      printf("%s: invalid characters in option -d\n", $PROGRAM_NAME);
      usage();
      return(1);
   };
   if ($opt_p =~ /^([\d]+)$/) {
      $opt_p = $1;
     } else {
      printf("%s: invalid characters in option -p\n", $PROGRAM_NAME);
      usage();
      return(1);
   };
   if ($opt_t =~ /^([\d]+)$/) {
      $opt_t = $1;
     } else {
      printf("%s: invalid characters in option -t\n", $PROGRAM_NAME);
      usage();
      return(1);
   };
   if ($opt_w =~ /^($regex_pass)$/) {
      $opt_w = $1;
     } else {
      printf("%s: invalid characters in option -w\n", $PROGRAM_NAME);
      usage();
      return(1);
   };
   if ($ARGV[0] =~ /^($regex_arg)$/) {
      $opt_file1 = $1;
     } else {
      printf("%s: invalid characters in file1\n", $PROGRAM_NAME);
      usage();
      return(1);
   };
   if ($ARGV[1] =~ /^($regex_arg)$/) {
      $opt_file2 = $1;
     } else {
      printf("%s: invalid characters in file2\n", $PROGRAM_NAME);
      usage();
      return(1);
   };
   
   # ends function
   return(0);
};


# sends/recieves file via FTP
sub ftp() {

   # declares local vars
   my $ftp;
   my $lfile;
   my $rfile;
   my $host;
   my $user;
   my $sending;
   my %opts;

   # sets vars
   $sending = 0;
   $user = '';
   $host = '';

   # checks for one local file
   if (($opt_file1 !~ /^$regex_file$/) && ($opt_file2 !~ /^$regex_file$/)) {
      printf("%s: one file must be local\n", $PROGRAM_NAME);
      return(1);
   };

   # parses opt_file1
   if ($opt_file1 =~ /^($regex_file)$/) {
      $lfile = $opt_file1;
      $sending = 1;
   } else {
      ($user, $host) = split(/@/, $opt_file1);
      if ($user eq $opt_file1) {
         $host = $user;
         $user = '';
      };
      ($host, $rfile) = split(/:/, $host);
      if ($host eq $opt_file1) {
         $rfile = $host;
         $host = '';
      };
   };

   # parses opt_file2
   if ($opt_file2 =~ /^($regex_file)$/) {
      $lfile = $opt_file2;
   } else {
      ($user, $host) = split(/@/, $opt_file2);
      if ($user eq $opt_file2) {
         $host = $user;
         $user = '';
      };
      ($host, $rfile) = split(/:/, $host);
      if ($host eq $opt_file2) {
         $rfile = $host;
         $host = '';
      };
   };

   # sets local options
   $opts{'BlockSize'}	= $opt_B;
   $opts{'Port'}	= $opt_p;
   $opts{'Timeout'}	= $opt_t;
   $opts{'Debug'}	= $opt_d;
   $opts{'Passive'}	= $opt_P;

   # connects to host
   if (!($ftp = Net::FTP->new($host, %opts))) {
      printf("%s: unable to connect to server\n", $PROGRAM_NAME);
      return(1);
   };

   # logs into host
   if ($user ne '') {
      if (!($ftp->login($user, $opt_w))) {
         printf("%s: unable to login to remote server\n", $PROGRAM_NAME);
         $ftp->quit();
         return(1);
      };
     } else {
      if (!($ftp->login())) {
         printf("%s: unable to login to remote server\n", $PROGRAM_NAME);
         $ftp->quit();
         return(1);
      };
   };

   # sets transfer modes
   if ($opt_a) {
      $ftp->ascii();
   };
   if ($opt_b) {
      $ftp->binary();
   };
   if ($opt_v) {
      $ftp->hash(*STDOUT, 1024);
   };

   # uploads file
   if ($sending) {
      if (!($ftp->put($lfile, $rfile))) {
         printf("%s: unable to upload file\n", $PROGRAM_NAME);
         $ftp->quit();
         return(1);
      };
   } else {
      if (!($ftp->get($rfile, $lfile))) {
         printf("%s: unable to download file\n", $PROGRAM_NAME);
         $ftp->quit();
         return(1);
      };
   };

   # disconnects from server
   $ftp->quit();

   # ends function
   return(0);
};


# displays script usage info
sub usage() {
   printf("Usage: %s [options] [[user@]host1:]file1 [[user@]host2:]file2\n", $PROGRAM_NAME);
   printf("      -a                transfer files in ASCII mode\n");
   printf("      -b                transfer files in BINARY mode\n");
   printf("      -B size           transfer block size [%i]\n", $opt_B);
   printf("      -d level          debug level [%i]\n", $opt_d);
   printf("      -p port           remote port [%i]\n", $opt_p);
   printf("      -P                passive transfer mode\n");
   printf("      -t sec            network timeout [%i]\n", $opt_t);
   printf("      -v                verbose mode\n");
   printf("      -w pass           ftp password\n");
#   printf("      -W                prompt for password\n");
   printf("      --help            print this help and exit\n");
   printf("      --version         print version number and exit\n");
   printf("\n");
   printf("Report bugs to %s.\n", $AUTHOR);
};


# displays script version info
sub version() {
   printf("%s (%s) %s\n", $PROGRAM_NAME, $PACKAGE_NAME, $VERSION);
   printf("Written by David M. Syzdek.\n");
   printf("\n");
   printf("Copyright 2006 (c) Alaska Communications Systems Group \n");
   printf("This is free software; see the source for copying conditions.  There is NO\n");
   printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
};

# +-=-=-=-=-=-=-=-=-+
# |                 |
# |  Main  Section  |
# |                 |
# +-=-=-=-=-=-=-=-=-+
sub main() {

   # parses commandline args
   if (cmdline_opts()) {
      return(1);
   };

   # verifies  file1 and file2 do not match
   if ($opt_file1 eq $opt_file2) {
      printf("%s: %s and %s are identical (not copied).\n", $PROGRAM_NAME, $opt_file1, $opt_file2);
      return(1);
   };

   # checks if both are local files
   if (($opt_file1 =~ /^$regex_file$/) && ($opt_file2 =~ /^$regex_file$/)) {
      if (! copy($opt_file1, $opt_file2)) {
         printf("%s: unable to copy file\n", $PROGRAM_NAME);
         return(1);
      };
      return(0);
   };

   # copies file
   if (ftp()) {
      return(1);
   };

   # ends function
   return(0);
};
exit(main);

# end of script
