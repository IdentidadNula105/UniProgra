/*
25/05/2025
Una cola pero con listas doblemente enlazadas jaja.
Esto fue para un ejercicio de examen, asi que cito:
"Una cola doble o deque (double-ended queque) es un tipo de datos lineal que permite
consultar, anadir y eliminar elementos en cualquiera de los dos extremos de la cola.
Se pide: Implementar colas dobles usando listas doblemente enlazadas."
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodoLD{
    void* dato;
    struct nodoLD *sig;
    struct nodoLD *ant;
} NodoLD;

NodoLD* crearNLD(void *dato){
    NodoLD *nvo;
    nvo=(NodoLD*)malloc(sizeof(NodoLD));
    nvo->dato=dato;
    nvo->ant=NULL;
    nvo->sig=NULL;
    return nvo;
}

void inicCola(NodoLD** cola){
    *cola=NULL;
}

void InsertarIncioC(NodoLD **cola, void *dato){
    NodoLD *nvo;
    nvo=crearNLD(dato);
    if(*cola){
        nvo->sig=*cola;
        (*cola)->ant=nvo;
    } 
    *cola=nvo;
}

void InsertarFinalC(NodoLD **cola, void *dato){
    NodoLD *nvo, *p;
    nvo=crearNLD(dato);
    if(!*cola) *cola=nvo;
    p=*cola;
    while(p->sig) p=p->sig;
    nvo->ant=p;
    p->sig=nvo;
}

void* EliminarFinalC(NodoLD** cola){
    if(!*cola){
        printf("LISTA VACIA");
        return NULL;
    }    
    NodoLD *p=*cola, *q=NULL;
    while(p->sig) p=p->sig;
    void *dato=p->dato;
    if(!p->ant){
        *cola=NULL;
    } else {
        q=p->ant;
        q->sig=NULL;
        p->ant=NULL;
    }
    return dato;
}

void* EliminarInicioC(NodoLD **cola){
    if(!*cola){
        printf("LISTA INV");
        return NULL;
    }
    void *dato=(*cola)->dato;
    if(!(*cola)->sig){
        *cola=NULL;
    } else {
        NodoLD* p=(*cola)->sig;
        p->ant=NULL;
        (*cola)->sig=NULL;
        *cola=p;
    }
    return dato;
}

void* MostrarInicio(NodoLD* cola){
    return cola->dato;
}

void* MostrarFinal(NodoLD* cola){
    NodoLD* p=cola;
    while(p->sig)p=p->sig;
    return p->dato;
}

void impLD(NodoLD *ld){
    if(!ld) return;
    printf("\n(%d)", *(int*)ld->dato);//CAMBIAR SI ES NECESARIO
    impLD(ld->sig);
}

int main(){
    NodoLD* ld1=NULL;
    int a[10];
    for(int i=0;i<10; i++) a[i]=i+1;
    InsertarIncioC(&ld1, &a[0]);
    InsertarIncioC(&ld1, &a[1]);
    InsertarFinalC(&ld1, &a[2]);
    InsertarFinalC(&ld1, &a[3]);
    impLD(ld1);
    printf("\n");
    printf("\n%d", *(int*)MostrarFinal(ld1));
    impLD(ld1);
}