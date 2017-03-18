#include <cstdlib>
#include <iostream>

using namespace std;


struct Pessoa{
       char nome[50];
       Pessoa *next;
       }head;

void mostra(struct Pessoa *s);

int main(int argc, char *argv[]){
    char palavra[50];
    Pessoa *p;
    p=&head;
    printf("Digite exit quando desejar finalizar\n");
    scanf("%s",palavra);
    
    while (strcmp(palavra,"exit")){
          memcpy(p->nome,palavra,sizeof(palavra));
          scanf("%s",&palavra);
          p->next = (struct Pessoa*) malloc(sizeof(Pessoa));
          p=p->next;
    }
    p->next = NULL;    
    mostra(&head);
    system("PAUSE");
    return EXIT_SUCCESS;
}

void mostra(struct Pessoa *s){
     while (s->next != NULL){
           printf("Nome: %s\n",s->nome);
           s=s->next;
     }
}
