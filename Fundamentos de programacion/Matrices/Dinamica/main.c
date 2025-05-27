//Realizado el 22/22/2024, este es un ejemplo de como codificar el main. No lo olvides, facil de entender y autodocumentado
#include <stdio.h>
#include <stdlib.h>

/*
Mucho texto...
Bueno, en este caso usaremos dobles apuntadores, los cuales guardan direcciones de otros apuntadores
Para hacer matrices dinamicas, primero crearemos un doble apuntador, el cual almacena como un arreglo las dirreciones
de los otros apuntadores. Estos apuntadores, a su vez, almacena la direccion de memoria que estamos solicitando en
forma de filas de cuadros [][][][]. Entonces, en resumidas cuentas guardamos la posición de las filas generadas
por la memoria prestada. 
*(A+i)=A[]
*(*(A+FILAS)+COLUMNAS)=A[FILAS][COLUMNAS]
*/
void LlenaMatriz(int **M, int fila, int columna);
void SumaMatriz(int **M1, int **M2, int **R, int fila, int columna); //R guarda el resultado
void ImprimeMatriz(int **M, int fila, int columna);
int** CrearMatriz(int fila, int columna);


int main(){
    
    int fila, columna;
    //Las matrices se acostumbran a ser nombradas con mayuscula y una sola letra
    int **M1, **M2, **R;

    printf("Numero de filas:\n");
    scanf("%d", &fila);
    printf("Numero de columna:\n");
    scanf("%d", &columna);

    M1=CrearMatriz(fila, columna);
    M2=CrearMatriz(fila, columna);
    R=CrearMatriz(fila, columna);

    printf("Llene la matriz A:\n");
    LlenaMatriz(M1, fila, columna);
    ImprimeMatriz(M1, fila, columna);
    printf("\n");

    printf("\nLlene la matriz B:\n");
    LlenaMatriz(M2, fila, columna);  
    ImprimeMatriz(M2, fila, columna);
    printf("\n");

    printf("\nResultado de la suma de A y B:\n");
    SumaMatriz(M1, M2, R, fila, columna);
    ImprimeMatriz(R, fila, columna);

    while(1){

    }
    return 0;
}

void LlenaMatriz(int **M, int fila, int columna){
    int i,j;
    for(i=0; i<fila; i++){
        for(j=0; j<columna; j++){
            scanf("%d", &M[i][j]);
        }
    }
    return;
}

void SumaMatriz(int **M1, int **M2, int **R, int fila, int columna){
    int i,j;
    for(i=0; i<fila; i++){
        for(j=0; j<columna; j++){
            R[i][j]=M1[i][j]+M2[i][j];
        }
    }
}

void ImprimeMatriz(int **M, int fila, int columna){
    int i,j;
    for(i=0; i<fila; i++){
        printf("\n");
        for(j=0; j<columna; j++){
            printf("%d\t", M[i][j]);//\t da un tab en consola
        }
    }
}

int** CrearMatriz(int fila, int columna){
    int **M;
    int i;
    M=malloc(fila*sizeof(int*));
    for(i=0; i<fila; i++){
        M[i]=malloc(columna*sizeof(int));
    }
    return M;
}
