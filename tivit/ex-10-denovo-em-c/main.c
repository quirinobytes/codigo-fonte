#include <stdio.h>
#include <stdlib.h>

struct Produto {
       int codigo;
       char marca[99];
       char tipo[20];
       char modelo[999];
       double valor;
       struct Produto *next;
}head,*tail;

void add(char*);
void show(struct Produto*);

int main(int argc, char *argv[])
{
int c; 
    
tail=&head;
tail->next = &head;

//printf("%s",argv[1]);
//printf("%d",argc);

for (c=1;c<argc;c++){
    add(argv[c]);
}

//add("3245PHILIPS:Radio_MP3_Player:XII-32050:1300.23");
//add("2525SHARP:TV 24':LCD-2012:8900.98");
  
if (argc>1) 
  show(&head);
    
  system("PAUSE");	
  return 0;
}


void add(char *stream){
     int codigo;
     char *str1,*str2,*str3,valor[30];
     int indice1,indice2,indice3;
     char strcodigo[5];
     memcpy(strcodigo,stream,4);
     strcodigo[4]='\0';
     codigo = atoi(strcodigo);
     str1 = (char*) memchr(stream,':',strlen(stream));
     indice1 = str1 - stream;

//   printf("indice %d\n",indice1);
//   printf("str2 %s\n",str2);

     str2 = (char*) memchr(stream+indice1+1,':',strlen(stream)-indice1);     
     indice2 = str2 - stream;     
//   printf("indice2 %d\n",indice2);

     str3 = (char *) memchr(stream+indice2+1,':',strlen(stream)-indice2);
     indice3 = str3 - stream;
//   printf("indice3 %d\n",indice3);

     memcpy(valor,str3+1,strlen(stream) - indice3);
     tail->valor = atof(valor);

                   
     memcpy(tail->tipo,str1+1,indice2-indice1 -1);
     memcpy(tail->modelo,str2+1,indice3-indice2 -1);
     memcpy(tail->marca,stream+4,indice1-4);
     tail->codigo = codigo;
     tail->next = (struct Produto*) malloc(sizeof(struct Produto));
     tail=tail->next;
     tail->next = NULL;
}
void show(struct Produto *s){
     
     while (s->next!=NULL){
           printf("Codigo: %i \n",s->codigo);
           printf("Marca: %s \n",s->marca);
           printf("Tipo: %s \n",s->tipo);
           printf("Modelo: %s \n",s->modelo);
           printf("Valor: %.2f\n",s->valor);
           printf("\n");
           s=s->next;

     }
}
     
