/*
24/05/2025
Una lista doblemente enlazada es casi lo mismo que una lista enlazada, 
con la diferencia de cada nodo apunta al siguiente y al anterior nodo.
Operaciones:
- Inicializar lista 
- Agregar nodo al principio de la lista
- Agregar nodo al final de la lista
- Eliminar nodo al final de la lista
- Eliminar nodo al principio de la lista
- Eliminar nodo con dato dado
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

void InsertarIncioNLD(NodoLD **ld, void *dato){
    NodoLD *nvo;
    nvo=crearNLD(dato);
    if(*ld){
        nvo->sig=*ld;
        (*ld)->ant=nvo;
    } 
    *ld=nvo;
}

void InsertarFinalNLD(NodoLD **ld, void *dato){
    NodoLD *nvo, *p;
    nvo=crearNLD(dato);
    if(!*ld) *ld=nvo;
    p=*ld;
    while(p->sig) p=p->sig;
    nvo->ant=p;
    p->sig=nvo;
}

void EliminarFinalNLD(NodoLD** ld){
    if(!*ld){
        printf("LISTA VACIA");
        return;
    }    
    NodoLD *p=*ld, *q=NULL;
    while(p->sig) p=p->sig;
    if(!p->ant){
        *ld=NULL;
        return;
    }
    q=p->ant;
    q->sig=NULL;
    p->ant=NULL;
}

void EliminarInicioNLD(NodoLD **ld){
    if(!*ld){
        printf("LISTA INV");
        return;
    }
    if(!(*ld)->sig){
        *ld=NULL;
        return;
    }
    NodoLD* p=(*ld)->sig;
    p->ant=NULL;
    (*ld)->sig=NULL;
    *ld=p;
}

void EliminarNodoLD(NodoLD **ld, void* dato){
    NodoLD *p=*ld;
    if(!*ld){
        printf("LISTA VACIA");
        return;
    }
    while(p && p->dato!=dato) p=p->sig;
    if(!p){
        printf("ELEMENTO NO ENCONTRADO");
        return;
    }
    //CHATGPT, no es que no pude hacerlo, solo quize hacerlo de la manera mas eficiente
    if (p->ant != NULL)
        p->ant->sig = p->sig;
    else
        *ld = p->sig; // era el primero

    if (p->sig != NULL)
        p->sig->ant = p->ant;
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
    InsertarIncioNLD(&ld1, &a[0]);
    InsertarIncioNLD(&ld1, &a[1]);
    InsertarFinalNLD(&ld1, &a[2]);
    InsertarFinalNLD(&ld1, &a[3]);
    impLD(ld1);
    printf("\n");
    EliminarNodoLD(&ld1, &a[2]);
    impLD(ld1);
}