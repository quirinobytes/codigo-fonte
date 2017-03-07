#include <stdio.h>
#include <conio.h>





int main(){
	
	int vetor[10], pos = 0, valor;
	int c=0;
	double soma=0;
	
	do{
		printf ("Digite o valor para a posicao %d ou 0 para Sair.",pos+1);
		scanf ("%d",&valor);
		vetor[pos]= valor;
		pos++;
		
	}while ( valor != 0 );
	
	while(c < pos){
		printf ("Vetor[%d]=%d\n",c,vetor[c]);
		soma=soma+vetor[c];
		c++;
	}
	
	
	printf ("A Média é: %lf ",soma/(pos-1));
	
return 0;	
}
