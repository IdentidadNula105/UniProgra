#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Pila{
    char *pila;
    int tope;
}Pila;

Pila *InicPila(int n);
void Push(Pila *p, char ele);
char Pop(Pila *p);
char Top(Pila *p);
int Palindromo(Pila* p, char* c);

int main(){
    char *c;
    Pila* pila;
    int h;
    c=(char*)malloc((MAX+1)*sizeof(char));
    pila=InicPila(MAX);
    printf("\nIntroduzca su frase menor a 100 letras: ");
    scanf("%[^\n]", c);
    h=Palindromo(pila, c);
    
    if(!h){
        printf("No es palindroma");
    } else{
        printf("Es palindroma");
    }
    return 0;
}

Pila *InicPila(int n){
    Pila *p;
    p->pila=malloc(n*sizeof(char));
    p->tope=0;
    return p;
}
void Push(Pila *p, char ele){
    p->pila[p->tope]=ele;
    p->tope++;
}
char Pop(Pila *p){
    p->tope--;
    return p->pila[p->tope];
}
char Top(Pila *p){
    return p->pila[p->tope-1];
}

int Palindromo(Pila* p, char* c){
    int i=0,j=0;
    char h;
    
    while(c[i]!=0){
        Push(p, c[i]);
        i++;
    }
    while(j<i){
        while(Top(p)==32) h=Pop(p);
        while(c[j]==32) j++;
        if(c[j]!=Pop(p)) break;
        j++;
    }
    if(j==i) return 1;//La cadena es palindromo
    return 0;//La cadena no es palindromo
}