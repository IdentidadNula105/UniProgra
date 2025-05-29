/*
28/05/2025
Una cola de prioridad es aquella en donde los elementos son atendidos no solamente
por ser los primeros en llegar, si no también por su nivel de prioridad.
Dicha prioridad depende del problema, como en este caso, la prioridad es binaria, 
es decir, los elementos que sean de tipo 1/noble son atendidos primero, despues
los catalogados por 0/plebeyos.
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct estamento{
    int dato;
    int tipo;//0=plebeyo, 1=noble
} Estamento;

typedef struct ColaM{
    Estamento* a[MAX];
    int tam;
} ColaMed;

ColaMed *crearCM(){
    ColaMed* nvo;
    nvo=(ColaMed*)malloc(sizeof(ColaMed));
    nvo->tam=0;
    return nvo;
}

void agregarElet(ColaMed *colm, Estamento* ele){
    int i;
    if(!colm->tam){
        colm->a[colm->tam]= ele;
    } else if(colm->tam==MAX+1){
        return;//cola LLENA
    } else {
        if(colm->a[colm->tam-1]->tipo==ele->tipo || !ele->tipo) colm->a[colm->tam]=ele;
        else {
            for(i=colm->tam-1; i>0 && colm->a[i-1]->tipo!=1; i--);//encontrar el indice del ultimo noble
            for(int j=colm->tam-1; j>=i; j--) colm->a[j+1]=colm->a[j];//Mover un lugar todos los plebeyos
            colm->a[i]=ele;
        }
    }
    colm->tam++;
}

int consultarcola(ColaMed *colm){
    if(!colm->tam) return 0;
    return colm->a[0]->dato;
}

int eliminarcola(ColaMed *colm){
    Estamento *aux;
    aux=colm->a[0];
    for(int i=0; i<colm->tam-1; i++) colm->a[i]=colm->a[i+1];
    colm->tam--;
    return aux->dato;
}

int numPlebeyos(ColaMed *colm){
    int contp=0;
    for(int i=0; i<colm->tam; i++) if(colm->a[i]->tipo==0) contp++;
    return contp;
}

int numNobles(ColaMed *colm){
    int contn=0;
    for(int i=0; i<colm->tam; i++) if(colm->a[i]->tipo==1) contn++;
    return contn;
}

int ColaVacia(ColaMed *colm){
    if(!colm->tam) return 1;
    return 0;
}

void impColat(ColaMed *colm){
    for(int i=0; i<colm->tam; i++) printf("(%d)", colm->a[i]->dato);
}

int main(){
    ColaMed *xd;
    Estamento lol[4];
    int h=0;
    lol[0].dato=3;
    lol[0].tipo=1;
    lol[1].dato=4;
    lol[1].tipo=1;
    lol[2].dato=1;
    lol[2].tipo=0;
    lol[3].dato=5;
    lol[3].tipo=0;
    xd=crearCM();

    agregarElet(xd, &lol[3]);// Plebeyo
    agregarElet(xd, &lol[1]);// Noble
    agregarElet(xd, &lol[0]);// Noble
    agregarElet(xd, &lol[2]);// Plebeyo
    impColat(xd);//4 3 5 1
    printf("\nPrimer elmento: %d", consultarcola(xd));
    //impColat(xd);//3 1
}