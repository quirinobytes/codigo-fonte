#include <cstdlib>
#include <iostream>


using namespace std;

void show(struct Produto *p);

struct Produto{
       int codigo;
       char marca[99];
       char modelo[999];
       double valor;
       Produto *next;
       }primeiro;

int main(int argc, char *argv[])
{
    char codigo[5];
    int icod, i1,i2;
    struct Produto *p;
    p=&primeiro;
    
    
    char *stream[] = {"0110SONY:V03-bfz:388.85","notebook"};
    stream[0] = "9988TOSHIBA:V03-megasuperblaster:2088.85";
    printf("Stream = %s\n",stream[0]);
    memcpy(codigo,stream[0],4);
    codigo[4]='\0';
    icod = atoi(codigo);
    p->codigo = icod;
    char *indice;
    indice = (char*) memchr(stream[0],':',strlen(stream[0]));
//    printf("%d", indice - stream[0] +1);
    i1 = indice - stream[0]+1;
    memcpy (p->marca,stream[0]+4,i1-5);
    

    
    char valor[99];
    indice = (char*) memchr(stream[0]+i1,':',strlen(stream[0])-i1);
    i2 = indice - stream[0]+1;
//    printf("%d", indice - stream[0]+1);
    memcpy(valor,stream[0]+i2,strlen(stream[0]) - i2 -1 );
    p->valor = atof(valor);
    
    memcpy(p->modelo, stream[0]+i1, i2-i1-1);

    p->next = (struct Produto*) malloc (sizeof(struct Produto));
    p=p->next;
    p->next=NULL;
    show(&primeiro);
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

void show(struct Produto *p){
     while (p->next != NULL){
           printf("Codigo: %d\n",p->codigo);
           printf("Marca: %s\n",p->marca);
           printf("Modelo: %s\n",p->modelo);
           printf("Valor: R$ %.2f\n",p->valor);
           p=p->next;
     }
}
           
