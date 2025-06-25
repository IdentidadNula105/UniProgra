#include <stdio.h>
#include <stdlib.h>
#include "../libpiladinamica/piladin.h"
#include "../libarbolbinario/arbbin.h"
#include "../libis/is.h"
#include "../libcadespecial/cadesp.h"
#include "../libnotainfpost/notainfpost.h"
#include "derivarbfun.h"
/*
Nota: cuando se construye el arbol, el argumento de funciones trigo y ln, se coloca
como subarbol izquierdo, siendo el derecho NULL.
*/
#define fundato ((char*)fun->dato)
#define funizqdato ((char*)fun->izq->dato)
#define funderdato ((char*)fun->der->dato)
#define funderderdato ((char*)fun->der->der->dato)
#define funderizqdato ((char*)fun->der->izq->dato)
#define funizqizqdato ((char*)fun->izq->izq->dato)
#define funizqderdato ((char*)fun->izq->der->dato)

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
    NodoArb* nvo=CrearNodoArb(NULL, NULL, Caduno());
    return nvo;
}

NodoArb* DerivArb_Numero(NodoArb* fun){
    NodoArb* nvo= CrearNodoArb(NULL, NULL, Cadcero());
    return nvo;
}

NodoArb* DerivArb_Producto(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
    nvo[2]=CrearNodoArb(fun->izq, DerivarArbolFuncion(fun->der), fun->dato);
    nvo[1]=CrearNodoArb(fun->der, DerivarArbolFuncion(fun->izq), fun->dato);
    nvo[0]=CrearNodoArb(nvo[2], nvo[1], Cadsum());
    return *nvo;
}

NodoArb* DerivArb_Cociente(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb(fun->der, DerivarArbolFuncion(fun->izq), Cadprod());
    nvo[4]=CrearNodoArb(fun->izq, DerivarArbolFuncion(fun->der), Cadprod());
    nvo[3]=CrearNodoArb(nvo[5], nvo[4], Caddif());
    nvo[2]=CrearNodoArb(NULL, NULL, Caddos());
    nvo[1]=CrearNodoArb(fun->der, nvo[2], Cadexpo());
    nvo[0]=CrearNodoArb(nvo[3], nvo[1], fun->dato);
    return *nvo;
}

NodoArb* DerivArb_Fun_C(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
    nvo[4]=CrearNodoArb(NULL, NULL, Caduno());
    nvo[3]=CrearNodoArb(fun->der, nvo[4], Caddif());
    nvo[2]=CrearNodoArb(fun->izq, nvo[3], Cadexpo());
    nvo[1]=CrearNodoArb(nvo[2], DerivarArbolFuncion(fun->izq), Cadprod());
    nvo[0]=CrearNodoArb(fun->der, nvo[1], Cadprod());
    return *nvo;
}

NodoArb* DerivArb_C_Fun(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, fun->der, Cadexpo());
    nvo[2]=CrearNodoArb(fun->izq, NULL, Cadln());
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], Cadprod());
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->der), Cadprod());
    return *nvo;
}

NodoArb* DerivArb_Fun_Fun(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(10*sizeof(NodoArb*));
    nvo[9]=CrearNodoArb(NULL, NULL, Caduno());
    nvo[8]=CrearNodoArb(fun->der, nvo[9], Caddif());
    nvo[7]=CrearNodoArb(fun->izq, nvo[8], Cadexpo());
    nvo[6]=CrearNodoArb(fun->der, nvo[7], Cadprod());
    nvo[5]=CrearNodoArb(nvo[6], DerivarArbolFuncion(fun->izq), Cadprod());
    nvo[4]=CrearNodoArb(fun->izq, fun->der, Cadexpo());
    nvo[3]=CrearNodoArb(fun->izq, NULL, Cadln());
    nvo[2]=CrearNodoArb(nvo[4],nvo[3], Cadprod());
    nvo[1]=CrearNodoArb(nvo[2], DerivarArbolFuncion(fun->der), Cadprod());
    nvo[0]=CrearNodoArb(nvo[5], nvo[1], Cadsum());
    return *nvo;
}

NodoArb* DerivArb_Raiz(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb((fun->der)->der, (fun->der)->izq, Caddif());
    nvo[4]=CrearNodoArb(nvo[5], (fun->der)->der, Caddivi());
    nvo[3]=CrearNodoArb(fun->izq, nvo[4], Cadexpo());
    nvo[2]=CrearNodoArb((fun->der)->der, nvo[3], Cadprod());
    nvo[1]=CrearNodoArb((fun->der)->izq, DerivarArbolFuncion(fun->izq), Cadprod());
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], Caddivi());
    return *nvo;
}

NodoArb* DerivArb_sen(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(fun->izq, NULL, Cadcos());
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), Cadprod());
    return *nvo;
}

NodoArb* DerivArb_cos(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, NULL, Cadsen());
    nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), Cadprod());
    nvo[1]=CrearNodoArb(NULL, NULL, Cadcero());
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], Caddif());
    return *nvo;
}

NodoArb* DerivArb_tan(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, NULL, Cadsec());
    nvo[2]=CrearNodoArb(NULL, NULL, Caddos());
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], Cadexpo());
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), Cadprod());
    return *nvo;
}

NodoArb* DerivArb_cot(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb(fun->izq, NULL, Cadcsc());
    nvo[4]=CrearNodoArb(NULL, NULL, Caddos());
    nvo[3]=CrearNodoArb(nvo[5], nvo[4], Cadexpo());
    nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), Cadprod());
    nvo[1]=CrearNodoArb(NULL, NULL, Cadcero());
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], Caddif());
    return *nvo;
}

NodoArb* DerivArb_sec(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
    nvo[3]=CrearNodoArb(fun->izq, NULL, Cadsec());
    nvo[2]=CrearNodoArb(fun->izq, NULL, Cadtan());
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], Cadprod());
    nvo[0]=CrearNodoArb(nvo[1], DerivarArbolFuncion(fun->izq), Cadprod());
    return *nvo;
}

NodoArb* DerivArb_csc(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
    nvo[5]=CrearNodoArb(fun->izq, NULL, Cadcsc());
    nvo[4]=CrearNodoArb(fun->izq, NULL, Cadcot());
    nvo[3]=CrearNodoArb(nvo[5], nvo[4], Cadprod());
    nvo[2]=CrearNodoArb(nvo[3], DerivarArbolFuncion(fun->izq), Cadprod());
    nvo[1]=CrearNodoArb(NULL, NULL, Cadcero());
    nvo[0]=CrearNodoArb(nvo[1], nvo[2], Caddif());
    return *nvo;
}

NodoArb* DerivArb_arcsen(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(7*sizeof(NodoArb*));
    nvo[6]=CrearNodoArb(NULL, NULL, Caddos());
    nvo[5]=CrearNodoArb(fun->izq, nvo[6], Cadexpo());
    nvo[4]=CrearNodoArb(NULL, NULL, Caduno());
    nvo[3]=CrearNodoArb(nvo[4], nvo[5], Caddif());
    nvo[2]=CrearNodoArb(nvo[4], nvo[6], Caddivi());
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], Cadexpo());
    nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], Caddivi());
    return *nvo;
}

NodoArb* DerivArb_arccos(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(NULL, NULL, Cadcero());
    nvo[0]=CrearNodoArb(nvo[1], DerivArb_arcsen(fun), Caddif());
    return *nvo;
}

NodoArb* DerivArb_arctan(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
    nvo[4]=CrearNodoArb(NULL, NULL, Caddos());
    nvo[3]=CrearNodoArb(fun->izq, nvo[4], Cadexpo());
    nvo[2]=CrearNodoArb(NULL, NULL, Caduno());
    nvo[1]=CrearNodoArb(nvo[3], nvo[2], Cadsum());
    nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], Caddivi());
    return *nvo;
}

NodoArb* DerivArb_arccot(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(NULL, NULL, Cadcero());
    nvo[0]=CrearNodoArb(nvo[1], DerivArb_arctan(fun), Caddif());
    return *nvo;
}

NodoArb* DerivArb_arcsec(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(8*sizeof(NodoArb*));
    nvo[7]=CrearNodoArb(NULL, NULL, Caddos());
    nvo[6]=CrearNodoArb(fun->izq, nvo[7], Cadexpo());
    nvo[5]=CrearNodoArb(NULL, NULL, Caduno());
    nvo[4]=CrearNodoArb(nvo[6], nvo[5], Caddif());
    nvo[3]=CrearNodoArb(nvo[5], nvo[7], Caddivi());
    nvo[2]=CrearNodoArb(nvo[4], nvo[3], Cadexpo());
    nvo[1]=CrearNodoArb(fun->izq, nvo[2], Cadprod());
    nvo[0]=CrearNodoArb(DerivarArbolFuncion(fun->izq), nvo[1], Caddivi());
    return *nvo;
}

NodoArb* DerivArb_arccsc(NodoArb* fun){
    NodoArb **nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
    nvo[1]=CrearNodoArb(NULL, NULL, Cadcero());
    nvo[0]=CrearNodoArb(nvo[1], DerivArb_arcsec(fun), Caddif());
    return *nvo;
}

NodoArb* DerivArb_ln(NodoArb* fun){
    NodoArb* nvo=CrearNodoArb(DerivarArbolFuncion(fun->izq), fun->izq, Caddivi());
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
                nvo=DerivArb_Raiz(fun);
            } else {
                //f(x)^g(x)
                nvo=DerivArb_Fun_Fun(fun);
            }
        } else {
            nvo=CrearNodoArb(NULL, NULL, Cadcero());
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
    *p=Push(p, Cadcoma());
}

char *Derivar(char *funcionx){
    char*exp1, *res;
    NodoArb* exp2, *exp3;
    NodoL* p;
    CrearPila(&p);
    
    //Se convierte a notación postfija y después se construye el árbol
    exp1=Convertir_Lista_Cadena(PostFijo(funcionx));
    exp2=SimplificarFun(ConstruirArbolFuncion(exp1));

    //Se construye el árbol derivado, se simplifica y se convierte a cadena en notación infija
    Convertir_Arbol_Lista(SimplificarFun((exp2)), &p);
    //Convertir_Arbol_Lista(DerivarArbolFuncion(exp2), &p);
    //Convertir_Arbol_Lista(SimplificarFun(DerivarArbolFuncion(exp2)), &p);
    
    res=Convertir_Lista_Cadena(p);
    return ((Expifj*)Infija(res)->dato)->exp;
}