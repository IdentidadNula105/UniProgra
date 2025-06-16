//29/11/2024
//En este ejercicio se realiza la multiplicación entre dos matrices cuadradas

#include <stdio.h>
#include <stdlib.h>

int** CrearMatriz(int dimension);
void LlenarMatriz(int **M, int dimension);
void ImprimirMatriz(int **M, int dimension);
void MultiplicarMatriz(int **M1, int **M2, int **R, int dimension);

int main(){
int **A, **B, **R;
int dimension;
printf("Escribe la dimension de sus matrices:\n");
scanf("%d", &dimension);

A=CrearMatriz(dimension);
printf("Llene la matriz A: \n");
LlenarMatriz(A, dimension);
printf("\n");

B=CrearMatriz(dimension);
printf("Llene la matriz B: \n");
LlenarMatriz(B, dimension);
printf("\n");

ImprimirMatriz(A, dimension);
printf("\n * \n");
ImprimirMatriz(B, dimension);
R=CrearMatriz(dimension);
MultiplicarMatriz(A, B, R, dimension);
printf("\n");
printf("Resultado: \n");
ImprimirMatriz(R, dimension);
}

int** CrearMatriz(int dimension){
    int **M;
    M=malloc(dimension*sizeof(int*));
    for(int i=0; i<dimension; i++){
        M[i]=malloc(dimension*sizeof(int));
    }
    return M;
}

void LlenarMatriz(int **M, int dimension){
    for(int i=0; i<dimension;i++){
        for(int j=0; j<dimension; j++){
            scanf("%d", &M[i][j]);
        }
    }
}

void ImprimirMatriz(int** M, int dimension){
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            printf("%d\t",M[i][j]);
        }
        printf("\n");
    }
}

void MultiplicarMatriz(int **M1, int **M2, int** R, int dimension){
int valor=0;
for(int i=0; i<dimension; i++){
    for(int j=0; j<dimension; j++){
        for(int k=0; k<dimension; k++){
            valor= valor + M1[i][k]*M2[k][j];
        }
        R[i][j]=valor;
        valor=0;
    }
}
}
