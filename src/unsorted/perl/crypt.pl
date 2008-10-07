#!/usr/local/bin/perl -Tw
use strict;
#
# This script displays a password in crypt
# or validates a password and crypt
#
# David Syzdek
#

my ($password, $crypt, $salt);

if (@ARGV == 0) {
   print STDERR ("\nUsage: crypt.pl <password> [ -c <crypt> | -s <salt> ]\n\n");
   exit;
  } elsif (@ARGV == 3) {
   if ($ARGV[1] eq '-c') {
      $crypt = $ARGV[2];
     } elsif ($ARGV[1] eq '-s') {
      $salt = $ARGV[2];
     } else {
      print STDERR ("\nUsage: crypt.pl <password> [ -c <crypt> | -s <salt> ]\n\n");
      exit
   };
  } elsif (@ARGV != 1) {
   print STDERR ("\nUsage: crypt.pl <password> [ -c <crypt> | -s <salt> ]\n\n");
   exit
};
$password = $ARGV[0];
if (!defined($crypt)) {
   if (!defined($salt)) {
      $salt = rand 100;
      ($salt) = split (/\./, $salt);
      $salt = crypt ($password, $salt);
      $salt = substr ($salt, 2, 2);
   };
   $crypt = crypt($password, $salt);
   print ('Crypt: ', $crypt, "\n");
  } else {
   $salt = substr ($crypt, 0, 2);
   if ($crypt ne crypt($password, $salt)) {
      print("incorrect password\n");
      exit 1;
     } else {
      print("correct password\n");
      exit 0;
   };
};

