#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

/*###  EXEMPLO DE LISTA ENCADEADA - SIMPLES ###*/


///#ESTRUTURA

typedef struct pessoa{
	struct pessoa * next;
	int idade;
	char * nome;
}cadastro;


///#FUNCAO PRINCIPAL
	
int main (int argc, char *argv[]){
	int resp;
	cadastro * ini_cadastro;
	cadastro * item_cadastro;
	 
	ini_cadastro = (cadastro *) malloc (sizeof(cadastro));

if (ini_cadastro == NULL ) 
	exit (1);
	item_cadastro = ini_cadastro;
	
	while (1){
	
	printf("\nDigite o nome:");
	scanf("%s",&item_cadastro->nome);
	
	printf ("\nDigite idade:");
	scanf("%d",&item_cadastro->idade);
	
	printf("\nDeseja digitar outro valor? 1-> SIM  |  0-> NAO");

	scanf("%d",&resp);
	
	
	if (resp == 1)
	{
			item_cadastro->next = (cadastro *) malloc (sizeof (cadastro));
			item_cadastro = item_cadastro->next;
	}
	else
		break;
	}
	printf("\n");
	item_cadastro->next = NULL;
	item_cadastro = ini_cadastro;
	
	while (item_cadastro->next != NULL)
	{
		printf("%s tem idade: %d \n", &item_cadastro->nome, item_cadastro->idade);
		item_cadastro = item_cadastro->next;
	}
	return 0;
		
}
