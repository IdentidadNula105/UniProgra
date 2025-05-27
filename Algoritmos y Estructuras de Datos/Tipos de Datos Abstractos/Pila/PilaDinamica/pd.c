/*
25/04/2025
En esta ocacion veremos lo que es una pila dinamica, la cual en resumidas cuentas 
es una lista enlazada.
*/
#include <stdio.h>
#include <stdlib.h>

struct nodoL{
    void * dato;//Almacena cualquier valor, resguardando la direccion del valor
    struct nodoL * sig;
};typedef struct nodoL NodoL;

NodoL* removeN(NodoL**cab){
    NodoL* p;
    if(!*cab)return NULL;
    p=*cab;
    *cab=p->sig;
    p->sig=NULL;
    return p;
}

NodoL* crearNodoL(NodoL* cab, void* dato){
    NodoL* np;
    np=(NodoL*)malloc(sizeof(NodoL));
    np->dato=dato;
    np->sig=cab;
    return np;

}

void crearPila(NodoL** stack){
    *stack=NULL;
}

//OPERACIONES
int IsEmpty(NodoL* stack){
    return !stack;
}
NodoL* push(NodoL** stack, void* dato){
    *stack=crearNodoL(*stack, dato);
    return *stack;
}

void* top(NodoL* stack){
    return stack->dato;
}

void* pop(NodoL** stack){
    return removeN(stack)->dato;
}

int main(){
NodoL* pA;
int a=34;
char b='c';
float c=3.4;
crearPila(&pA);
pA=push(&pA, &a);
pA=push(&pA, &b);
pA=push(&pA, &c);

printf("Float: %.1f",*(float*)pop(&pA));
printf("Char: %c",*(char*)pop(&pA));
printf("Int: %d",*(int*)pop(&pA));

return 0;
}