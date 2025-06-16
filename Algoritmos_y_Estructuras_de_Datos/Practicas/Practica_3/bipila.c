#include <stdio.h>
#include <stdlib.h>
#define MAX 14
/*
En esta ocación trabajeromos con bipila, la cual es basicamente dos pilas que comparte la misma unidad de memoria.
La primera tiene inicializado su tope en 0.
La segunda tiene su tope inicializado en n-1.
Todas las demas funciones son mas o menos igual, lo unico que cambia es en que pila se realiza la accion
*/
typedef struct Bipila{
    void ** ele;
    int tpinf;
    int tpsup;
}BP;
BP* InicBP();
void *top(BP * bipila, int(*ef)(BP*, int), int pila);
void push(BP * bipila, void* ele, int(*ef)(BP*), int pila);
void* pop(BP * bipila, int(*ef)(BP*, int), int pila);
int IsEmpty(BP * bipila, int pila);
int IsFull(BP * bipila);

int main(){
    BP* mbp;
    int a=3, b=4;
    int list[15];
    mbp=InicBP();
    for(int i=0; i<10; i++){
        list[i]=i+1;
        push(mbp, &list[i], IsFull, 0);
        //printf("\n%d", mbp->tpinf);
    }

    for(int i=10; i<15; i++){
        list[i]=i+1;
        push(mbp, &list[i], IsFull, 1);
        //printf("\n%d", mbp->tpsup);
    }
    printf("\nTope1: %d, Cont: %d", mbp->tpinf, *(int*)top(mbp, &IsEmpty, 0));
    printf("\nTope2: %d, Cont: %d", mbp->tpsup, *(int*)top(mbp, &IsEmpty, 1));
    pop(mbp, IsEmpty, 1);
    printf("\nTope 2 despues del pop: %d", mbp->tpsup);
    //push(mbp, &a, IsFull);
    //push(mbp, &b, IsFull);
    //push(mbp, &b, IsFull);

    //printf("\n%d",*(int*)top(mbp, IsEmpty));
    /*
    
    pop(mbp, IsEmpty);*/
    return 0;
}

BP* InicBP(){
    BP* bp;
    bp=(BP*)malloc(sizeof(BP));
    bp->ele=(void**)malloc(MAX*sizeof(void*));
    bp->tpinf=0;
    bp->tpsup=MAX-1;
    return bp;
}
void *top(BP * bipila, int(*ef)(BP*, int), int pila){
    if(pila==1){
        if(ef(bipila, 1)==1){
            printf("\nPILA VACIA");
            return (void*)NULL;
        }
        return bipila->ele[bipila->tpsup+1];
    }else if(pila==0){
        if(ef(bipila, 0)==1){
            printf("\nPILA VACIA");
            return (void*)NULL;
        }
        return bipila->ele[bipila->tpinf-1];
    }else{
        printf("\nPila no valida");
        return (void*)NULL;
    }
}
void push(BP * bipila, void* ele, int(*ef)(BP*), int pila){
    if(ef(bipila)==1){
        printf("\nPILA LLENA");
        return;
    }
    if(pila==1){
        bipila->ele[bipila->tpsup]=ele;
        bipila->tpsup--;
    }else if(pila==0){
        bipila->ele[bipila->tpinf]=ele;
        bipila->tpinf++;
    }else{
        printf("\nPila no valida.");
    }
    return;
}
void* pop(BP * bipila, int(*ef)(BP*, int), int pila){
    if(pila==1){
        if(ef(bipila, 1)==1){
            printf("\nPILA VACIA");
            return (void*)NULL;
        }
        bipila->tpsup++;
        return bipila->ele[bipila->tpsup];
    }else if(pila==0){
        if(ef(bipila, 0)==1){
            printf("\nPILA VACIA");
            return (void*)NULL;
        }
        bipila->tpinf--;
        return bipila->ele[bipila->tpinf];
    }else{
        printf("\nPila no valida.");
    }
}
int IsEmpty(BP * bipila, int pila){
    if(pila==1){
        if(bipila->tpsup==MAX-1) return 1;
        return 0;
    }else if(pila==0){
        if(bipila->tpinf==0) return 1;
        return 0;
    }
    return -1;
}
int IsFull(BP * bipila){
    if(bipila->tpinf-1==bipila->tpsup) return 1;
    return 0;
}
