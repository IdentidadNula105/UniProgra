//02/04/2025
/*
Lastiosamente, esta clase fue de la que menos entendí, pero, las listas enlazadas son un tipo de dato en
la cual se almacenan los datos de forma en que estos se enlazan.
*/

#include <stdio.h>
#include <stdlib.h>

struct nodo{
    int dato;
    struct nodo *sig;
};
typedef struct nodo Nodo;

Nodo *crearNodo(int dato, Nodo *sig){
    Nodo *nvo=(Nodo*)malloc(sizeof(Nodo));
    nvo->dato=dato;
    nvo->sig=sig;
    return nvo;
}

void imprimeLI(Nodo *cab){//Funcion mia
    if(cab->sig==NULL){
        printf(" %d ", cab->dato);
        return;
    }
    imprimeLI(cab->sig);
    printf(" %d ", cab->dato);
}

void imprimeL(Nodo *cab){//Funcion del profesor
    Nodo *p;
    for(p=cab; p!=NULL; p=p->sig){
        printf("%d", p->dato);
    }
    printf("\n");
}

Nodo *CopiListaS(Nodo* cab, Nodo* (*crn)(int, Nodo*)){
    Nodo *cab2=(Nodo*)NULL;
    Nodo* p;
    for(p=cab; p; p=p->sig){
        cab2=crn(p->dato, cab2);
    }
    return cab2;
}

void removerNodo(Nodo *cab, int dato){
    Nodo *p;
    Nodo *p1;
    for(p=cab; p || p->dato!=dato; p=p->sig){
        p1=p;
    }
}
static Nodo *cab=NULL;
static Nodo *cab2=NULL;

int main(){
    cab=crearNodo(1, cab);
    cab=crearNodo(2, cab);
    cab=crearNodo(3, cab);
    cab=crearNodo(4, cab);
    cab2=(Nodo*)CopiListaS(cab, crearNodo);

    imprimeLI(cab);
    printf("\n");
    //imprimeLI(cab2);

    return 0;
}