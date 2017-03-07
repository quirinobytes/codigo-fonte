#!/usr/bin/env perl


use DBI;
use strict;
use warnings;
use Getopt::Long;
use Term::ANSIColor qw(:constants);
my($wordlist,$file,$ini,$fin,@lista,$arq,$i,@a,@filtrado,$palavra);
$file=1;
$palavra=1;

sub banner {
    print '
    '.GREEN.'[+]'.RESET.' Cat - Quirinobytes

    '.BOLD BLUE.'[*]'.RESET.' Opcoes:

        -f | --file => nome do arquivo         [exemplo: arquivo.txt]

    '.BOLD BLUE.'[*]'.RESET.' Exemplo de uso:

        perl cat.pl -f file ordlist.txt -t 10';
    exit(1);
}

GetOptions( 'f|file=s'  => \$file,
			'p|palavra=s' => \$palavra
) || die &banner;
&banner if (not defined($file));

open($arq,"<$file") || die &banner;
@lista = <$arq>;
@filtrado = grep { " " } @lista;
print @filtrado;
  