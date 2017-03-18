#include <stdio.h>
#include <conio.h>


double fibo(double);



int main()
{
	
	int num;
	double result;
	
	printf("Digite o valor para fibonacci:");
	scanf ("%d",&num);
	
	result = fibo(num);
	
	printf("Resultado = %lf",result);
	
	getch();
	
}




double fibo(double v){
	
	if (v == 0)
	 return 1;
	else 
	 return v* fibo(v-1);
		
}
