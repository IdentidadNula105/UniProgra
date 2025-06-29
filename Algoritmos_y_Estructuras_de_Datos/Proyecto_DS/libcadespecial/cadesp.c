#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../libis/is.h"
#include "cadesp.h"

char coma=',';
char cero='0';
char uno='1';
char dos='2';
char sum='+';
char dif='-';
char prod='*';
char divi='/';
char expo='^';
char* ln="ln";
char* senl="sen";
char* csl="cos";
char* tnl="tan";
char* cotl="cot";
char* secl="sec";
char* cscl="csc";

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

int Convertir_Cad_Numero(char *numero){
    int numeroint, indice;
    for(indice=numeroint=0; numero[indice]!='\0'; indice++)
        numeroint=(numero[indice]-'0')+numeroint*10;
    return numeroint;
}

char *Convertir_Numero_Cad(int numero){
    int tamnumero, temp=0;
    for(tamnumero=0; (int)(numero/pow(10, tamnumero+1)); tamnumero++);
    tamnumero++;
    char* numerocad=(char*)malloc((tamnumero+1)*sizeof(char));
    for(int i=tamnumero-1, temp=numero; i>=0; i--){
        numerocad[i]='0'+(int)(temp%10);
        temp=(temp-temp%10)/10;
    }
    numerocad[tamnumero]='\0';
    return numerocad;
}

char* CrearChar(char c){
    char* s;
    s=(char*)malloc(2*sizeof(char));
    s[0]=c;
    s[1]='\0';
    return s;
}

char *Cadcoma(){
    char *cad=CrearChar(coma);
    return cad;
}

char *Cadcero(){
    char *cad=CrearChar(cero);
    return cad;
}

char *Caduno(){
    char *cad=CrearChar(uno);
    return cad;
}

char *Caddos(){
    char *cad=CrearChar(dos);
    return cad;
}

char *Cadsum(){
    char *cad=CrearChar(sum);
    return cad;
}

char *Caddif(){
    char *cad=CrearChar(dif);
    return cad;
}

char *Cadprod(){
    char *cad=CrearChar(prod);
    return cad;
}

char *Caddivi(){
    char *cad=CrearChar(divi);
    return cad;
}

char *Cadexpo(){
    char *cad=CrearChar(expo);
    return cad;
}

char *Cadln(){
    return ln;
}

char *Cadsen(){
    return senl;
}

char *Cadcos(){
    return csl;
}

char *Cadtan(){
    return tnl;
}

char *Cadcot(){
    return cotl;
}

char *Cadsec(){
    return secl;
}

char *Cadcsc(){
    return cscl;
}