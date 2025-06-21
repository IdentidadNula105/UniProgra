#include <stdlib.h>
#include "../libarbolbinario/arbbin.h"
#include "../libpiladinamica/piladin.h"
#include "../libis/is.h"
#include "../libcadespecial/cadesp.h"
#include "derivsimb.h"

#define fundato ((char*)fun->dato)

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
char* cosl="cos";
char* tanl="tan";
char* cotl="cot";
char* secl="sec";
char* cscl="csc";

NodoArb* ConstruirArbolFuncion(char* s){
    int indice_exp=0;
    NodoArb *izq, *der, *nvo;
    NodoL* pila;
    CrearPila(&pila);
    while(s[indice_exp]){
        if(s[indice_exp]!=','){
            nvo=CrearNodoArb(NULL, NULL, CrearSubcadena(s, &indice_exp));
            if(s[indice_exp]=='+' || s[indice_exp]=='-' || s[indice_exp]=='*' || s[indice_exp]=='/' || s[indice_exp]=='^'){
                der=(NodoArb*)Pop(&pila);
                izq=(NodoArb*)Pop(&pila);
                nvo->der=der;
                nvo->izq=izq;
            } else if(IsFuncion(s, indice_exp)){
                izq=(NodoArb*)Pop(&pila);
                nvo->izq=izq;
                if(IsFuncion(s, indice_exp)==1){
                    indice_exp++;
                } else if(IsFuncion(s, indice_exp)==2){
                    indice_exp=indice_exp+2;
                } else if(IsFuncion(s, indice_exp)==3){
                    indice_exp=indice_exp+5;
                }
            }
            pila=Push(&pila, nvo);
        }
        indice_exp++;
    }
    return (NodoArb*)(Pop(&pila));
}

NodoArb** DerivarArbolsen(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(fun->izq, NULL, cosl);
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    return nvo;
}

NodoArb* DerivarArbolFuncion(NodoArb* fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb** nvo;
    if(fundato[0]=='x'){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=CrearNodoArb(NULL, NULL, CrearChar(uno));
    } else if(IsDigito(fundato[0])){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=CrearNodoArb(NULL, NULL, CrearChar(cero));
    } else if(fundato[0]=='+' || fundato[0]=='-'){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), DerivarArbolFuncion(fun->der), fun->dato);
    } else if(fundato[0]=='*'){
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(fun->izq, DerivarArbolFuncion(fun->der), fun->dato);
        nvo[1]=CrearNodoArb(fun->der, DerivarArbolFuncion(fun->izq), fun->dato);
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], CrearChar(sum));
    } else if(fundato[0]=='/'){
        nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
        nvo[5]=CrearNodoArb(fun->der, DerivarArbolFuncion(fun->izq), CrearChar(prod));
        nvo[4]=CrearNodoArb(fun->izq, DerivarArbolFuncion(fun->der), CrearChar(prod));
        nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(dif));
        nvo[2]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[1]=CrearNodoArb(fun->der, nvo[2], CrearChar(expo));
        nvo[0]=CrearNodoArb(nvo[3], nvo[1], fun->dato);
    } else if(fundato[0]=='^'){
        if(!IsDigito(((char*)(fun->izq)->dato)[0]) && IsDigito(((char*)(fun->der)->dato)[0])){
            nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
            nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(uno));
            nvo[3]=CrearNodoArb(fun->der, nvo[4], CrearChar(dif));
            nvo[2]=CrearNodoArb(fun->izq, nvo[3], CrearChar(expo));
            nvo[1]=CrearNodoArb(nvo[2], DerivarArbolFuncion(fun->izq), CrearChar(prod));
            nvo[0]=CrearNodoArb(fun->der, nvo[1], CrearChar(prod));
        } else if(IsDigito(((char*)(fun->izq)->dato)[0]) && !IsDigito(((char*)(fun->der)->dato)[0])){
            nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
            nvo[3]=CrearNodoArb(fun->izq, fun->der, CrearChar(expo));
            nvo[2]=CrearNodoArb(fun->izq, NULL, ln);
            nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(prod));
            nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->der), CrearChar(prod));
        } else if(!IsDigito(((char*)(fun->izq)->dato)[0]) && !IsDigito(((char*)(fun->der)->dato)[0])){
            if(((char*)(fun->der)->dato)[0]=='/' && IsDigito(((char*)((fun->der)->izq)->dato)[0]) && IsDigito(((char*)((fun->der)->der)->dato)[0])){
                nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
                nvo[5]=CrearNodoArb((fun->der)->der, (fun->der)->izq, CrearChar(dif));
                nvo[4]=CrearNodoArb(nvo[5], (fun->der)->der, CrearChar(divi));
                nvo[3]=CrearNodoArb(fun->izq, nvo[4], CrearChar(expo));
                nvo[2]=CrearNodoArb((fun->der)->der, nvo[3], CrearChar(prod));
                nvo[1]=CrearNodoArb((fun->der)->izq, DerivarArbolFuncion(fun->izq), CrearChar(prod));
                nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(divi));
            } else {
                nvo=(NodoArb**)malloc(10*sizeof(NodoArb*));
                nvo[9]=CrearNodoArb(NULL, NULL, CrearChar(uno));
                nvo[8]=CrearNodoArb(fun->der, nvo[9], CrearChar(dif));
                nvo[7]=CrearNodoArb(fun->izq, nvo[8], CrearChar(expo));
                nvo[6]=CrearNodoArb(fun->der, nvo[7], CrearChar(prod));
                nvo[5]=CrearNodoArb(nvo[6], DerivarArbolFuncion(fun->izq), CrearChar(prod));
                nvo[4]=CrearNodoArb(fun->izq, fun->der, CrearChar(expo));
                nvo[3]=CrearNodoArb(fun->izq, NULL, ln);
                nvo[2]=CrearNodoArb(nvo[4],nvo[3], CrearChar(prod));
                nvo[1]=CrearNodoArb(nvo[2], DerivarArbolFuncion(fun->der), CrearChar(prod));
                nvo[0]=CrearNodoArb(nvo[5], nvo[1], CrearChar(sum));
            }
        }
    } else if(Issen(fundato, 0)){
        nvo=DerivarArbolsen(fun);
    } else if(Iscos(fundato, 0)){
        nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
        nvo[3]=CrearNodoArb(fun->izq, NULL, senl);
        nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), CrearChar(prod));
        nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
        nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    } else if(fundato[0]=='t' && fundato[1]=='a' && fundato[2]=='n'){
        nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
        nvo[3]=CrearNodoArb(fun->izq, NULL, secl);
        nvo[2]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(expo));
        nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    } else if(fundato[0]=='c' && fundato[1]=='o' && fundato[2]=='t'){
        nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
        nvo[5]=CrearNodoArb(fun->izq, NULL, cscl);
        nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(expo));
        nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), CrearChar(prod));
        nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
        nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    } else if(fundato[0]=='s' && fundato[1]=='e' && fundato[2]=='c'){
        nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
        nvo[3]=CrearNodoArb(fun->izq, NULL, secl);
        nvo[2]=CrearNodoArb(fun->izq, NULL, tanl);
        nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(prod));
        nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    } else if(fundato[0]=='c' && fundato[1]=='s' && fundato[2]=='c'){
        nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
        nvo[5]=CrearNodoArb(fun->izq, NULL, cscl);
        nvo[4]=CrearNodoArb(fun->izq, NULL, cotl);
        nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(prod));
        nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), CrearChar(prod));
        nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
        nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    } else if(fundato[0]=='a' && fundato[1]=='r' && fundato[2]=='c' && fundato[3]=='s' && fundato[4]=='e' && fundato[5]=='n'){
        nvo=(NodoArb**)malloc(7*sizeof(NodoArb*));
        nvo[6]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[5]=CrearNodoArb(fun->izq, nvo[6], CrearChar(expo));
        nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(uno));
        nvo[3]=CrearNodoArb(nvo[4], nvo[5], CrearChar(dif));
        nvo[2]=CrearNodoArb(nvo[4], nvo[6], CrearChar(divi));
        nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(expo));
        nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], CrearChar(divi));
    } else if(fundato[0]=='a' && fundato[1]=='r' && fundato[2]=='c' && fundato[3]=='c' && fundato[4]=='o' && fundato[5]=='s'){
        nvo=(NodoArb**)malloc(9*sizeof(NodoArb*));
        nvo[8]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[7]=CrearNodoArb(fun->izq, nvo[8], CrearChar(expo));
        nvo[6]=CrearNodoArb(NULL, NULL, CrearChar(uno));
        nvo[5]=CrearNodoArb(nvo[6], nvo[7], CrearChar(dif));
        nvo[4]=CrearNodoArb(nvo[6], nvo[8], CrearChar(divi));
        nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(expo));
        nvo[2]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[3], CrearChar(divi));
        nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
        nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    } else if(fundato[0]=='a' && fundato[1]=='r' && fundato[2]=='c' && fundato[3]=='t' && fundato[4]=='a' && fundato[5]=='n'){
        nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
        nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[3]=CrearNodoArb(fun->izq, nvo[4], CrearChar(expo));
        nvo[2]=CrearNodoArb(NULL, NULL, CrearChar(uno));
        nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(sum));
        nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], CrearChar(divi));
    } else if(fundato[0]=='a' && fundato[1]=='r' && fundato[2]=='c' && fundato[3]=='c' && fundato[4]=='o' && fundato[5]=='t'){
        nvo=(NodoArb**)malloc(7*sizeof(NodoArb*));
        nvo[6]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[5]=CrearNodoArb(fun->izq, nvo[6], CrearChar(expo));
        nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(uno));
        nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(sum));
        nvo[2]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[3], CrearChar(divi));
        nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
        nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    } else if(fundato[0]=='a' && fundato[1]=='r' && fundato[2]=='c' && fundato[3]=='s' && fundato[4]=='e' && fundato[5]=='c'){
        nvo=(NodoArb**)malloc(8*sizeof(NodoArb*));
        nvo[7]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[6]=CrearNodoArb(fun->izq, nvo[7], CrearChar(expo));
        nvo[5]=CrearNodoArb(NULL, NULL, CrearChar(uno));
        nvo[4]=CrearNodoArb(nvo[6], nvo[5], CrearChar(dif));
        nvo[3]=CrearNodoArb(nvo[5], nvo[7], CrearChar(divi));
        nvo[2]=CrearNodoArb(nvo[4], nvo[3], CrearChar(expo));
        nvo[1]=CrearNodoArb(fun->izq, nvo[2], CrearChar(prod));
        nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], CrearChar(divi));
    } else if(fundato[0]=='a' && fundato[1]=='r' && fundato[2]=='c' && fundato[3]=='c' && fundato[4]=='s' && fundato[5]=='c'){
        nvo=(NodoArb**)malloc(10*sizeof(NodoArb*));
        nvo[9]=CrearNodoArb(NULL, NULL, CrearChar(dos));
        nvo[8]=CrearNodoArb(fun->izq, nvo[9], CrearChar(expo));
        nvo[7]=CrearNodoArb(NULL, NULL, CrearChar(uno));
        nvo[6]=CrearNodoArb(nvo[8], nvo[7], CrearChar(dif));
        nvo[5]=CrearNodoArb(nvo[7], nvo[9], CrearChar(divi));
        nvo[4]=CrearNodoArb(nvo[6], nvo[5], CrearChar(expo));
        nvo[3]=CrearNodoArb(fun->izq, nvo[4], CrearChar(prod));
        nvo[2]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[3], CrearChar(divi));
        nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
        nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    } else if(fundato[0]=='l' && fundato[1]=='n'){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), fun->izq, CrearChar(divi));
    }
    //free(fun);
    return nvo[0];
}

void Convertir_Arbol_Lista(NodoArb* arb, NodoL** p){
    int i=0;
    if(!arb) return;
    Convertir_Arbol_Lista(arb->izq, p);
    Convertir_Arbol_Lista(arb->der, p);
    while(((char*)arb->dato)[i]!='\0'){
        *p=Push(p, &((char*)arb->dato)[i]);
        i++;
    }
    
    *p=Push(p, CrearChar(coma));
}

NodoArb *SimplificarRaiz(NodoArb *fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb **nvo; 
    if(fundato[0]=='*' && (((char*)(fun->izq)->dato)[0]=='1' || ((char*)(fun->der)->dato)[0]=='1')){
        //1*u=u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        if(((char*)(fun->izq)->dato)[0]=='1')
            *nvo=fun->der;
        else if(((char*)(fun->der)->dato)[0]=='1')
            *nvo=fun->izq;
    } else if((fundato[0]=='*' || fundato[0]=='/') && (((char*)(fun->izq)->dato)[0]=='0' || ((char*)(fun->der)->dato)[0]=='0')){
        //0*u=0, 0/u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=CrearNodoArb(NULL, NULL, CrearChar(cero));
        //Nota: el caso de u/0 entra en este if, sin embargo, esto jamas ocurrira a menos que el usuario ingrese una expresion similar
    } else if(fundato[0]=='+' && (((char*)(fun->izq)->dato)[0]=='0' || ((char*)(fun->der)->dato)[0]=='0')){
        //0+u=u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        if(((char*)(fun->izq)->dato)[0]=='0')
            *nvo=fun->der;
        else if(((char*)(fun->der)->dato)[0]=='0')
            *nvo=fun->izq;
    } else if(fundato[0]=='-' && ((char*)(fun->der)->dato)[0]=='0'){
        //u-0=u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=fun->izq;
    } else if(fundato[0]=='/' && (((char*)(fun->izq)->dato)[0]=='/' || ((char*)(fun->der)->dato)[0]=='/')){
        if(((char*)(fun->izq)->dato)[0]=='/' && ((char*)(fun->der)->dato)[0]!='/'){
            //(a/b)/c=a/b*c
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der, CrearChar(prod));
            nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], CrearChar(divi));
        } else if(((char*)(fun->izq)->dato)[0]!='/' && ((char*)(fun->der)->dato)[0]=='/'){
            //a/(b/c)=a*c/b
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=CrearNodoArb(fun->izq, fun->izq->izq, CrearChar(prod));
            nvo[0]=CrearNodoArb(nvo[1], fun->der->izq, CrearChar(divi));
        } else if(((char*)(fun->izq)->dato)[0]=='/' && ((char*)(fun->der)->dato)[0]=='/'){
            //(a/b)/(c/d)=a*d/b*c
            nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
            nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->der, CrearChar(prod));
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der->izq, CrearChar(prod));
            nvo[0]=CrearNodoArb(nvo[2], nvo[1], CrearChar(divi));
        }
    } else {
        //No se cumple ninguna condicion para simplificar o fun es un numero/funcion
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=CrearNodoArb(fun->izq, fun->der, fun->dato);
    }
    (*nvo)->der=SimplificarRaiz((*nvo)->der);
    (*nvo)->izq=SimplificarRaiz((*nvo)->izq);
    //free(fun);
    return *nvo;
}

NodoArb *SimplificarArbolFuncion(NodoArb *fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb *nvo=CrearNodoArb(SimplificarArbolFuncion(fun->izq), SimplificarArbolFuncion(fun->der), fun->dato);
    nvo=SimplificarRaiz(nvo);
    return nvo;
}