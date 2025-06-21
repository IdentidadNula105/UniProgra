#include <stdio.h>
#include <stdlib.h>
#include "is.h"

int IsDigito(char carac){
    if((carac>47 && carac<58) || carac==69 || carac==101) return 1;//numero, e, x
    return 0;
}

int IsFuncion(char *exp, int i){
    if(Isln(exp, i)){
        return 1;//Funcion ln
    } else if(Issen(exp, i) || Iscos(exp, i) || Istan(exp, i) || Iscot(exp, i) || Issec(exp, i) || Iscsc(exp, i)){
        return 2;//Funcion trigonometrica
    } else if(Isarcsen(exp, i) || Isarccos(exp, i) || Isarctan(exp, i) || Isarccot(exp, i) || Isarcsec(exp, i) || Isarccsc(exp, i)){
        return 3;//Funcion arcotrigonometrica
    } else {
        return 0;//No es funcion
    }
}

int Isln(char *exp, int i){
    if(exp[i]=='l' && exp[i+1]=='n') return 1;
    return 0;
}

int Issen(char* exp, int i){
    if(exp[i]=='s' && exp[i+1]=='e' && exp[i+2]=='n') return 1;
    return 0;
}

int Iscos(char* exp, int i){
    if(exp[i]=='c' && exp[i+1]=='o' && exp[i+2]=='s') return 1;
    return 0;
}

int Istan(char* exp, int i){
    if(exp[i]=='t' && exp[i+1]=='a' && exp[i+2]=='n') return 1;
    return 0;
}

int Iscot(char* exp, int i){
    if(exp[i]=='c' && exp[i+1]=='o' && exp[i+2]=='t') return 1;
    return 0;
}

int Issec(char* exp, int i){
    if(exp[i]=='s' && exp[i+1]=='e' && exp[i+2]=='c') return 1;
    return 0;
}

int Iscsc(char* exp, int i){
    if(exp[i]=='c' && exp[i+1]=='s' && exp[i+2]=='c') return 1;
    return 0;
}

int Isarcsen(char* exp, int i){
    if(exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='s' && exp[i+4]=='e' && exp[i+5]=='n') return 1;
    return 0;
}

int Isarccos(char* exp, int i){
    if(exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='c' && exp[i+4]=='o' && exp[i+5]=='s') return 1;
    return 0;
}

int Isarctan(char* exp, int i){
    if(exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='t' && exp[i+4]=='a' && exp[i+5]=='n') return 1;
    return 0;
}

int Isarccot(char* exp, int i){
    if(exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='c' && exp[i+4]=='o' && exp[i+5]=='t') return 1;
    return 0;
}

int Isarcsec(char* exp, int i){
    if(exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='s' && exp[i+4]=='e' && exp[i+5]=='c') return 1;
    return 0;
}

int Isarccsc(char* exp, int i){
    if(exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='c' && exp[i+4]=='s' && exp[i+5]=='c') return 1;
    return 0;
}