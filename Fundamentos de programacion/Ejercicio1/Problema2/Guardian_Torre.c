#include <stdio.h>
/*
Determina que entero es mayor mientras se van introduciendo los numeros
*/
int main(){
    int i;
    int piedra;
    int mayor;
    int n;
    i=0;
    piedra=0;
    mayor=0;
    n=0;

    printf("Introduzca el numero de piedras a analizar: ");
    scanf("%d",&n);
    while(i<n){
        printf("Piedra numero %d: ",i+1);
        scanf("%d",&piedra);
        if(piedra>mayor){
            mayor=piedra;
        }
        i++;
    }
    printf("%d", mayor);
    return 0;
}