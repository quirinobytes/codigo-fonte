#!/usr/bin/env perl
 
use strict;
use warnings;
use threads;
use Net::FTP;
use Getopt::Long;
use threads::shared;
use Term::ANSIColor qw(:constants);

my($wordlist,$thr,$ini,$fin,@threads,$arq,$i,@a,$int);
our($user,$host,@aa);
my $stop :shared = 0;
$host = "";
$arq = "arquivo.txt";
$thr = 2;
$ini = 0;
$fin = $thr - 1;
$int = 1;

while(1){

    exit if $stop;

    @threads = ();

    for($i=$ini;$i<=$fin;$i++){
        push(@threads,$i);
    }

    foreach(@threads){
        $_ = threads->create(\&ftp);
    }

    foreach(@threads){
        $_->join();
    }

    $ini = $fin + 1;
    $fin = $fin + $thr;

}

sub ftp {
	
    if (threads->tid() = 1 ){
		while (1){
			$int++;
			printf $int;
		}
		}
}  
