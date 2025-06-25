#include <stdio.h>
#include <stdlib.h>
#include "is.h"

int IsDigito(char carac){
    if((carac>47 && carac<58) || carac==101) return 1;//numero, e
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

int IsOperador(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='^') return 1;
    return 0;
}

int IsFuncionValida(char *exp){
    if(!exp) return 0;
    int indice=0, bandera=1, contPare1=0, contPare2=0, Opcons=0;
    while(bandera==1 && exp[indice]!='\0'){
        if(exp[indice]=='(') contPare1++;
        if(exp[indice]==')') contPare2++;
        if(IsOperador(exp[indice]) && Opcons==0) Opcons=1;
        else if(!IsOperador(exp[indice]) && Opcons==1) Opcons=0;
        else if(IsOperador(exp[indice]) && Opcons==1) bandera=0;
        indice++;
    }
    if(contPare1!=contPare2) bandera=0;
    return bandera;
}

int Iscero(char *exp, int i){
    int ind=0;
    for(ind=i; exp[ind]!='\0'; ind++);
    if(exp[0]=='0' && ind==1) return 1;
    return 0;
}

int Isuno(char *exp, int i){
    int ind=0;
    for(ind=i; exp[ind]!='\0'; ind++);
    if(exp[0]=='1' && ind==1) return 1;
    return 0;
}

int Ise(char *exp, int i){
    int ind=0;
    for(ind=i; exp[ind]!='\0'; ind++);
    if(exp[0]=='e' || exp[0]=='E' && ind==1) return 1;
    return 0;
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