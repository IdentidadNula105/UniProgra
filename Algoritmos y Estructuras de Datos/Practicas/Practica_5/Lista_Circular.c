/*
18/05/2025
En esta practica se codificara las funciones para una lista circular, la cual
basicamente es que el ultimo no apunte al primero.
Las funciones son:
- Crear
- Insertar
- Eliminar
- Recorrer
- Avanzar al siguiente
Mas aparte, se tendra que implementar en un carrusel (sin interfaz, obviamente)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodoL{
    void *dato;
    struct nodoL *sig;
}NodoL;

void *createLC(NodoL** list){
    *list=(NodoL*)NULL;
}

NodoL *insertNC(void* dato, NodoL* list){
    NodoL *p, *q;
    p=(NodoL*)malloc(sizeof(NodoL));
    p->dato=dato;
    if(!list){
        p->sig=p;
        return p;
    } else {
        p->sig=list->sig;
        list->sig=p;
        return list;
    }
}

void deleteNC(NodoL *list){
    NodoL* p, *q;
    if(!list) return;
    if((list)->sig=list){
        free(list);
        return;
    } 
    p=list->sig;
    list->sig=p->sig;
    //p=(NodoL*)NULL;
}

void travelLC(NodoL* list, void(*f)(void*)){
    NodoL* p;
    p=list;
    do{
        f(p->dato);
        p=p->sig;
    } while(p!=list);
}

void nextNC(NodoL **list){
    NodoL* p;
    p=*list;
    *list=p->sig;
}

void prtInt(void *dato){
    printf("(%d)", *(int*)dato);
}

int main(){
    NodoL* LC;
    int a=2, b=3, c=4, d=5, e=6;
    createLC(&LC);
    LC=insertNC(&a, LC);
    LC=insertNC(&b, LC);
    LC=insertNC(&c, LC);
    LC=insertNC(&d, LC);
    LC=insertNC(&e, LC);
    travelLC(LC, &prtInt);
    deleteNC(LC);
    printf("\n");
    travelLC(LC, &prtInt);
}