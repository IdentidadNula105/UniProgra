#include <stdio.h>
#include <stdlib.h>
#include "derivsimb.h"
#include "is.h"

void Menu();

int main(){
    char* funcion;
    Menu();
    printf("\n\nf(x)=");
    scanf("%[^\n]", funcion);
    if(!IsFuncionValida(funcion)){
        printf("\nFUNCION NO VALIDA");
    } else {
        printf("\nf'(x)=");
        printf("%s", Derivar(funcion));
    }
    return 0;
}

void Menu(){
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - Derivador Simbolico - - - - - - - - - - - - - - - - - - - - - - - - -");
    printf("\nIntroduzca su funcion en x considerando lo siguiente:");
    printf("\n\nA) El programa puede derivar las siguientes funciones:");
    printf("\n   -> sen, cos, tan, cot, sec, csc");
    printf("\n   -> arcsen, arccos, arctan, arccot, arcsec, arccsc");
    printf("\n   -> ln");
    printf("\n\nB) Use la jerarquia de operaciones para escribir su funcion: ");
    printf("\n   1. '()', funciones ln o trigonometricas");
    printf("\n   2. '^'");
    printf("\n   3. '*', '/'");
    printf("\n   4. '+', '-'");
    printf("\n   Ejemplo: x^2/x+1 NO ES IGUAL A x^2/(x+1)");
    printf("\n\nC) Si desea escribir una multiplicacion use siempre '*':");
    printf("\n   Ejemplo: 3*2, 2*x, 4*(3-x)");
    printf("\n\nD) Si desea escribir una funcion ln o trigonometrica, escriba el argumentro dentro de '()': ");
    printf("\n   Ejemplo: sen(x), arccot(x+3), tan(sec(x))");
    printf("\n\nE) Si desea escribir un exponente use '^':");
    printf("\n   Ejemplo:  3^2, (x-3)^3, 8^(x-ln(x))");
    printf("\n\nF) Si desea escribir una raiz use un equivalente como exponente con '^': ");
    printf("\n   Equivalencias: Raiz cuadrado -> u^(1/2)");
    printf("\n                 Raiz tercia   -> u^(1/3)");
    printf("\n                 Raiz cuarta   -> u^(1/4)");
    printf("\n   Ejemplo:  3^(1/2), (x^2+x)^(3/4), 8^(7/6)");
    printf("\n\nG) Si desea elevar una funcion ln o trigonometrica, use '^':");
    printf("\n   Ejemplo:  SI -> csc(x)^3");
    printf("\n             NO -> csc^3(x).");
}