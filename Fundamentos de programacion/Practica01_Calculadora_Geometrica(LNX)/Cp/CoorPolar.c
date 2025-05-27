#include <stdio.h>
#include <math.h>
#include "CoorPolar.h"
#define PI 3.14159265358979323846
struct Coordenada{
float valor1;
float valor2;
};
//typedef para darle un alias a la variable estructura
typedef struct Coordenada Coordenada;
Coordenada polar;
Coordenada rectangular;

void MenuCP(){
int op=0;
int resultado=0;
float grados=0.0;
do{
printf("\nCOORDENADAS POLARES");
printf("\n1. Pasar un punto de coordenadas rectangulares a polares");
printf("\n2. Pasar un punto de coordenadas polares a rectangulares");
printf("\n3. Regresar al menú principal");

while (1) {
printf("\nEscoja una opción [1-3]: ");
resultado = scanf("%d", &op);
if (resultado == 1) {
    // Entrada válida
    break;  // Salir del bucle
} else {
    // Entrada inválida
    printf("\nOpción inválida.\n");
    
    // Limpiar el buffer de entrada
    while (getchar() != '\n');  // Leer hasta el salto de línea
}
}

switch (op)
{
case 1:
printf("\nIntroduzca r(x,y): ");
scanf("%f,%f", &rectangular.valor1, &rectangular.valor2);
ConRP();
op=ContinuarCP();
break;

case 2:
printf("\nIntroduzca r: ");
scanf("%f", &polar.valor1);
printf("Introduzca ángulo (en grados): ");
scanf("%f", &grados);
polar.valor2=grados*(PI/180);
ConPR();
op=ContinuarCP();
break;

case 3:
printf("Regresando al menu principal...\n");
break;

default:
printf("\nOpción inválida.\n");
break;
}
}while(op != 3);
}

void ConRP(){
polar.valor1=sqrt(pow(rectangular.valor1,2)+pow(rectangular.valor2,2));
polar.valor2=atan(rectangular.valor2/rectangular.valor1);
printf("\n>>La coordenada rectangular r(%.1f,%.1f) en coordenada polar es: p(%.1f,%.1f rad)\n", rectangular.valor1, rectangular.valor2, polar.valor1, polar.valor2);
}

void ConPR(){
rectangular.valor1=polar.valor1*cos(polar.valor2);
rectangular.valor2=polar.valor1*sin(polar.valor2);
printf("\n>>La coordenada polar p(%.1f,%.1f rad) en coordenada rectangular es: r(%.1f,%.1f)\n", polar.valor1, polar.valor2, rectangular.valor1, rectangular.valor2);
}

int ContinuarCP(){
    char op2=0;
    do{
    getchar();
    printf("\nDesea regresar al menu anterior? [s/n] ");
    scanf("%c", &op2);
    if(op2>64 && op2<91){
        op2=op2+32;
    }
    if(op2=='s'){
        return 0;
    } else if(op2=='n'){
        return 3;
    }
    }while(op2 !='s' || op2 !='n');
}
