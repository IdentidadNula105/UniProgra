/*
18/05/2025
En esta practica se codificara las funciones para una lista circular, la cual
basicamente es que el ultimo apunte al primero?.
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
#include <unistd.h>

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
    NodoL* p;
    if(!list) return;
    if(list==list->sig){
        free(list);
        return;
    }
    p=list->sig;
    list->sig=p->sig;
    free(p);
}

void travelLC(NodoL* list, void(*f)(void*)){
    NodoL* p;
    p=list->sig;
    do{
        f(p->dato);
        p=p->sig;
    } while(p!=list->sig);
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
    char* a="start 1.png", *b="start 2.jpg", *c="start 3.jpg";
    int confirmar=1;
    createLC(&LC);
    LC=insertNC(a, LC);
    LC=insertNC(b, LC);
    LC=insertNC(c, LC);
    while(confirmar==1){
        //printf("\n");
        //travelLC(LC, &prtInt);
        system("cls");
        system((char*)LC->dato);
        nextNC(&LC);
        //printf("\n");
        scanf("%d", &confirmar);
        //sleep(1);
    }
    //deleteNC(LC); 
    //printf("\n");
    //travelLC(LC, &prtInt);
}