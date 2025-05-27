/*Modificado el 29/11/2024*/
#include <stdio.h>
#include <stdlib.h>
#define FILAS 10
#define COLUMNAS 10

int main(){
    printf("%d\n",FILAS);
    printf("%d\n",COLUMNAS);
    for(int i=0; i<COLUMNAS*FILAS*2;i++){
        printf("0\n", rand());
    }
}