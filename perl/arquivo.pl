#!/usr/bin/env perl
 
use strict;
use warnings;
use threads;
use Net::FTP;
use Getopt::Long;
use threads::shared;
use Term::ANSIColor qw(:constants);

sub banner {
    print '
    '.GREEN.'[+]'.RESET.' FTP Brute-force By MMxM

    '.BOLD BLUE.'[*]'.RESET.' Opcoes:

        -u | --user => nome do usuario         [exemplo: admin]
        -h | --host => Alvo            [exemplo: 127.0.0.1]
        -w | --wordlist => Lista de palavras    [exemplo: /tmp/wordlist.txt]
        -t | --threads => Numero de threads    [exemplo: 10]

    '.BOLD BLUE.'[*]'.RESET.' Exemplo de uso:

        perl ftp.pl -u admin -h 127.0.01 -w minha-wordlist.txt -t 10

';
    exit(1);
}

my($wordlist,$thr,$ini,$fin,@threads,$arq,$i,@a);
our($user,$host,@aa);

GetOptions(    'u|user=s'  => \$user,
        'h|host=s' => \$host,
        'w|wordlist=s' => \$wordlist,
        't|threads=i' => \$thr
) || die &banner;

&banner if (not defined($user)) || (not defined($host)) || (not defined($wordlist)) || (not defined($thr));
 

open($arq,"<$wordlist") || die($!);
@a = <$arq>;
print @a;