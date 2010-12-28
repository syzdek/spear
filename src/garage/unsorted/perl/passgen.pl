#!/share/bin/perl -Tw
use strict;

my ($Password, $Crypt, $Salt);

# Generates a password
   $Password = rand 100000000;
   $Password = (split(/\./, $Password))[0];
   $Salt = rand 100;
   $Salt = (split(/\./, $Salt))[0];
   $Salt = crypt ($Password, $Salt);
   $Salt = substr($Salt, 2, 2);
   $Crypt = '{crypt}' . crypt($Password, $Salt);

print($Password, " ", $Crypt, "\n");
