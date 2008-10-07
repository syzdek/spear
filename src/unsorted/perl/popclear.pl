#!/share/bin/perl -Tw
use strict;
use Net::LDAP;
use Net::POP3;
$|++;


# Configs
   my $LdapServer	= 'localhost';
   my $LdapPort		= 13891;
   my $PopPort		= '110';
   my $BindDn		= 'cn=Directory Manager';
   my $BindPw		= 'password';

# Variables
   my ($Mesg, $Entry, $MesgCount, $Buffer);
   my ($Salt, $Password, $Crypt, $CryptPasword);
   my $Error = 0;

# Checks usage
   if (@ARGV != 1) {
      print STDERR ("\n\tUsage: popclear.pl <address>\n\n");
      exit 1;
     } elsif ($ARGV[0] !~ /^[-\w._]+@[-\w._]+$/) {
      print STDERR ("\n\tUsage: popclear.pl <address>\n\n");
      exit 1;
   };
   my ($User, $Domain) = split(/@/, $ARGV[0]);
   my $Address = $ARGV[0];

# Verifies the staff knows what they are doing
   print("\n\n\e[31mAre you sure you want to delete the entire \n");
   print("mail spool for \"", $Address, "\"?\n");
   print("Enter [yes/no]:\e[0m ");
   chomp($Buffer = <STDIN>);
   while ( ($Buffer ne "yes") && ($Buffer ne "no") ) {
      print("\n\e[31mI'm sorry.  That was an invalid option.\n");
      print("Are you sure you want to delete the entire \n");
      print("mail spool for \"", $Address, "\"?\n");
      print("Enter [yes/no]:\e[0m ");
      chomp($Buffer = <STDIN>);
   };
   if ($Buffer eq "no") {
      print("\nbye\n");
      exit 0;
   };
   print("\n\e[2J\n\e[1;1H");

# Generates a password
   $Password = time();
   $Password = substr($Password, 3, 8);
   $Salt = rand 100;
   $Salt = (split(/\./, $Salt))[0];
   $Salt = crypt ($Password, $Salt);
   $Salt = substr($Salt, 2, 2);
   $Crypt = '{crypt}' . crypt($Password, $Salt);

# Opens LDAP connection
   print("Connecting to LDAP: ");
   my $LDAP = Net::LDAP->new($LdapServer, 'port' => $LdapPort) or die "unable to connec to ldap";
   $Mesg = $LDAP->bind($BindDn, 'password' => $BindPw);
   if ($Mesg->code() != 0) {
      print($Mesg->error(), "\n\n");
      exit $Mesg->code();
     } else {
      print("success\n");
   };

# Looks for User
   print("Searching LDAP for user: ");
   my $Filter = '(uid=' . $User . ')';
   my $BaseDn = 'ou=people,o=email,o=' . $Domain . ',o=acsalaska.net';
   $Mesg = $LDAP->search(
      'base'	=> $BaseDn,
      'scope'	=> 'sub',
      'filter'	=> $Filter,
      'attrs'	=> ['mailhost', 'userpassword']
   );
   if ($Mesg->code() != 0) {
      print STDERR ($Mesg->error(), "\n\n");
      $LDAP->unbind();
      exit $Mesg->code();
     } elsif ($Mesg->count() != 1) {
      print STDERR ("User not found in LDAP\n\n");
      $LDAP->unbind();
      exit 1;
     } else {
      print("success\n");
   };

# Gets Mailhost and Password
   $Entry = $Mesg->entry(0);
   my $CryptPassword = $Entry->get_value('userpassword');
   my $PopServer = $Entry->get_value('mailhost');
   my $UserBase = $Entry->dn();

# Resets password to a known password
   print("Changing POP password: ");
   $Mesg = $LDAP->modify($UserBase, replace => { userpassword => $Crypt } );
   if ($Mesg->code() != 0) {
      print STDERR ($Mesg->error(), "\n\n");
      $LDAP->unbind();
      exit $Mesg->code();
     } else {
      print("success\n");
   };

# Allows password to replicate
   print("Sleeping for 5 seconds: ");
   sleep(5);
   print("success\n");

# Connects to POP server
   print("Connecting to POP server: ");
   my $POP;
   if ($POP = Net::POP3->new($PopServer, 'Port' => $PopPort)) {
      print("success\n");
     } else {
      print STDERR ("F A I L E D\n\n");
      $Mesg = $LDAP->modify($UserBase, replace => { userpassword => $CryptPassword } ); 
      $LDAP->unbind();
      exit 1;
   };
   

# Logs into POP server
   print("Authenticating POP user: ");
   if (defined $POP->login($Address, $Password)) {
      print("success\n");
     } else {
      print("F A I L E D\n\n");
      $Mesg = $LDAP->modify($UserBase, replace => { userpassword => $CryptPassword } );
      print("Resetting POP password: ");
      if ($Mesg->code() == 0) {
         print("success\n\n");
        } else {
         print("F A I L E D\n\n");
      };
      $LDAP->unbind();
      exit 1;
   };

      
# Counting Messages
   print("Counting Messages: ");
   if ($MesgCount = $POP->list()) {
      print("success\n");
     } else {
      print("F A I L E D\n\n");
      print("Resetting POP password: ");
      $Mesg = $LDAP->modify($UserBase, replace => { userpassword => $CryptPassword } );
      if ($Mesg->code() == 0) {
         print("success\n\n");
        } else {
         print("F A I L E D\n\n");
      };
      $LDAP->unbind();
      exit 1;
   };  

# Deletes Messages
   if (scalar(keys(%$MesgCount)) == 0) {
      print("\nNO MESSAGES TO DELETE\n\n");
     } else {
      print("Deleting Message: ");
      my $Count = 0;
      foreach my $Temp (keys(%$MesgCount)) {
         $Count = $Count + 1;
         print("\e[8;19H ", $Count, "/", scalar(keys(%$MesgCount)));
         $POP->delete($Temp);
      };
      print("\n");
   };

# Disconnects from POP server
   #$POP->reset;
   $POP->quit();
   
# Changes password back
   print("Resetting POP password: ");
   $Mesg = $LDAP->modify($UserBase, replace => { userpassword => $CryptPassword } );
   if ($Mesg->code() == 0) {
      print("success\n\n");
      $LDAP->unbind();
      exit 0;
     } else {
      print("F A I L E D\n\n");
      $LDAP->unbind();
      exit 1
   };

