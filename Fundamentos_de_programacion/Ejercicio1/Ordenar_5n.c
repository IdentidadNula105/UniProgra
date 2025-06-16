#include <stdio.h>

int main(){
    //Vamos a ordenar 5 numeros de menor a mayor
    int numeros[5];
    int prov, i, j;
    prov=0;
    i=0;
    j=0;
    //Primeramente vamos a recoger los numeros
    while(i<5){
    printf("Por favor, ingrese el numero %d:\n", i+1);
    scanf("%d",&numeros[i]);
    i=i+1;
    }
    i=0;
    //Aqui se ordenan los numeros
    while (i<4){
    i=0;
    j=0;
    while(j<4){
    if(numeros[j]>numeros[j+1]){
    prov=numeros[j];
    numeros[j]=numeros[j+1];
    numeros[j+1]=prov;
    }else{
    i=i+1;
    }
    j=j+1;
    }
    }
    i=0;
    //Se imprime la lista ordenada
    printf("\nSu lista ordenada es:");
    while(i<5){
    if(i==4){
    printf(" %d.", numeros[i]);
    } else {
    printf(" %d,", numeros[i]);
    }
    i=i+1;
    }
}