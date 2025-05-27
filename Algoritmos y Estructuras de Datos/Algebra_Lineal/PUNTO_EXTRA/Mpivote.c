#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **InicM(int n);
double ***InicSubM(int a);//a es el numero de submatrices 2x2
void LlenaM(double **M, int n);
void LlenaSubM(double ***sM,double **M, int i, int j, int k);//k como numero de submatrices, i y j como las coordenadas en la matriz (n-1)(n-1)
void ImprimeM(double **M, int n);
void IntFilaM(double **M, int n, int i);//Intercambia la fila 0 por la fila i
double Pivotal(double **M, int n);

int iteracion;//ANULO CUALQUIER MALDICION

int main(){
    double **A;
    double detA;
    int n;
    printf("Ingrese el tamano de la matriz: ");
    scanf("%d", &n);

    A=InicM(n);
    LlenaM(A, n);

    printf("\n\nEl determinantes ingresado es: ");
    ImprimeM(A, n);
    
    iteracion=0;
    printf("\nEl determinante 2x2 final es: %.1f", Pivotal(A,n));
    return 0;
}

double **InicM(int n){
    double **matriz;
    matriz=(double**)malloc(n*sizeof(double*));
    for(int i=0; i<n; i++){
        matriz[i]=(double*)malloc(n*sizeof(double));
    }
    return matriz;
}

double ***InicSubM(int a){
    double ***submatriz;
    submatriz=(double***)malloc(a*sizeof(double**));
    for(int i=0; i<a; i++){
        submatriz[i]=(double**)malloc(2*sizeof(double*));
        for(int j=0; j<2; j++){
            submatriz[i][j]=(double*)malloc(2*sizeof(double));
        }
    }
    return submatriz;
}

void LlenaM(double **M, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("\nElemento (%d,%d): ", i, j);
            scanf("%lf", &M[i][j]);//XD
        }
    }
}

void LlenaSubM(double ***sM, double **M,  int i, int j, int k){
    sM[k][0][0]=M[0][0];
    sM[k][0][1]=M[0][1+j];
    sM[k][1][0]=M[1+i][0];
    sM[k][1][1]=M[1+i][1+j];
}

double Pivotal(double **M, int n){
    double **B;
    double ***subB;
    int fila, sig;//sig guarda el signo si es que se hace un intercambio de renglones
    sig=1;
    if(n==2) return M[0][0]*M[1][1]-M[1][0]*M[0][1];//Caso base
    
    B=InicM(n-1);//Guarda los resultados de los subdeterminantes 2x2
    subB=InicSubM(n);//submatriz por renglon, se recicla con la funcion LlenaSubM

    if(M[0][0]==0){
        while(M[fila][0]==0){
        fila++;
        }
        IntFilaM(M, n, fila);
        sig=-1; 
        printf("\nLa entrada m11 es cero, por lo que se intercambia la fila 1 con la fila %d, quedando: ", fila+1);
        ImprimeM(M, n);
    }
    printf("\n\nPaso %d: Se encuentra el subdeterminante M de %dx%d.", iteracion+1, n-1, n-1);
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1; j++){
            LlenaSubM(subB, M, i, j, j);
            B[i][j]=subB[j][0][0]*subB[j][1][1]-subB[j][1][0]*subB[j][0][1];//resultado de la submatriz
        }

        //Imprime las submatrices del renglon i
        for(int l=0; l<2; l++){
            printf("\n| ");
            for(int m=0; m<n-1; m++){
                printf("|%.1f  %.1f| ", subB[m][l][0], subB[m][l][1]);
            }
            printf("|");
        }
        printf("\n");
    }
    printf("\nSubdeterminante resultante:");
    ImprimeM(B, n-1);
    iteracion++;
    return sig*pow(1/M[0][0],n-2)*Pivotal(B, n-1);

}

void IntFilaM(double **M, int n, int i){
    double aux;
    for(int j=0; j<n; j++){
        aux=M[0][j];
        M[0][j]=M[i][j];
        M[i][j]=aux;
    }
}

void ImprimeM(double **M, int n){
    for(int i=0; i<n; i++){
        printf("\n|  ");
        for(int j=0; j<n; j++){
            printf("%.1f  ", M[i][j]);
        }
        printf("|");
    }
    printf("\n");
}
