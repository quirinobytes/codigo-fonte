#include <stdio.h>
#include <stdlib.h>


long double fib(long double num);



int main(){
long double number;

	printf("Digite um numero para calcular o fibonacci=");
	scanf("%Lf",&number);

printf("Resposta= ");
printf("###  %.2Lf  ####\n\n\n",fib(number));


}












long double fib(long double num){

	if (num == 0){
		return 1;
	}
	else{
		return num*fib(num-1);
	}
}

