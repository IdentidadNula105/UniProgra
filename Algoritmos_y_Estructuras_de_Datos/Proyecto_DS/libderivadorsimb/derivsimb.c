#include <stdio.h>
#include <stdlib.h>
#include "../libarbolbinario/arbbin.h"
#include "../libpiladinamica/piladin.h"
#include "../libis/is.h"
#include "../libcadespecial/cadesp.h"
#include "derivsimb.h"

#define fundato ((char*)fun->dato)
#define funizqdato ((char*)fun->izq->dato)
#define funderdato ((char*)fun->der->dato)
#define funderderdato ((char*)fun->der->der->dato)
#define funderizqdato ((char*)fun->der->izq->dato)
#define funizqizqdato ((char*)fun->izq->izq->dato)
#define funizqderdato ((char*)fun->izq->der->dato)

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

NodoArb* DerivArb_x(NodoArb* fun){
    NodoArb* nvo=CrearNodoArb(NULL, NULL, CrearChar(uno));
    return nvo;
}

NodoArb* DerivArb_Numero(NodoArb* fun){
    NodoArb* nvo= CrearNodoArb(NULL, NULL, CrearChar(cero));
    return nvo;
}

NodoArb* DerivArb_Producto(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
    nvo[2]=CrearNodoArb(fun->izq, DerivarArbolFuncion(fun->der), fun->dato);
    nvo[1]=CrearNodoArb(fun->der, DerivarArbolFuncion(fun->izq), fun->dato);
    nvo[0]=CrearNodoArb(nvo[2], nvo[1], CrearChar(sum));
    return *nvo;
}

NodoArb* DerivArb_Cociente(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb(fun->der, DerivarArbolFuncion(fun->izq), CrearChar(prod));
    nvo[4]=CrearNodoArb(fun->izq, DerivarArbolFuncion(fun->der), CrearChar(prod));
    nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(dif));
    nvo[2]=CrearNodoArb(NULL, NULL, CrearChar(dos));
    nvo[1]=CrearNodoArb(fun->der, nvo[2], CrearChar(expo));
    nvo[0]=CrearNodoArb(nvo[3], nvo[1], fun->dato);
    return *nvo;
}

NodoArb* DerivArb_Fun_C(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
    nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(uno));
    nvo[3]=CrearNodoArb(fun->der, nvo[4], CrearChar(dif));
    nvo[2]=CrearNodoArb(fun->izq, nvo[3], CrearChar(expo));
    nvo[1]=CrearNodoArb(nvo[2], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    nvo[0]=CrearNodoArb(fun->der, nvo[1], CrearChar(prod));
    return *nvo;
}

NodoArb* DerivArb_C_Fun(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, fun->der, CrearChar(expo));
    nvo[2]=CrearNodoArb(fun->izq, NULL, ln);
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(prod));
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->der), CrearChar(prod));
    return *nvo;
}

NodoArb* DerivArb_Fun_Fun(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(10*sizeof(NodoArb*));
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
    return *nvo;
}

NodoArb* DerivArb_ArSimplificarArbolFuncion(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb((fun->der)->der, (fun->der)->izq, CrearChar(dif));
    nvo[4]=CrearNodoArb(nvo[5], (fun->der)->der, CrearChar(divi));
    nvo[3]=CrearNodoArb(fun->izq, nvo[4], CrearChar(expo));
    nvo[2]=CrearNodoArb((fun->der)->der, nvo[3], CrearChar(prod));
    nvo[1]=CrearNodoArb((fun->der)->izq, DerivarArbolFuncion(fun->izq), CrearChar(prod));
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(divi));
    return *nvo;
}

NodoArb* DerivArb_sen(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(fun->izq, NULL, cosl);
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    return *nvo;
}

NodoArb* DerivArb_cos(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, NULL, senl);
    nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    return *nvo;
}

NodoArb* DerivArb_tan(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, NULL, secl);
    nvo[2]=CrearNodoArb(NULL, NULL, CrearChar(dos));
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(expo));
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    return *nvo;
}

NodoArb* DerivArb_cot(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb(fun->izq, NULL, cscl);
    nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(dos));
    nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(expo));
    nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    return *nvo;
}

NodoArb* DerivArb_sec(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, NULL, secl);
    nvo[2]=CrearNodoArb(fun->izq, NULL, tanl);
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(prod));
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    return *nvo;
}

NodoArb* DerivArb_csc(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb(fun->izq, NULL, cscl);
    nvo[4]=CrearNodoArb(fun->izq, NULL, cotl);
    nvo[3]=CrearNodoArb(nvo[5], nvo[4], CrearChar(prod));
    nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), CrearChar(prod));
    nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], CrearChar(dif));
    return *nvo;
}

NodoArb* DerivArb_arcsen(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(7*sizeof(NodoArb*));
    nvo[6]=CrearNodoArb(NULL, NULL, CrearChar(dos));
    nvo[5]=CrearNodoArb(fun->izq, nvo[6], CrearChar(expo));
    nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(uno));
    nvo[3]=CrearNodoArb(nvo[4], nvo[5], CrearChar(dif));
    nvo[2]=CrearNodoArb(nvo[4], nvo[6], CrearChar(divi));
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(expo));
    nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], CrearChar(divi));
    return *nvo;
}

NodoArb* DerivArb_arccos(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
    nvo[0]=CrearNodoArb(nvo[1], DerivArb_arcsen(fun), CrearChar(dif));
    return *nvo;
}

NodoArb* DerivArb_arctan(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
    nvo[4]=CrearNodoArb(NULL, NULL, CrearChar(dos));
    nvo[3]=CrearNodoArb(fun->izq, nvo[4], CrearChar(expo));
    nvo[2]=CrearNodoArb(NULL, NULL, CrearChar(uno));
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], CrearChar(sum));
    nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], CrearChar(divi));
    return *nvo;
}

NodoArb* DerivArb_arccot(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
    nvo[0]=CrearNodoArb(nvo[1], DerivArb_arctan(fun), CrearChar(dif));
    return *nvo;
}

NodoArb* DerivArb_arcsec(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(8*sizeof(NodoArb*));
    nvo[7]=CrearNodoArb(NULL, NULL, CrearChar(dos));
    nvo[6]=CrearNodoArb(fun->izq, nvo[7], CrearChar(expo));
    nvo[5]=CrearNodoArb(NULL, NULL, CrearChar(uno));
    nvo[4]=CrearNodoArb(nvo[6], nvo[5], CrearChar(dif));
    nvo[3]=CrearNodoArb(nvo[5], nvo[7], CrearChar(divi));
    nvo[2]=CrearNodoArb(nvo[4], nvo[3], CrearChar(expo));
    nvo[1]=CrearNodoArb(fun->izq, nvo[2], CrearChar(prod));
    nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], CrearChar(divi));
    return *nvo;
}

NodoArb* DerivArb_arccsc(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(cero));
    nvo[0]=CrearNodoArb(nvo[1], DerivArb_arcsec(fun), CrearChar(dif));
    return *nvo;
}

NodoArb* DerivArb_ln(NodoArb* fun){
    NodoArb* nvo=CrearNodoArb(DerivarArbolFuncion(fun->izq), fun->izq, CrearChar(divi));
    return nvo;
}

NodoArb* DerivarArbolFuncion(NodoArb* fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb* nvo;
    if(fundato[0]=='x'){
        nvo=DerivArb_x(fun);
    } else if(IsDigito(fundato[0])){
        nvo=DerivArb_Numero(fun);
    } else if(fundato[0]=='+' || fundato[0]=='-'){
        nvo=CrearNodoArb(DerivarArbolFuncion(fun->izq), DerivarArbolFuncion(fun->der), fun->dato);
    } else if(fundato[0]=='*'){
        nvo=DerivArb_Producto(fun);
    } else if(fundato[0]=='/'){
        nvo=DerivArb_Cociente(fun);
    } else if(fundato[0]=='^'){
        if(!IsDigito(funizqdato[0]) && IsDigito(funderdato[0])){
            //f(x)^c
            nvo=DerivArb_Fun_C(fun);
        } else if(IsDigito(funizqdato[0]) && !IsDigito(funderdato[0])){
            //c^f(x)
            nvo=DerivArb_C_Fun(fun);
        } else if(!IsDigito(funizqdato[0]) && !IsDigito(funderdato[0])){
            if(funderdato[0]=='/' && IsDigito(funderizqdato[0]) && IsDigito(funderderdato[0])){
                //f(x)^(c1/c2)
                nvo=DerivArb_ArSimplificarArbolFuncion(fun);
            } else {
                //f(x)^g(x)
                nvo=DerivArb_Fun_Fun(fun);
            }
        }
    } else if(Issen(fundato, 0)){
        nvo=DerivArb_sen(fun);
    } else if(Iscos(fundato, 0)){
        nvo=DerivArb_cos(fun);
    } else if(Istan(fundato, 0)){
        nvo=DerivArb_tan(fun);
    } else if(Iscot(fundato, 0)){
        nvo=DerivArb_arccot(fun);
    } else if(Issec(fundato, 0)){
        nvo=DerivArb_sec(fun);
    } else if(Iscsc(fundato, 0)){
        nvo=DerivArb_csc(fun);
    } else if(Isarcsen(fundato, 0)){
        nvo=DerivArb_arcsen(fun);
    } else if(Isarccos(fundato, 0)){
        nvo=DerivArb_arccos(fun);
    } else if(Isarctan(fundato, 0)){
        nvo=DerivArb_arctan(fun);
    } else if(Isarccot(fundato, 0)){
        nvo=DerivArb_arccot(fun);
    } else if(Isarcsec(fundato, 0)){
        nvo=DerivArb_arcsec(fun);
    } else if(Isarccsc(fundato, 0)){
        nvo=DerivArb_arccsc(fun);
    } else if(Isln(fundato, 0)){
        nvo=DerivArb_ln(fun);
    }
    //free(fun);
    return nvo;
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


NodoArb *SimplificarArbolFuncion(NodoArb *fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb **nvo;
    fun->der=SimplificarArbolFuncion(fun->der);
    fun->izq=SimplificarArbolFuncion(fun->izq);
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    *nvo=fun;
    if(fundato[0]=='+'){
        if(CompararArbol(fun->izq, fun->der)){
            //u+u=2*u
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(dos));
            nvo[0]=CrearNodoArb(nvo[1], fun->der, CrearChar(prod));
        } else if(Iscero(funderdato, 0) || Iscero(funizqdato, 0)){
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            if(Iscero(funderdato, 0))*nvo=fun->izq;//u+0=u
            else if(Iscero(funizqdato, 0)) *nvo=fun->der;//0+u=u
        }
    } else if (fundato[0]=='-'){
        if(CompararArbol(fun->izq, fun->der)){
            //u-u=0
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            nvo[0]=CrearNodoArb(NULL, NULL, CrearChar(cero));
        } else if(Iscero(funderdato, 0)){
            //u-0=u
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            *nvo=fun->izq;
        } else if(funderdato[0]=='-'){
            //u-(v-z)=u-v+z
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            nvo[0]=CrearNodoArb(fun->der->izq, fun->der->der, CrearChar(sum));
        }
    } else if (fundato[0]=='*'){
        if(Isuno(funizqdato, 0) || Isuno(funderdato, 0)){
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            if(Isuno(funizqdato, 0)) 
            *nvo=fun->der;//1*u=u
            else if(Isuno(funderdato, 0))
            *nvo=fun->izq;//u*1=u
        } else if(Iscero(funderdato, 0) || Iscero(funizqdato, 0)){
            // u*0=0*u=0
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            *nvo=CrearNodoArb(NULL, NULL, CrearChar(cero));
        } else if(CompararArbol(fun->izq, fun->der)){
            //u*u=u^2
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=CrearNodoArb(NULL, NULL, CrearChar(dos));
            nvo[0]=CrearNodoArb(fun->izq, nvo[1], CrearChar(expo));
        }
    } else if (fundato[0]=='/'){
        if(CompararArbol(fun->izq, fun->der)){
            //u/u=1
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            *nvo=CrearNodoArb(NULL, NULL, CrearChar(uno));
        } else if(Iscero(funizqdato, 0)){
            //0/u=1
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            *nvo=CrearNodoArb(NULL, NULL, CrearChar(cero));
        }else if(funizqdato[0]=='/' && funderdato[0]!='/'){
            //(a/b)/c=a/b*c
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der, CrearChar(prod));
            nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], CrearChar(divi));
        } else if(funizqdato[0]!='/' && funderdato[0]=='/'){
            //a/(b/c)=a*c/b
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=CrearNodoArb(fun->izq, fun->izq->izq, CrearChar(prod));
            nvo[0]=CrearNodoArb(nvo[1], fun->der->izq, CrearChar(divi));
        } else if(funizqdato[0]=='/' && funderdato[0]=='/'){
            //(a/b)/(c/d)=a*d/b*c
            nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
            nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->der, CrearChar(prod));
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der->izq, CrearChar(prod));
            nvo[0]=CrearNodoArb(nvo[2], nvo[1], CrearChar(divi));
        }
    } else if (fundato[0]=='^'){
        if(Isuno(funderdato, 0)){
            //u^1=u
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            *nvo=fun->izq;
        } else if(Iscero(funderdato, 0)){
            //u^0=1
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            *nvo=CrearNodoArb(NULL, NULL, CrearChar(uno));
        } else if(funizqdato[0]=='^'){
            //u^v^z=(u^v)^z=u^(v*z)
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der, CrearChar(prod));
            nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], CrearChar(expo));
        }
    }
    (*nvo)->der=SimplificarArbolFuncion((*nvo)->der);
    (*nvo)->izq=SimplificarArbolFuncion((*nvo)->izq);
    //free(fun);
    return *nvo;
}