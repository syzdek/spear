#!/usr/local/bin/perl -Tw

if (!(open(FILE, $ARGV[0])))
{
   printf("boo\n");
   exit 1;
};

close(FILE);
