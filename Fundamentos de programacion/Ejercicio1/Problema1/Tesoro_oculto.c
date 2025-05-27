#include <stdio.h>
/*
Suma todos los numeros pares que se vayan ingresando
*/
int main(){
int i;
int numero;
int monedas;
int suma;

i=0;
numero=0;
monedas=0;
suma=0;
printf("Ingrese el numero de monedas magicas: ");
scanf("%d", &monedas);
while(i<monedas){
scanf("%d",&numero);
if(numero%2==0){
suma+=numero;
}
i++;
}
printf("%d\n", suma);
return 0;
}