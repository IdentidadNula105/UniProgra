/*Hoy veremos como hacer mini librerias, las cuales nos serviran para la practica 01*/
//Nota: si lees un entero o cualquier ptro dato y luego un caracter, se saltara el scan del caracter.

#include <stdio.h>
#include "insano.h"
#define MAX 1000
int main(){
    int a=0;
    int b=0;
    int resultado=0;
    int op=0;

    do{
        printf("\nBienvenido a su libreria 'insano', por favor escoja una opcion.");
        printf("\n1. Tilin");
        printf("\n2. Suma");
        printf("\n3. Salir");
        printf("\nElija del 1-3: ");
        scanf("%d", &op);

        switch(op){
        case 1:
        Tilin();
        op=Continuar();
        break;

        case 2:
        printf("\nN1: ");
        scanf("%d", &a);
        printf("N2: ");
        scanf("%d", &b);
        resultado=Suma(a, b);
        printf("%d+%d=%d",a,b,resultado);
        op=Continuar();
        break;

        case 3:
        printf("\nSaliendo...");
        break;

        default:
        printf("\nOpcion invalida");
        break;
    }
    }while(op != 3);
    return 0;
}