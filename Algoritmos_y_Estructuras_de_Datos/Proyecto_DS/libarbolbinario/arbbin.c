
#include <stdio.h>
#include <stdlib.h>
#include "arbbin.h"

NodoArb* CrearNodoArb(NodoArb* izq, NodoArb* der, void* dato){
    NodoArb* newn;
    newn=(NodoArb*)malloc(sizeof(NodoArb));
    newn->izq=izq;
    newn->der=der;
    newn->dato=dato;
    return newn; 
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