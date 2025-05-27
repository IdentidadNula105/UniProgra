#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct testamento{
    int dato;
    int tipo;//0=plebeyo, 1=noble
} Testamento;

typedef struct ColaM{
    Testamento* a[MAX];
    int tam;
} ColaMed;

ColaMed *crearCM(){
    ColaMed* nvo;
    nvo=(ColaMed*)malloc(sizeof(ColaMed));
    nvo->tam=0;
}

void agregarElet(ColaMed *colm, Testamento* ele){
    if(!colm->tam){
        colm->a[colm->tam]= ele;
    } else if(colm->tam==MAX){
        return;
    } else {
        if(ele->tipo==1){
            
        } else {
            colm->a[colm->tam]=ele;
        }
    }
    colm->tam++;
}

int consultarcola(ColaMed *colm){
    return colm->a[colm->tam-1];
}

int eliminarcola(ColaMed *colm){
    return colm->a[colm->tam--];
}

int numPlebeyos(ColaMed *colm){
    int contp=0;
    for(int i=0; i<colm->tam; i++) if(colm->a[i]==0) contp++;
    return contp;
}

int numNobles(ColaMed *colm){
    int contn=0;
    for(int i=0; i<colm->tam; i++) if(colm->a[i]==1) contn++;
    return contn;
}

int ColaVacia(ColaMed *colm){
    if(!colm->tam) return 1;
    return 0;
}