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

typedef struct deque{
    NodoLD *fren;
    NodoLD *fin;
} Deque;

NodoLD* crearNLD(void *dato){
    NodoLD *nvo;
    nvo=(NodoLD*)malloc(sizeof(NodoLD));
    nvo->dato=dato;
    nvo->ant=nvo->sig=NULL;
    return nvo;
}

Deque *crearDeque(){
    Deque *dqnv=(Deque*)malloc(sizeof(Deque));
    dqnv->fren=dqnv->fin=(NodoLD*)NULL;
    return dqnv;
}

void InsertIncioD(Deque *dq, void *dato){
    NodoLD* ndnv=crearNLD(dato);
    if(!dq->fren){
        dq->fin=ndnv;
    } else {
        dq->fren->ant=ndnv;
        ndnv->sig=dq->fren;
    }
    dq->fren=ndnv;
}

void InsertFinalD(Deque *dq, void *dato){
    NodoLD* ndnv=crearNLD(dato);
    if(!dq->fren){
        dq->fren=ndnv;
    } else {
        dq->fin->sig=ndnv;
        ndnv->ant=dq->fin;
    }
    dq->fin=ndnv;
}

void* EliminarFinalD(Deque *dq){
    if(!dq->fren) return (void*)NULL;
    NodoLD *aux;
    void *dat=dq->fin->dato;
    if(dq->fren==dq->fin){
        free(dq->fin);
        dq->fren=dq->fin=NULL;
    } else {
        aux=dq->fin->ant;
        aux->sig=NULL;
        free(dq->fin);
        dq->fin=aux;
    }
    return dat;
}

void* EliminarInicioD(Deque *dq){
    if(!dq->fren) return (void*)NULL;
    NodoLD *aux;
    void *dat=dq->fren->dato;
    if(dq->fren==dq->fin){
        free(dq->fren);
        dq->fren=dq->fin=NULL;
    } else {
        aux=dq->fren->sig;
        aux->ant=NULL;
        free(dq->fren);
        dq->fren=aux;
    }
    return dat;
}

void* MostrarInicio(Deque* dq){
    if(!dq->fren) return (void*)NULL;
    return dq->fren->dato;
}

void* MostrarFinal(Deque* dq){
    if(!dq->fren) return (void*)NULL;
    return dq->fin->dato;
}

void impLD(Deque *dq){
    for(NodoLD *p=dq->fren;p;p=p->sig) printf("(%d)", *(int*)p->dato);
}

int main(){
    int a=1, b=2, c=3, d=4;
    Deque *dq1;
    int h;
    dq1=crearDeque();
    InsertIncioD(dq1, &a);
    InsertIncioD(dq1, &b);
    InsertFinalD(dq1, &c);
    InsertFinalD(dq1, &d);
    h=*(int*)EliminarFinalD(dq1);
    //printf("(%d)", *(int*)EliminarFinalD(dq1));
    impLD(dq1);
    return 0;
}