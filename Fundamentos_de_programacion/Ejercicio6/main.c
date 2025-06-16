/*Este es un ejercicio en donde se multiplican dos matrices cuadradas y apartir de dos vectores (de las mimas dimensiones) se realiza su producto punto y producto cruz*/
#include <stdio.h>
#include <stdlib.h>

int* crearVector(int n);
void llenarVector(int* vector, int n);
int productoPunto(int* vectorA, int* vectorB, int n);
void productoCruz(int* vectorA, int* vectorB, int* vectorR, int n);
void imprimirProductoPunto(int resultado);
void imprimirProductoCruz(int* vectorR, int n);

int main() {
    int n;

    printf("Introduce el numero de componentes de los vectores: ");
    scanf("%d", &n);

    int* vectorA = crearVector(n);
    int* vectorB = crearVector(n);
    int* vectorR = crearVector(n);

    printf("\nLlena el vector A\n");
    llenarVector(vectorA, n);

    printf("\nLlena el vector B\n");
    llenarVector(vectorB, n);

    int resultado = productoPunto(vectorA, vectorB, n);
    imprimirProductoPunto(resultado);

    productoCruz(vectorA, vectorB, vectorR, n);
    imprimirProductoCruz(vectorR, n);

    return 0;
}

int* crearVector(int n) {
    int* vector = malloc(n * sizeof(int));
    return vector;
}

void llenarVector(int* vector, int n) {
    printf("Introduce los %d elementos del vector:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Componente %d: ", i + 1);
        scanf("%d", &vector[i]);
    }
}

int productoPunto(int* vectorA, int* vectorB, int n) {
    int resultado = 0;
    for (int i = 0; i < n; i++) {
        resultado += vectorA[i] * vectorB[i];
    }
    return resultado;
}

void productoCruz(int* vectorA, int* vectorB, int* vectorR, int n){

for(int i=0; i<n; i++){
    for(int j=0; j<n;j++){
        if(j==i-1){
            vectorR[j]= vectorA[j]*vectorB[j+2]-vectorB[j]*vectorA[j+2];
        }else if(j==i){
        
        }else if(j==n-1){
            vectorR[j]= vectorA[j]*vectorB[0]-vectorB[j]*vectorA[0];
        }else{
            vectorR[j]= vectorA[j]*vectorB[j+1]-vectorB[j]*vectorA[j+1];
        }
    }
}
}

void imprimirProductoCruz(int* vectorR, int n) {
    printf("\nR=[");
    for(int i=0; i<n;i++){
        printf("%d, ", vectorR[i]);
        /*
        if(i==n-1){
            printf("%d", vectorR[i]);
        }else{
            printf("%d, ", vectorR[i]);
        }*/
    }
    printf("]");
}

void imprimirProductoPunto(int resultado) {
    printf("\nEl producto punto de los dos vectores es: %d\n", resultado);
}
