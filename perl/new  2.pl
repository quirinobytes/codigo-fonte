#!/usr/bin/env perl


use DBI;
use strict;
use warnings;
use Getopt::Long;
my($wordlist,$file,$ini,$fin,@lista,$arq,$i,@a);
$file=1;

sub banner {
    print '
    '.GREEN.'[+]'.RESET.' Cat - Quirinobytes

    '.BOLD BLUE.'[*]'.RESET.' Opcoes:

        -f | --file => nome do arquivo         [exemplo: arquivo.txt]

    '.BOLD BLUE.'[*]'.RESET.' Exemplo de uso:

        perl cat.pl -f file ordlist.txt -t 10';
    exit(1);
}

GetOptions( 'f|file=s'  => \$file) || die &banner;

open($arq,"<$file") || die($!);;
@lista = <$arq>;
print @lista;
 