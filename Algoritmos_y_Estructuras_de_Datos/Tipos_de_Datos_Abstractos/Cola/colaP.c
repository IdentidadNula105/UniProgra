/*
28/05/2025
Una cola de prioridad es aquella en donde los elementos son atendidos no solamente
por ser los primeros en llegar, si no también por su nivel de prioridad.
Dicha prioridad depende del problema, como en este caso, la prioridad es binaria, 
es decir, los elementos que sean de tipo 1/noble son atendidos primero, despues
los catalogados por 0/plebeyo.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct nodol{
    void *dato;//Costumbre, para uso general
    int estamento;// 1/noble, 0/plebeyo
    struct nodol* sig;
} NodoL;

typedef struct cola{
    NodoL* fren;
    NodoL* fin;
} ColaM;

ColaM* crearColaM(){
    ColaM* cm;
    cm=(ColaM*)malloc(sizeof(ColaM));
    cm->fren=NULL;
    cm->fin=NULL;
    return cm;
}

int IsEmptyC(ColaM* cm){
    if(!cm->fren) return 1;
    return 0;
}

void Encolar(ColaM* cm, void* dato, int est){
    NodoL* newn=malloc(sizeof(NodoL));
    newn->dato=dato;
    newn->estamento=est;
    newn->sig=NULL;
    if(!cm->fren)
        cm->fren=newn;
        else
        cm->fin->sig=newn;
    cm->fin=newn;
}

void *Desencolar(ColaM* cm){
    if(!cm->fren) return (void*)NULL;
    NodoL *p=cm->fren, *aux;
    void *dat;
    while(p->sig && p->sig->estamento!=1) p=p->sig;
    if(!p->sig){
        aux=cm->fren;
        dat=aux->dato;
        cm->fren=aux->sig;
    } else {
        aux=p->sig;
        dat=aux->dato;
        p->sig=aux->sig;
    }
    free(aux);
    return dat;
}

void *consultarprimCM(ColaM *cm){
    if(!cm->fren) return (void*)NULL;
    NodoL* p=cm->fren;
    while(p->sig && p->estamento!=1) p=p->sig;
    if(p->estamento==1) 
        return p->dato;
        else
        return cm->fren->dato;
}

int numPleb(ColaM* cm){
    int cnp=0;
    for(NodoL* p=cm->fren; p; p=p->sig) if(p->estamento==0) cnp++;
    return cnp;
}

int numNobl(ColaM* cm){
    int cnn=0;
    for(NodoL* p=cm->fren; p; p=p->sig) if(p->estamento==1) cnn++;
    return cnn;
}

void impLD(ColaM *dq){
    for(NodoL *p=dq->fren;p;p=p->sig) printf("(%d)", *(int*)p->dato);
}

int main(){
    ColaM *cm;
    int a=1, b=2, c=3, d=4, e=5;
    cm=crearColaM();
    Encolar(cm, &a, 0);
    Encolar(cm, &b, 0);
    Encolar(cm, &c, 0);
    Encolar(cm, &d, 0);
    Encolar(cm, &e, 1);
    impLD(cm);
    Desencolar(cm);
    printf("\nN: %d", numNobl(cm));
    impLD(cm);
    return 0;
}