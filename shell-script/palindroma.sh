#!/bin/bash 


if [ -f $1 ]; then

echo -e "Digite uma palavra na entrada, exemplo: \n ./$0 string"

fi

pos = ${#1}

for ((c=0; $c < ${#1} ; c++)) do 

	if [ ${1:$c:1} !=  ${1:$pos-$c-1:1} ]; then

		echo NAO EH
		exit   
	fi

done

echo A Palavra eh palindroma
