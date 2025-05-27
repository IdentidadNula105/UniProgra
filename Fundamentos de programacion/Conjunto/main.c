//Todo lo anterior se realizo el 18/11/2024
#include <stdio.h>
#include "Conjunto.h"
void ResetearConjunto(conjunto *X);

int main(){
    conjunto A, B, C;
    int primo=0;
    InicializarConjunto(&A);
    InicializarConjunto(&B);
    InicializarConjunto(&C);
    printf("\n");
    //A
    for(int i=0; i<50;i++){
        AgregarElemento(&A, i);
    }
    printf("\nConjunto A: ");
    ImprimeConjunto(&A);
    printf("\n");

    //B
    for(int i=21,j=0;j<50;i=3+i, j++){
        AgregarElemento(&B,i);
    }
    printf("\nConjunto B: ");
    ImprimeConjunto(&B);
    printf("\n");

    //C
    for(int i=0;i<A.size;i++){
        if(ElementoPrimo(A.C[i])==-1){
            primo++;
        }
    }
    printf("\nNumero de primos en A: %d", primo);
    primo=0;
    for(int i=0;i<B.size;i++){
        if(ElementoPrimo(B.C[i])==-1){
            primo++;
        }
    }
    printf("\nNumero de primos en B: %d", primo);
    printf("\n");
    //D
    for(int i=0, l=0;i<A.size;i++){
        if(A.C[i]==A.C[A.size-1]){
            if(ElementoPrimo(A.C[i])==-1 ||A.C[i]%2==0){
                EliminarElemento(&A,A.C[i]);
            }
        }else{
        while(ElementoPrimo(A.C[i])==-1 ||A.C[i]%2==0){
            EliminarElemento(&A,A.C[i]);
        }
        }
    }
    printf("\nConjunto A sin numeros primos ni pares: ");
    ImprimeConjunto(&A);
    printf("\n");
    //E
    for(int i=0;i<A.size;i++){
        if(PerteneceElemento(&B,A.C[i])==0){
            AgregarElemento(&C,A.C[i]);
        }
    }
    printf("\nA interseccion B: ");
    ImprimeConjunto(&C);
    return 0;
}