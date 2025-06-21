#include <stdio.h>
#include <stdlib.h>
#include "../libpiladinamica/piladin.h"
#include "../libis/is.h"
#include "../libcadespecial/cadesp.h"
#include "notainfpost.h"
char coma1=',';
char cero1='0';
int ind_exp=0;

int CompararOp(char op1, char op2){
    char arr[2];
    arr[0]=op1;
    arr[1]=op2;
    for(int i=0; i<2; i++){
        if(arr[i]=='N'){
            //Los operadores neutros hacen referencia a numeros o funciones, los cuales no necesitan parentesis
            arr[i]=4;
        } else if(arr[i]=='+'|| arr[i]=='-'){
            arr[i]=1;
        } else if(arr[i]=='*' || arr[i]=='/'){
            arr[i]=2;
        } else if(arr[i]=='^'){
            arr[i]=3;
        }
    }
    if(arr[0]>arr[1] || arr[0]==arr[1]){
        return 1;//op1 es mayor que op2 o son iguales
    } else if(arr[0]<arr[1]){
        return -1;//op1 es menor que op2
    }
}

void ConvCad(NodoL* exp, char* rec, int tam){
    if(exp->sig==NULL){
        rec[0]=*(char*)exp->dato;
        rec[tam]='\0';
        return;
    }else{
        ConvCad(exp->sig, rec, tam);
        rec[NumeroNL(exp)-1]=*(char*)exp->dato;
    }
}

char* Convertir_Lista_Cadena(NodoL* expL){
    char* expcad;
    int tamL;
    tamL=NumeroNL(expL);
    expcad=(char*)malloc((tamL+1)*sizeof(char));
    ConvCad(expL, expcad, tamL);
    return expcad;
}

NodoL* PostFijo(char* exp){
    NodoL* pilop;
    NodoL* expfn;
    int copind_exp=0;
    CrearPila(&pilop);
    CrearPila(&expfn);//No es una pila, pero permite inicializarlo correctamente con NULL
    while(exp[ind_exp]){
        if(exp[ind_exp]=='('){
            ind_exp++;
            expfn=ConcatenarListInvertida(expfn, PostFijo(exp));//Agrega los elementos de la expfn del () de forma invertida
        } else if(exp[ind_exp]==')'){
            break;
        } else if(!IsDigito(exp[ind_exp])){
            if(exp[ind_exp]=='x'){
                expfn=CrearNodoL(expfn, &exp[ind_exp]);
                expfn=CrearNodoL(expfn, &coma1);
            } else if(IsFuncion(exp, ind_exp)){
                copind_exp=ind_exp;
                if(IsFuncion(exp, ind_exp)==1){
                    ind_exp=ind_exp+3;
                } else if(IsFuncion(exp, ind_exp)==2){
                    ind_exp=ind_exp+4;
                } else if(IsFuncion(exp, ind_exp)==3){
                    ind_exp=ind_exp+7;
                }
                expfn=ConcatenarListInvertida(expfn, PostFijo(exp));
                while(exp[copind_exp]!='('){
                    expfn=CrearNodoL(expfn, &exp[copind_exp]);
                    copind_exp++;
                } 
                expfn=CrearNodoL(expfn, &coma1);
            } else if(exp[ind_exp]=='+' || exp[ind_exp]=='-' || exp[ind_exp]=='*' || exp[ind_exp]=='/' || exp[ind_exp]=='^'){
                if(exp[ind_exp]=='-' && (ind_exp-1<0 || exp[ind_exp-1]=='(')){
                    expfn=CrearNodoL(expfn, &cero1);
                    expfn=CrearNodoL(expfn, &coma1);
                }
                while(!IsEmpty(pilop) && CompararOp(*(char*)Top(pilop), exp[ind_exp])==1){
                expfn=CrearNodoL(expfn, Pop(&pilop));
                expfn=CrearNodoL(expfn, &coma1);
                }
                pilop=Push(&pilop, &exp[ind_exp]);
            } else if(exp[ind_exp]=='.'){
                expfn=CrearNodoL(expfn, &exp[ind_exp]);
            }
        } else if(IsDigito(exp[ind_exp])){
            expfn=CrearNodoL(expfn, &exp[ind_exp]);
            if(!IsDigito(exp[ind_exp+1]) && exp[ind_exp+1]!='.') expfn=CrearNodoL(expfn, &coma1);
        }
        ind_exp++;
    }
    while(pilop){
        expfn=CrearNodoL(expfn, Pop(&pilop));
        expfn=CrearNodoL(expfn, &coma1);
    } 
    return expfn;
}

NodoL* Infija(char* exp){
    NodoL* p1;
    Expifj* out, *el1, *el2;
    int tamt=0;
    int ind_expa=0;
    CrearPila(&p1);
    while(exp[ind_expa]!='\0'){
        if(exp[ind_expa]!=','){
            out=(Expifj*)malloc(sizeof(Expifj));
            if(IsDigito(exp[ind_expa]) || exp[ind_expa]=='x'){
                out->exp=CrearSubcadena(exp, &ind_expa);
                out->op='N';
            } else if(IsFuncion(exp, ind_expa)){
                el1=(Expifj*)Pop(&p1);//Argumento de la funcion
                tamt=TamanoCadena(el1->exp, 0)+3;
                if(IsFuncion(exp, ind_expa)==1){
                    tamt=tamt+2;
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    out->exp[0]='l';
                    out->exp[1]='n';
                    out->exp[2]='(';
                    for(int i=3, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    ind_expa=ind_expa+1;
                } else if(IsFuncion(exp, ind_expa)==2){
                    //Trigonometrica
                    tamt=tamt+3;
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    out->exp[0]=exp[ind_expa];
                    out->exp[1]=exp[ind_expa+1];
                    out->exp[2]=exp[ind_expa+2];
                    out->exp[3]='(';
                    for(int i=4, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    ind_expa=ind_expa+2;
                } else if(IsFuncion(exp, ind_expa)==3){
                    //arc trigonometrica
                    tamt=tamt+6;
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    out->exp[0]=exp[ind_expa];
                    out->exp[1]=exp[ind_expa+1];
                    out->exp[2]=exp[ind_expa+2];
                    out->exp[3]=exp[ind_expa+3];
                    out->exp[4]=exp[ind_expa+4];
                    out->exp[5]=exp[ind_expa+5];
                    out->exp[6]='(';
                    for(int i=7, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    ind_expa=ind_expa+5;
                }
                out->exp[tamt-2]=')';
                out->exp[tamt-1]='\0';
                out->op='N';
            } else {
                //Operador
                el2=(Expifj*)Pop(&p1);//Operando derecho
                el1=(Expifj*)Pop(&p1);//Operando izquierdo
                tamt=TamanoCadena(el1->exp, 0)+TamanoCadena(el2->exp, 0)+2;
                if((CompararOp(el1->op, exp[ind_expa])==1 && CompararOp(el2->op, exp[ind_expa])==-1) || (exp[ind_expa]=='-' && (el2->op=='+' || el2->op=='-')) || (exp[ind_expa]=='/' && el1->op=='N' && el2->op!='N')){
                    //Cuando el operador de entrada es mayor que el de ele2 o sean iguales a '-'
                    out->exp=(char*)malloc((tamt+2)*sizeof(char));
                    for(int i=0; el1->exp[i]!='\0'; i++) out->exp[i]=el1->exp[i];
                    out->exp[TamanoCadena(el1->exp, 0)]=exp[ind_expa];
                    out->exp[TamanoCadena(el1->exp, 0)+1]='(';
                    for(int i=TamanoCadena(el1->exp, 0)+2, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt]=')';
                    out->exp[tamt+1]='\0';
                } else if((CompararOp(el1->op, exp[ind_expa])==-1 && CompararOp(el2->op, exp[ind_expa])==-1) || (exp[ind_expa]=='/' && el1->op!='N' && el2->op!='N')){
                    //Los operadores de el1 y el2 son menores al de la entrada
                    out->exp=(char*)malloc((tamt+4)*sizeof(char));
                    out->exp[0]='(';
                    for(int i=1, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    out->exp[TamanoCadena(el1->exp, 0)+1]=')';
                    out->exp[TamanoCadena(el1->exp, 0)+2]=exp[ind_expa];
                    out->exp[TamanoCadena(el1->exp, 0)+3]='(';
                    for(int i=TamanoCadena(el1->exp, 0)+4, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt+2]=')';
                    out->exp[tamt+3]='\0';
                } else if((CompararOp(el1->op, exp[ind_expa])==1 && CompararOp(el2->op, exp[ind_expa])==1) || (exp[ind_expa]=='/' && el1->op=='N' && el2->op=='N')){
                    //Cuando el1 y el2 son numeros o funciones (trigo, log, arc)
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    for(int i=0; el1->exp[i]!='\0'; i++) out->exp[i]=el1->exp[i];
                    out->exp[TamanoCadena(el1->exp, 0)]=exp[ind_expa];
                    for(int i=TamanoCadena(el1->exp, 0)+1, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt-1]='\0';
                } else if((CompararOp(el1->op, exp[ind_expa])==-1 && CompararOp(el2->op, exp[ind_expa])==1) || (exp[ind_expa]=='/' && el1->op!='N' && el2->op=='N')){
                    //Cuando el operador de entrada es mas grande que el del el1
                    out->exp=(char*)malloc((tamt+2)*sizeof(char));
                    out->exp[0]='(';
                    for(int i=1, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    out->exp[TamanoCadena(el1->exp, 0)+1]=')';
                    out->exp[TamanoCadena(el1->exp, 0)+2]=exp[ind_expa];
                    for(int i=TamanoCadena(el1->exp, 0)+3, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt+1]='\0';
                }
                out->op=exp[ind_expa];
            }
            p1=Push(&p1, out);
        }
        ind_expa++;
    }
    return p1;
}