/*
23/05/2025
Como tarea, dado n vectores de k dimensiones, crear una base ortonormal
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float** crearMatriz(int numf, int numc);
void llenarMatriz(float** Matriz, int numf, int numc);
float prodPun(float** Matriz, int vind1, int vind2, int numc);
void impBase(float** Matriz, int numf, int numc);
void normBase(float** Matriz, int numf, int numc);
void GS(float** Matriz, int numf, int numc);

int main(){
    float** matriz;
    int n, k;
    printf("\nNumero de vectores: ");
    scanf("%d", &n);
    printf("\nNumero de componentes: ");
    scanf("%d", &k);
    matriz=crearMatriz(n, k);
    llenarMatriz(matriz, n, k);
    GS(matriz, n, k);
    normBase(matriz, n, k);
    impBase(matriz, n, k);
}

float** crearMatriz(int numf, int numc){
    float** m;
    m=(float**)malloc((2*numf)*sizeof(float*));//los vectores
    for(int i=0; i<2*numf; i++) m[i]=(float*)malloc(numc*sizeof(float));//las componentes de cada vector
    return m;
}

void llenarMatriz(float** Matriz, int numf, int numc){
    for(int i=0; i<numf; i++){
        for(int j=0; j<numc; j++){
            printf("U%d%d: ", i+1, j+1);
            scanf("%f", &Matriz[i][j]);
        }
    }
}

float prodPun(float** Matriz, int vind1, int vind2, int numc){
    float rs=0.0;
    for(int i=0; i<numc; i++) rs=rs+Matriz[vind1][i]*Matriz[vind2][i];//aij*bij
    return rs;
}

void impBase(float** Matriz, int numf, int numc){
    for(int i=numf; i<2*numf; i++){
        printf("\nV%d: (", i-numf+1);
        for(int j=0; j<numc; j++){
            printf("%.2f,", Matriz[i][j]);
        }
        printf(")");
    }
}

void normBase(float** Matriz, int numf, int numc){
    float sumcuad;
    float rs;
    for(int i=numf; i<2*numf; i++){
        for(int j=0; j<numc; j++) sumcuad=sumcuad+pow(Matriz[i][j], 2);
        rs=sqrt(sumcuad);
        for(int j=0; j<numc; j++) Matriz[i][j]=Matriz[i][j]/rs;
        sumcuad=0;
        rs=0;
    }
}

void GS(float** Matriz, int numf, int numc){
    float aux=0.0;
    for(int i=numf; i<2*numf; i++){
        for(int j=0; j<numc; j++){
            for(int c=0; c<i-numf; c++){
                aux=aux+prodPun(Matriz, i-numf, c+numf, numc)*Matriz[c+numf][j]/prodPun(Matriz, c+numf, c+numf, numc);
            }
            Matriz[i][j]=Matriz[i-numf][j]-aux;
            aux=0.0;
        }
    }
}