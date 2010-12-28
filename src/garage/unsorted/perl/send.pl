#!/usr/local/bin/perl

use Net::SMTP;

if (!($smtp = Net::SMTP->new('smt.acsalaska.net', 'Hello' => 'test', 'Timeout' => 60 )))
{
    printf stderr ("unable to connect to server\n");
};
