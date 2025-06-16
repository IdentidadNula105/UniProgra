/*
02/01/2025 (FELIZ AÑO NUEVO)
Diaz Amaro Josue Ramses 1CM3
En esta tarea se desarrolla un algoritmo que emplea el metodo Gauss Jordan para resolver sistemas de ecuaciones de
nxn.

Punto[fila][columna]
DiagonaldelPunto[columna][columna]
Numero total de columnas=tam_matriz+1
Numero total de filas=tam_matriz
Si sin_sistema==-1, el sistema no tiene solucion
Si infinitas_soluciones==-1, el sistema tiene soluciones infinitas
Diagonal: la diagonal de la matriz sin contar la columna que alberga los resultados de las ecuaciones

Nota final: por dios, si no fuera por que no me gusta dejar las cosas a medias, no le hubiera dedicado mas de 7h
*/

#include <stdio.h>
#include <stdlib.h>

float** InicializarSistema();//Crea la matriz doble y solicita los datos para sistema
void RecorrerSistema(float** Sistema);//Convierte la matriz a una matriz identiddad
void AcomodarSistema(float** Sistema, int elediagonal);//Asegura que los elementos de la diagonal no sean cero, intercambiando las filas donde se encuentra por una donde en la misma columna no haya un cero
void ValorCero(float** Sistema, int fila, int columna);//Iguala a cero un punto de la matriz, realizando los cambios necesarios a la fila que pertenece
void IntercambiarFila(float** Sistema, int fila1, int fila2);//Intercambia filas, donde la fila 1 pasa a la fila 2 y viceversa
void SimplificarSistema(float** Sistema);//Divide a los elementos de la columna de resultados por el valor de la diagonal al que pertenecen
void ImprimirMatriz(float** Sistema);//Oye, aca entre nosotros, sabes lo que es imprimir?
void ImprimirResultado(float** Sistema);//Imprime el valor de las variables del sistema

int tam_matriz;
int sin_solucion;
int infinitas_soluciones;

int main(){
    float** Sistema; 

    Sistema=InicializarSistema(Sistema);
    ImprimirMatriz(Sistema);
    RecorrerSistema(Sistema);
    SimplificarSistema(Sistema);
    if(infinitas_soluciones==-1){
        printf("\nEl sistema tiene infinitas soluciones");
    }else if(sin_solucion==-1){
        printf("\nEl sistema no tiene solucion jaja");
    }else{
        ImprimirMatriz(Sistema);
        ImprimirResultado(Sistema);
    }
    return 0;

}

float** InicializarSistema(){
    float** Sistema;
    //printf("\nIngrese el numero de variables del sistema: ");
    scanf("%d", &tam_matriz);
    Sistema=malloc(tam_matriz*sizeof(float*));
    for(int i=0; i<(tam_matriz+1);i++){
        Sistema[i]=malloc((tam_matriz+1)*sizeof(float));
    }
    for(int i=0; i<tam_matriz;i++){
        for(int j=0; j<(tam_matriz+1); j++){
            if(j==tam_matriz){
                //printf("\nResultado de la ecuacion %d: ", i+1);
            }else{
                //printf("\nCoeficiente de la variable %d de la ecuacion %d: ", j+1, i+1);
            }
            scanf("%f", &Sistema[i][j]);
        }
    }
    return Sistema;
}

void AcomodarSistema(float** Sistema, int elediagonal){
    int k=0;
    //La segunda condicion del while evita que se salga del numero de filas totales que existen
    while(Sistema[k+elediagonal][elediagonal]==0 && (k+elediagonal)<tam_matriz){
    k++;
    }
    if(k+elediagonal!=tam_matriz){
        IntercambiarFila(Sistema, elediagonal, k+elediagonal);
    }
    k=0;
}

void RecorrerSistema(float** Sistema){
    for(int i=0; i<tam_matriz; i++){
        if(i!=tam_matriz-1){
            if(Sistema[i][i]==0){
                AcomodarSistema(Sistema, i);
            }
        }
    }

    //columna
    for(int i=0; i<tam_matriz; i++){
        //fila
        for(int j=0; j<tam_matriz; j++){
            if(j!=i){
                ValorCero(Sistema, j, i);
            }
        }
    }
}

void ValorCero(float** Sistema, int fila, int columna){
    float c;
    int acumpunt=0;
    c=Sistema[fila][columna]/Sistema[columna][columna];

    //Esto valida si el sistema no tiene solucion
    if(Sistema[fila][columna]!=0 && Sistema[columna][columna]==0){
        sin_solucion=-1;
    }

    for(int i=0; i<(tam_matriz+1);i++){
        Sistema[fila][i]=Sistema[fila][i]-c*Sistema[columna][i];
        //Esto valida si tiene soluciones infinitas
        if(Sistema[fila][i]==0){
            acumpunt++;
        }
    }

    if(acumpunt==tam_matriz+1){
        infinitas_soluciones=-1;
    }
}

void IntercambiarFila(float** Sistema, int fila1, int fila2){
    float varaux;
    for(int i=0; i<tam_matriz+1; i++){
        varaux=Sistema[fila2][i];
        Sistema[fila2][i]=Sistema[fila1][i];
        Sistema[fila1][i]=varaux;
    }
}

void SimplificarSistema(float** Sistema){
    //fila
    for(int i=0; i<tam_matriz;i++){
        Sistema[i][tam_matriz]=Sistema[i][tam_matriz]/Sistema[i][i];
        Sistema[i][i]=Sistema[i][i]/Sistema[i][i];
    }
}

void ImprimirMatriz(float** Sistema){
    printf("\n\n");
    for(int i=0; i<tam_matriz; i++){
        for(int j=0; j<(tam_matriz+1);j++){
            if(Sistema[i][j]==-0.0){
                Sistema[i][j]==0.0;
            }
            printf("%.1f\t", Sistema[i][j]);
        }
        printf("\n");
    }
}

void ImprimirResultado(float** Sistema){
    for(int i=0; i<tam_matriz; i++){
        printf("\nValor de v%d: %.1f", i+1, Sistema[i][tam_matriz]);
    }
}