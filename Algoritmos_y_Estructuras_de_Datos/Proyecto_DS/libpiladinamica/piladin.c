#include <stdio.h>
#include <stdlib.h>
#include "piladin.h"

NodoL* RemoveN(NodoL**cab){
    NodoL* p;
    if(!*cab)return NULL;
    p=*cab;
    *cab=p->sig;
    p->sig=NULL;
    return p;
}

NodoL* CrearNodoL(NodoL* cab, void* dato){
    NodoL* np;
    np=(NodoL*)malloc(sizeof(NodoL));
    np->dato=dato;
    np->sig=cab;
    return np;

}

void CrearPila(NodoL** stack){
    *stack=NULL;
}

int NumeroNL(NodoL* n){
    if(n->sig==NULL) return 1;
    return 1+NumeroNL(n->sig);
}

NodoL* ConcatenarListInvertida(NodoL* L1, NodoL* L2){
    if(L2->sig==NULL) return CrearNodoL(L1, L2->dato);
    L1=ConcatenarListInvertida(L1, L2->sig);
    L1=CrearNodoL(L1, L2->dato);
}

int IsEmpty(NodoL* stack){
    return !stack;
}

NodoL* Push(NodoL** stack, void* dato){
    *stack=CrearNodoL(*stack, dato);
    return *stack;
}

void* Top(NodoL* stack){
    return stack->dato;
}

void* Pop(NodoL** stack){
    return RemoveN(stack)->dato;
}