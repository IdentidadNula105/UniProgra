/*Este archivo contendra a las funciones como tal, no olvides seguir los comandos en el .bat que se anexa*/
/*Recuerda, las funciones solo son el back, por lo que nada de recibir datos aqui*/
#include <stdio.h>
#include "insano.h"

void Tilin(){
    printf("Tilin te dice: 'Hola'");
}

int Suma(int a, int b){
    int resultado=0;
    resultado=a+b;
    return resultado;
}

int Continuar(){
char respuesta=0;
do{
getchar();
printf("\nDesea regresar al menu? s/n\n");
scanf("%c", &respuesta);
if(64<respuesta && respuesta<91){
    respuesta=respuesta+32;
}
if(respuesta == 'n'){
    return 3;
}else if(respuesta == 's'){
    return 0;
}
} while (respuesta !='s' || respuesta !='n');
printf("\n\n");
}

