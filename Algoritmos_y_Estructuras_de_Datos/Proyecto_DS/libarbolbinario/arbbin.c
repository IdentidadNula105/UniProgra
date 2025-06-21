
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbbin.h"

NodoArb* CrearNodoArb(NodoArb* izq, NodoArb* der, void* dato){
    NodoArb* newn;
    newn=(NodoArb*)malloc(sizeof(NodoArb));
    newn->izq=izq;
    newn->der=der;
    newn->dato=dato;
    return newn; 
}

int CompararArbol(NodoArb* arb1, NodoArb* arb2){
    if(!arb1 || !arb2) return (arb1==arb2);
    if(strcmp((char*)arb1->dato,(char*)arb2->dato)) return 0;
    return (CompararArbol(arb1->izq, arb2->izq) && CompararArbol(arb1->der, arb2->der));
}

//Inorden
void ImprimeArb(NodoArb* r, void(*f)(void*)){
    if(!r) return;
    ImprimeArb(r->izq, f);
    f(r->dato);
    ImprimeArb(r->der, f);
}

void impInt(void* dato){
    printf("%d", *(int*)dato);
}

void impChar(void* dato){
    printf("%c", *(char*)dato);
}

void impCad(void* dato){
    printf("%s", (char*)dato);
}

void impFloat(void* dato){
    printf("%f", *(float*)dato);
}