#include <stdio.h>//print y scan
#include <math.h>//pow, sqrt
#include <stdlib.h>//Apuntadores
#include <string.h>//Manejo de cadenas

int main(){
    int numero=0, nmenor=0, nmayor=0, i=0, naux=0;
    float promedio=0.0;
    do{
        //printf("\nIngrese un numero: ");
        promedio=promedio+numero;
        scanf("%d", &numero);
        
        if(numero!=0){
        if(i==0){
        nmenor=numero;
        }
        if(numero>nmayor){
            nmayor=numero;
        }else if(numero<nmenor){
            nmenor=numero;
        }
        i++;
        }
    }while(numero!=0);
    promedio=promedio/i;
    printf("%d %d %.2f", nmayor, nmenor, promedio);
    return 0;
}