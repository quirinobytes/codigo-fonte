#include <cstdlib>
#include <iostream>

using namespace std;


struct Pessoa{
       char nome[50];
       struct Pessoa *next;
       }head;

void show(struct Pessoa*);

int main(int argc, char *argv[])
{
    struct Pessoa *p;
    char palavra[50];
    
    p=&head;
    printf("Digite exit quando desejar finalizar\n");
    scanf("%s",palavra);
    
    
    while (strcmp(palavra,"exit")){
          memcpy(p->nome,palavra,sizeof(palavra));
          p->next = (struct Pessoa*) malloc(sizeof(Pessoa));
          scanf("%s",palavra);
          p=p->next;
    }
    p->next = NULL;
    show(&head);
    system("PAUSE");
    return EXIT_SUCCESS;
}

void show(struct Pessoa *s){
     while(s->next != NULL){
           printf("Nome: %s\n",s->nome);
           s=s->next;
     }
}
