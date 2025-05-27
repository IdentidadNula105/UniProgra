#include <stdio.h>
#include <math.h>
#include "LineaRecta.h"

void MenuLR(){
int op=0;
float m=0.0;
float p1x=0.0;
float p1y=0.0;
float p2x=0.0;
float p2y=0.0;
float p3x=0.0;
float p3y=0.0;
float distancia=0.0;

int resultado=0;
do{
printf("\nLA LÍNEA RECTA");
printf("\n1. Ecuación de la recta dada su pendiente y un punto de la misma");
printf("\n2. Ecuación de la recta que pasa por dos puntos");
printf("\n3. Distancia entre dos puntos del plano");
printf("\n4. Punto medio entre dos puntos del plano");
printf("\n5. Perímetro  y área de un triangulo en el plano");
printf("\n6. Regresar al menú principal");

while (1) {
printf("\nEscoja una opción [1-6]: ");
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
printf("\nPendiente: ");
scanf("%f", &m);
printf("Coordenadas de p1(x,y): ");
scanf("%f,%f", &p1x, &p1y);
EcMP(m, p1x, p1y);
op=ContinuarLR();
break;

case 2:
printf("\nCoordenadas de p1(x1,y1): ");
scanf("%f,%f", &p1x, &p1y);
printf("Coordenadas de p2(x2,y2): ");
scanf("%f,%f", &p2x, &p2y);
EcPP(p1x,p1y,p2x,p2y);
op=ContinuarLR();
break;

case 3:
printf("\nCoordenadas de p1(x1,y1): ");
scanf("%f,%f", &p1x, &p1y);
printf("Coordenadas de p2(x2,y2): ");
scanf("%f,%f", &p2x, &p2y);
distancia=DisPP(p1x,p1y,p2x,p2y);
printf("\n>>La distancia entre p1(%.1f,%.1f) y p2(%.1f,%.1f) es: ", p1x, p1y, p2x, p2y);
printf("%.1f\n", distancia);
op=ContinuarLR();
break;

case 4:
printf("\nCoordenadas de p1(x1,y1): ");
scanf("%f,%f", &p1x, &p1y);
printf("Coordenadas de p2(x2,y2): ");
scanf("%f,%f", &p2x, &p2y);
PunM(p1x,p1y,p2x,p2y);
op=ContinuarLR();
break;

case 5:
printf("\nCoordenadas de p1(x1,y1): ");
scanf("%f,%f", &p1x, &p1y);
printf("Coordenadas de p2(x2,y2): ");
scanf("%f,%f", &p2x, &p2y);
printf("Coordenadas de p3(x3,y3): ");
scanf("%f,%f", &p3x, &p3y);
TriPA(p1x,p1y,p2x,p2y,p3x,p3y);
op=ContinuarLR();
break;

case 6:
printf("Regresando al menú principal...\n");
break;

default:
printf("\nOpción inválida.\n");
break;
}
}while(op != 6);
}

void EcMP(float m, float p1x, float p1y){
//y=mx+b
float b=0.0;
b=p1y-m*p1x;
printf("\n>>Ecuación: y = %.1fx + (%.1f)\n", m, b);
}

void EcPP(float p1x, float p1y, float p2x, float p2y){
float m=0.0;
if(p1x==p2x && p1y==p2y){
printf("\n>>No se puede hacer una recta con un dos puntos iguales.\n");
}else{
m=(p2y-p1y)/(p2x-p1x);
EcMP(m, p1x, p1y); 
}
}

float DisPP(float p1x, float p1y, float p2x, float p2y){
float distancia=0.0;
distancia=sqrt(pow(p2x-p1x, 2)+pow(p2y-p1y, 2));
return distancia;
}

void PunM(float p1x, float p1y, float p2x, float p2y){
float mx=0.0;
float my=0.0;
mx=(p1x+p2x)/2;
my=(p1y+p2y)/2;
printf("\n>>Las coordenadas del punto medio entre p1(%.1f,%.1f) y p2(%.1f,%.1f) es: ", p1x, p1y, p2x, p2y);
printf("PM(%.1f, %.1f)\n",mx, my);
}

void TriPA(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y){
float perimetro=0.0;
float semiperimetro=0.0;
float area=0.0;
float d1=0.0, d2=0.0, d3=0.0;
d1=DisPP(p1x,p1y,p2x,p2y);
d2=DisPP(p2x,p2y,p3x,p3y);
d3=DisPP(p1x,p1y,p3x,p3y);
perimetro=d1+d2+d3;
semiperimetro=perimetro/2;
area=sqrt((semiperimetro)*(semiperimetro-d1)*(semiperimetro-d2)*(semiperimetro-d3));
printf("\n>>El perímetro y area del triángulo formado por los puntos p1(%.1f,%.1f), p2(%.1f,%.1f), p3(%.1f,%.1f) son: ",p1x,p1y,p2x,p2y,p3x,p3y);
printf("%.1f y %.1f\n", perimetro, area);
}

int ContinuarLR(){
    char op2=0;
    do{
    getchar();
    printf("\nDesea regresar al menú anterior? [s/n] ");
    scanf("%c", &op2);
    if(op2>64 && op2<91){
        op2=op2+32;
    }
    if(op2=='s'){
        return 0;
    } else if(op2=='n'){
        return 6;
    }
    }while(op2 !='s' || op2 !='n');
}