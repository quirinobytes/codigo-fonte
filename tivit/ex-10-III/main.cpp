#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
       int codigo;
       char *marca;
       char *tipo;
       char *modelo;
       double valor;
       struct Produto *next;
       }head,*tail;

void add(char*);
void show(struct Produto*);

int main(int argc, char *argv[])
{
head.next = NULL;
tail->next = &head;


add("3245PHILIPS:Radio MP3 Player:XII-32050:1300.23");
  
show(&head);
    
  system("PAUSE");	
  return 0;
}


void add(char *stream){
     int codigo;
     char strcodigo[5];
     memcpy(strcodigo,stream,4);
     strcodigo[4]='\0';
     codigo = atoi(strcodigo);

     tail->codigo = codigo;
     
     
     tail->next = (struct Produto*) malloc(sizeof(struct Produto));
     tail=tail->next;
     tail->next = NULL;
}
void show(struct Produto *s){
     while (s->next !=NULL){
           printf("Codigo: %i \n",s->codigo);
           printf("Marca: %s \n",s->marca);
           printf("Tipo: %s \n",s->tipo);
           printf("Modelo: %s \n",s->modelo);
           printf("Valor: %.2f\n",s->valor);
           s=s->next;
     }
}
     
