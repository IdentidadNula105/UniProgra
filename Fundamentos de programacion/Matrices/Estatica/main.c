//Realizado el 22/22/2024, este es un ejemplo de como codificar el main. No lo olvides, facil de entender y autodocumentado
#include <stdio.h>
#define FILA 5
#define COLUMNA 7

//Como estas son matrices estáticas, se debe de especificar las dimensiones en todos los parametros
void LlenaMatriz(int M[FILA][COLUMNA]);
void SumaMatriz(int M1[FILA][COLUMNA], int M2[FILA][COLUMNA], int R[FILA][COLUMNA]); //R guarda el resultado
void ImprimeMatriz(int M[FILA][COLUMNA]);

int main(){
    int A[FILA][COLUMNA], B[FILA][COLUMNA], C[FILA][COLUMNA];
    int i, j;
    printf("Llene la matriz A:\n");
    LlenaMatriz(A);
    ImprimeMatriz(A);
    printf("\n");

    printf("\nLlene la matriz B:\n");
    LlenaMatriz(B);  
    ImprimeMatriz(B);
    printf("\n");

    printf("\nResultado de la suma de A y B:\n");
    SumaMatriz(A, B, C);
    ImprimeMatriz(C);
    return 0;
}

void LlenaMatriz(int M[FILA][COLUMNA]){
    int i,j;
    for(i=0; i<FILA; i++){
        for(j=0; j<COLUMNA; j++){
            scanf("%d", &M[i][j]);
        }
    }
    return;
}

void SumaMatriz(int M1[FILA][COLUMNA], int M2[FILA][COLUMNA], int R[FILA][COLUMNA]){
    int i,j;
    for(i=0; i<FILA; i++){
        for(j=0; j<COLUMNA; j++){
            R[i][j]=M1[i][j]+M2[i][j];
        }
    }
}

void ImprimeMatriz(int M[FILA][COLUMNA]){
    int i,j;
    for(i=0; i<FILA; i++){
        printf("\n");
        for(j=0; j<COLUMNA; j++){
            printf("%d\t", M[i][j]);//\t da un tab en consola
        }
    }
}
