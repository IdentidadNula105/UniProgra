#include <stdio.h>
#include <math.h>
#include "Circunferencia.h"
#include "../LR/LineaRecta.h"

void MenuC(){
int op=0;
int resultado=0;
float r=0.0;
float c1x=0.0;
float c1y=0.0;
float p1x=0.0;
float p1y=0.0;

do{
printf("\nLA CIRCUNFERENCIA");
printf("\n1. Ecuación de la circunferencia con centro en el origen y radio r");
printf("\n2. Ecuación de la circunferencia con centro C y radio r");
printf("\n3. Ecuación de la circunferencia con centro C y un punto P");
printf("\n4. Ecuación de la circunferencia con P1 y P2 como extremos  del diámetro");
printf("\n5. Regresar al menú principal");

while (1) {
printf("\nEscoja una opción [1-5]: ");
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
printf("\nIntroduzca el radio de la circunferencia: ");
scanf("%f", &r);
EcOR(r);
op=ContinuarCir();
break;

case 2:
printf("\nCoordenadas del centro de la circuferencia c(cx,cy): ");
scanf("%f,%f", &c1x, &c1y);
printf("Introduzca el radio de la circunferencia: ");
scanf("%f", &r);
EcCR(c1x,c1y,r);
op=ContinuarCir();
break;

case 3:
printf("\nCoordenadas del centro de la circuferencia c(cx,cy): ");
scanf("%f,%f", &c1x, &c1y);
printf("Coordenadas de un punto por donde pase la circuferencia p(px,py): ");
scanf("%f,%f", &p1x, &p1y);
EcCP(c1x,c1y,p1x,p1y,r=0);
op=ContinuarCir();
break;

case 4:
printf("\nCoordenadas del punto p1(p1x,p1y): ");
scanf("%f,%f", &c1x, &c1y);
printf("Coordenadas del punto p2(p2x,p2y): ");
scanf("%f,%f", &p1x, &p1y);
EcPPD(c1x,c1y,p1x,p1y,r);
op=ContinuarCir();
break;

case 5:
printf("Regresando al menu principal...\n");
break;

default:
printf("\nOpción inválida.\n");
break;
}
}while(op != 5);
}

float EcOR(float r){
printf("\n>>La ecuación de la circuferencia con radio %.1f es: x^2 + y^2 = %.1f\n", r, pow(r,2));
}

void EcCR(float c1x, float c1y, float r){
float c=0.0, d=0.0, e=0.0;
c=-2*c1x;
d=-2*c1y;
e=pow(r,2)-(pow(c1x,2)+pow(c1y,2));
printf("\n>>La ecuación de la circuferencia con radio %.1f y c(%.1f,%.1f) es: x^2 + y^2 + (%.1f)x + (%.1f)y = %.1f\n", r, c1x, c1y, c, d , e);
}

void EcCP(float c1x, float c1y, float p1x, float p1y, float r){
r=DisPP(c1x, c1y, p1x, p1y);
EcCR(c1x, c1y, r);
}

void EcPPD(float p1x, float p1y, float p2x, float p2y, float r){
float mx=0.0;
float my=0.0;
mx=(p1x+p2x)/2;
my=(p1y+p2y)/2;
r=DisPP(p1x,p2y,mx,my);
EcCR(mx,my,r);
}

int ContinuarCir(){
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
        return 5;
    }
    }while(op2 !='s' || op2 !='n');
}