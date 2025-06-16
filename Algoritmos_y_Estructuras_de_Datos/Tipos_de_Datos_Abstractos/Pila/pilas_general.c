//Diaz Amaro Josue Ramses 19/03/2025
/*
PILAS
Las pilas son un tipo de dato abstracto en la cual se almacenan los datos
de forma que el primero en entrar es el ultimo en salir (LIFO: Last In, First Out).

El tope se considera como la posición en donde se guardara el siguiente elemento.
OPERACIONES:
Crear: crea la pila con el tamano dado y el tope inicializado en 0
Push: coloca el elemento dado al final de la pila
Pop: elimina el ultimo elemento que se agrego a la pila
Top: regresa el ultimo elemento de la pila sin eliminarlo
EstaVacia (IsEmpty): verifica si la pila esta vacia
EstaLlena (IsFull); verifica si la pila esta llena (solo para estaticas)
PrintPila (mio)
*/

//Estatica

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Pila{
    void **pila;
    int tope;
}Pila;

Pila *InicPila(int n);
void Push(Pila *p, void* ele);
void* Pop(Pila *p);
void* Top(Pila *p);
int IsEmpty(Pila *p);
int IsFull(Pila *p);

int main(){
Pila *pila1;
int a=45;
char* b="Hola";
float c=3.14;
pila1=InicPila(MAX);
Push(pila1, &a);
Push(pila1, b);
Push(pila1, &c);
printf("\n%.2f", *(float*)Pop(pila1));
printf("\n%s", (char*)Pop(pila1));
printf("\n%d", *(int*)Pop(pila1));

if(IsEmpty(pila1)){
    printf("\nEsta vacia jaja");
}else{
    printf("\nNo esta vacia");
}

if(IsFull(pila1)){
    printf("\nEsta llena");
}else{
    printf("\nNo esta llena");
}
}

Pila *InicPila(int n){
    Pila *p;
    p->pila=(void**)malloc(n*sizeof(void*));
    p->tope=0;
    return p;
}
void Push(Pila *p, void* ele){
    p->pila[p->tope]=ele;
    p->tope++;
}
void* Pop(Pila *p){
    p->tope--;
    return p->pila[p->tope];
}
void* Top(Pila *p){
    return p->pila[p->tope-1];
}

int IsEmpty(Pila *p){
    return p->tope == 0;
}

int IsFull(Pila *p){
    return p->tope == MAX;
}