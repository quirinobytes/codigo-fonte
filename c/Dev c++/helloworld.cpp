#include <stdio.h>
#include <conio.h>

double fib(double);

int main()
{

int num=10;
double resposta;



printf("Digite o valor que deseja saber o fibonati",num);
scanf("%i",&num);

resposta = fib(num);
printf("O fibonati de %d eh = %lf",num,resposta);

return 0;

}



double fib(double i){
	
if (i == 0)	
	return 1;
else
    return fib(i-1) * i;
    
}
