#include <stdio.h>
#include <stdlib.h>
#include "../libis/is.h"
#include "cadesp.h"

char* CrearSubcadena(char* exp, int* i){
    char* c;
    int cont;
    cont=0;
    if(IsFuncion(exp, *i)){
        if(IsFuncion(exp, *i)==1){
            c=(char*)malloc(3*sizeof(char));
            c[0]=exp[*i];
            c[1]=exp[*i+1];
            c[2]='\0';
        } else if(IsFuncion(exp, *i)==2){
            c=(char*)malloc(4*sizeof(char));
            c[0]=exp[*i];
            c[1]=exp[*i+1];
            c[2]=exp[*i+2];
            c[3]='\0';
        } else if(IsFuncion(exp, *i)==3){
            c=(char*)malloc(7*sizeof(char));
            c[0]=exp[*i];
            c[1]=exp[*i+1];
            c[2]=exp[*i+2];
            c[3]=exp[*i+3];
            c[4]=exp[*i+4];
            c[5]=exp[*i+5];
            c[6]='\0';
        }
    } else if(IsDigito(exp[*i])){
        cont=1;
        while(exp[*i+cont]!=',') cont++;
        c=(char*)malloc((cont+1)*sizeof(char));
        for(int j=0; j<cont; j++){
            c[j]=exp[*i+j];
        }//Unica vez donde se modifica ind
        *i=*i+cont-1;
        c[cont]='\0';
    } else {
        c=(char*)malloc(2*sizeof(char));
        c[0]=exp[*i];
        c[1]='\0';
    }
    return c;
}

int TamanoCadena(char* exp, int i){
    if(exp[i]=='\0') return 0;
    return 1+TamanoCadena(exp, i+1);
}

char* CrearChar(char c){
    char* s;
    s=(char*)malloc(2*sizeof(char));
    s[0]=c;
    s[1]='\0';
    return s;
}