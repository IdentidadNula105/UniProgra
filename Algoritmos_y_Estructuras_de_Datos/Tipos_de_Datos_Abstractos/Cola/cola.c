/*
24/05/2025
Una es un tipo de dato que sigue el patrón de el primero en entrar es el primero en
en salir (FIFO-First in, First out)
Sus operaciones son:
-Encolar (agrega un elemento a la cola)
-Desencolar (Lee y elimina un elemento de la cola)
-Colavacia (te doy un chocolate si lo adivinas)
NOTA: esta es una cola especial, pues se tiene apuntadores al primero y al último
de la cola. Para hacer una cola "normal", haz una lista enlazada pero con la unica
diferencia de que el cabezal nunca cambia.
void crearEleCola(NodoLD **cola, void *dato){
    NodoLD* nvo, *p;
    nvo=crearNLD(dato);
    if(!*cola){
        *cola=nvo;
    } else {
        p=*cola;
        while(p->sig) p=p->sig;
        p->sig=nvo;
        nvo->ant=p;
    }
}
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    void *dato;//Costumbre, para uso general
    struct Nodo* sig;
} Nodo;

typedef struct cola{
    Nodo* frente;
    Nodo* final;
} Cola;

Cola* inicCola(){
    Cola* cola;
    cola=(Cola*)malloc(sizeof(Cola));
    cola->frente=NULL;
    cola->final=NULL;
    return cola;
}

int IsEmptyC(Cola* cola){
    if(!cola->frente) return 1;
    return 0;
}

void Encolar(Cola* cola, void* dato){
    Nodo* newn;
    newn=malloc(sizeof(Nodo));
    newn->dato=dato;
    newn->sig=NULL;
    if(!cola->frente)
        cola->frente=newn;
        else
        cola->final->sig=newn;
    cola->final=newn;
}

void *Desencolar(Cola* cola){
    if(IsEmptyC(cola)){
        printf("COLA VACIA");
        return (void*)NULL;
    } 
    Nodo* naux=cola->frente;
    void* daux=naux->dato;
    cola->frente=naux->sig;
    if(!cola->frente) cola->final=NULL;
    free(naux);
    return daux;
}

int main(){
    Cola* c1;
    int a=2, b=4, c=10;
    c1=inicCola();
    Encolar(c1, &a);
    Encolar(c1, &b);
    Encolar(c1, &c);

    printf("\nElemento eliminado: %d", *(int*)Desencolar(c1));
    printf("\nElemento eliminado: %d", *(int*)Desencolar(c1));
    printf("\nElemento eliminado: %d", *(int*)Desencolar(c1));
    printf("\nElemento eliminado: %d", *(int*)Desencolar(c1));
    return 0;
}