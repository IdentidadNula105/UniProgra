//Diaz Amaro Josue Ramses 19/03/2025
/*
PILAS
Las pilas son un tipo de dato abstracto en la cual se almacenan los datos
de forma que el primero en entrar es el ultimo en salir (LIFO: Last In, First Out).

El tope se considera como la posición en donde se guardara el siguiente elemento.
OPERACIONES:
Crear: crea la pila con el tamano dado y el tope inicializado en 0
Push: coloca el elemento dado al final de la pila
Pop: elimina el ultimo elemento que se agrego a la pila y lo devuelve
Top: regresa el ultimo elemento de la pila sin eliminarlo
EstaVacia (IsEmpty): verifica si la pila esta vacia
EstaLlena (IsFull); verifica si la pila esta llena (solo para estaticas)
PrintPila (mio)
*/

//Estatica

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct Pila{
    int *pila;
    int tope;
}Pila;

Pila *InicPila(int n);
void Push(Pila *p, int ele);
int Pop(Pila *p);
int Top(Pila *p);
int IsEmpty(Pila *p);
int IsFull(Pila *p);

int main(){
Pila *pila1;
pila1=InicPila(MAX);
Push(pila1, 4);
Push(pila1, 13);
Push(pila1, 75);
Push(pila1, 45);
Push(pila1, 2);
Push(pila1, 90);
Push(pila1, 67);
Push(pila1, 42);
Push(pila1, 1);
Push(pila1, 0);

printf("\n%d", Pop(pila1));
printf("\n%d", Pop(pila1));

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
    p->pila=malloc(n*sizeof(int));
    p->tope=0;
    return p;
}
void Push(Pila *p, int ele){
    p->pila[p->tope]=ele;
    p->tope++;
}
int Pop(Pila *p){
    p->tope--;
    return p->pila[p->tope];
}
int Top(Pila *p){
    return p->pila[p->tope-1];
}

int IsEmpty(Pila *p){
    return p->tope == 0;
}

int IsFull(Pila *p){
    return p->tope == MAX;
}