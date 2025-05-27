/*
25/04/2025
Bien lo dice el nombre del archivo (creo), en esta ocacion se vera los arboles
binarios, los cuales son simplemente nodos con un maximo de dos arcos (enlaces),
los cuales a su vez conectan con otros arboles binarios (RECURSIVIDAD).

Como se construya el arbol, es de acuerdo al problema en el que se este usando, 
pero aqui se da un pequeno ejemplo de como debe de usarse sus funciones.
*/
#include <stdio.h>
#include <stdlib.h>

struct nodoArbol{
    void* dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
};typedef struct nodoArbol NodoArb;

NodoArb* crearNodoArb(NodoArb* izq, NodoArb* der, void* dato){
    NodoArb* newn;
    newn=(NodoArb*)malloc(sizeof(NodoArb));
    newn->izq=izq;
    newn->der=der;
    newn->dato=dato;
    return newn; 
}

//Inorden
void imprimeArb(NodoArb* r, void(*f)(void*)){
    if(!r) return;
    imprimeArb(r->izq, f);
    f(r->dato);
    imprimeArb(r->der, f);
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

int main(){
    NodoArb* A;
    NodoArb* B;
    NodoArb* C;
    NodoArb* D;
    NodoArb* E;
    int a=1, b=2, c=3, d=4, e=5;
    D=crearNodoArb(NULL, NULL, &d);
    E=crearNodoArb(NULL, NULL, &e);
    B=crearNodoArb(D, E, &b);
    C=crearNodoArb(NULL, NULL, &c);
    A=crearNodoArb(B, C, &a);
    /*
      1
    /  \
    2   3
    /\
    4 5
    */
    imprimeArb(A, &impInt);
    return 0;
}