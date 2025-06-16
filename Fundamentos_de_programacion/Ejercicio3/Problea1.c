/*
Determinar si una palabara es palindromo o no
*/
#include <stdio.h>
#define TAM_PALABRA 50

int main (){
    int tam, izq, der;
    char palabra[TAM_PALABRA+1];

    scanf("%s", & palabra[0]);
    tam=0;
    while(palabra[tam]!='\0'){
        tam=tam+1;
    }

    izq=0;
    der=tam-1;
    while(izq<tam && der>=0 && palabra[izq] == palabra[der]){
        izq=izq+1;
        der=der-1;
    }
    if(izq==tam){
        printf("SI");
    }else{
        printf("NO");
    }
    return 0;
}