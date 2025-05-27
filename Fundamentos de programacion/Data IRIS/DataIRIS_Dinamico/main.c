/*
13/12/2024
Esta practica consiste en utilizar el metodo K-means para clasificar datos con ciertas
caracteristicas.
*/
//NOTA: analizar el comportamiento de la funcion ASIGNARCLASE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERROR 0.1

typedef struct Punto{
    float* Comp;
    int Clase; //Primera: 1; Segunda: 2; Tercera: 3;...
} Punto;

typedef struct Centros{
    Punto* Centro;
    Punto* CentroOld;
    //No olvidar rellenar este arreglo
    int* Clase;
    float dismin;//No es una propiedad de la clase, solo es una variable que almacena una distancia para ser comparada posteriormente
} Centros;

typedef struct DIris{
    Punto* Puntos;
} DIris;

void InicializarDataIris(DIris* DI, Centros* Cen);//Deposita los datos del archivo DATA_IRIS en el programa
void InicializarCentros(DIris* DI, Centros* Cen);//Escoge aleatoriamente n puntos como centros
float CalcularDistancia(DIris* DI, Centros* Cen, int indiceP, int indiceC);//Neta?.. Calcula la distancia entre dos puntos de n componentes
void IteradorClase(DIris* DI, Centros* Cen);//Se encarga de repetir el proceso de asignar clase y actualizar los centros hasta que los cambios de los mismos sean MINIMOS
void AsignarClase(DIris* DI, Centros* Cen);//Asigna una clase de acuerdo a la distancia de los centros
void ActualizarCentro(DIris* DI, Centros* Cen, int indiceC);//Actualiza un centro de acuerdo al promeddio de cada componente de los puntos que pertenecen a dicha clase
void ImprimirDataIris(DIris* DI);//Imprime los datos con su respectiva clasificacion en DATA_CLASIFICADA

int iteracionesfinales;
int Numpuntos, Numcentros, Numcomponentes;

int main(){
    DIris DI;
    Centros Centros;

    InicializarDataIris(&DI, &Centros);
    InicializarCentros(&DI, &Centros);
    
    IteradorClase(&DI, &Centros);
    
    ImprimirDataIris(&DI);
    return 0;
}

void InicializarDataIris(DIris* DI, Centros* Cen){
    //NOTA: Todos los printf comentados son inecesarios para la salida del archivo
    //printf("\nCantidad de puntos:");
    scanf("%d", &Numpuntos);
    //printf("\nCantidad de componentes:");
    scanf("%d", &Numcomponentes);
    //printf("\nCantidad de centros:");
    scanf("%d", &Numcentros);
    DI->Puntos=malloc(Numpuntos*sizeof(Punto));
    for(int i=0; i<Numpuntos; i++){
        DI->Puntos[i].Comp=malloc(Numcomponentes*sizeof(float));
    }
    for(int i=0; i<Numpuntos; i++){
        //printf("\nPunto %d:", i+1);
        for(int j=0; j<Numcomponentes;j++){
            //printf("\nComponente %d:", j+1);
            scanf("%f",&DI->Puntos[i].Comp[j]);
        }
    }
}

void InicializarCentros(DIris* DI, Centros* Cen){
    int numerocurioso;
    Cen->Centro=malloc(Numcentros*sizeof(Punto));
    Cen->CentroOld=malloc(Numcentros*sizeof(Punto));
    Cen->Clase=malloc(Numcentros*sizeof(int));
    for(int i=0; i<Numcentros; i++){
        Cen->Centro[i].Comp=malloc(Numcomponentes*sizeof(float));
        Cen->CentroOld[i].Comp=malloc(Numcomponentes*sizeof(float));
        Cen->Clase[i]=i+1;
    }
    for(int i=0; i<Numcentros; i++){
        numerocurioso= (0 + rand()%(Numpuntos-0+1))-1; //Escoge un numero random entre el 1 y el 150 (0-149)
        for(int j=0; j<Numcomponentes;j++){
            Cen->Centro[i].Comp[j]=DI->Puntos[numerocurioso].Comp[j];
        }
        DI->Puntos[numerocurioso].Clase=-1;
    }

}

float CalcularDistancia(DIris* DI, Centros* Cen, int indiceP, int indiceC){
    float distancia=0;
    for(int i=0; i<Numcomponentes; i++){
        distancia=pow(Cen->Centro[indiceC].Comp[i] - DI->Puntos[indiceP].Comp[i], 2)+distancia;
    }
    distancia=sqrt(distancia);
    return distancia;
}

void AsignarClase(DIris* DI, Centros* Cen){
    Cen->dismin=0;
    for(int i=0; i<Numpuntos;i++){
        if(DI->Puntos[i].Clase!=-1){
            Cen->dismin=CalcularDistancia(DI, Cen, i, 0);
            DI->Puntos[i].Clase=Cen->Clase[0];
            for(int j=1; j<Numcentros; j++){
            //printf("\n%.2f",CalcularDistancia(DI, Cen, i, j));
            if(Cen->dismin > CalcularDistancia(DI, Cen, i, j)){
                Cen->dismin=CalcularDistancia(DI, Cen, i, j);
                DI->Puntos[i].Clase=Cen->Clase[j];
            }
            }
        } else {
            DI->Puntos[i].Clase=0;
        }
        //printf("\t%d",DI->Puntos[i].Clase);
    }
}

void ActualizarCentro(DIris* DI, Centros* Cen, int indiceC){
    int h=0;//Se encarga de guardar el numero de datos recorridos dde una clase
    for(int j=0; j<Numcomponentes; j++){
        Cen->CentroOld[indiceC].Comp[j]=Cen->Centro[indiceC].Comp[j];//Se copia la componente a la de un centro anterior
        Cen->Centro[indiceC].Comp[j]=0;//Se resetan la componentes de los centros
        for(int k=0; k<Numpuntos; k++){
            if(DI->Puntos[k].Clase == Cen->Clase[indiceC]){
                h++;
                Cen->Centro[indiceC].Comp[j]=DI->Puntos[k].Comp[j] + Cen->Centro[indiceC].Comp[j];
            }
        }
        Cen->Centro[indiceC].Comp[j]= Cen->Centro[indiceC].Comp[j]/h;
        h=0;
    }
    //printf("\nCOld%d: %.3f,%.3f,%.3f,%.3f\n", indiceC+1, Cen->CentroOld[indiceC].Comp[0], Cen->CentroOld[indiceC].Comp[1], Cen->CentroOld[indiceC].Comp[2], Cen->CentroOld[indiceC].Comp[3]);
    //printf("\nC%d: %.3f,%.3f,%.3f,%.3f\n", indiceC+1, Cen->Centro[indiceC].Comp[0], Cen->Centro[indiceC].Comp[1], Cen->Centro[indiceC].Comp[2], Cen->Centro[indiceC].Comp[3]);
}

void IteradorClase(DIris* DI, Centros* Cen){
    int AcumCentro=0;//Esta variable se encarga de acumular los puntos que se obtienen cuando la diferencia entre un centro viejo y nuevo sea MINIMA 
    int AcumComp=0;//Lo mismo pero para cada componente, es decir, si la diferenica es MINIMA entre las componentes del nuevo y viejo centro, entonces la variable de arriba aumenta su valor
    do{
        AcumCentro=0;
        AsignarClase(DI, Cen);
        for(int i=0; i<Numcentros; i++){
            ActualizarCentro(DI, Cen, i);
            for(int j=0; j<Numcomponentes; j++){
                if(0<=(Cen->CentroOld[i].Comp[j] - Cen->Centro[i].Comp[j]) && (Cen->CentroOld[i].Comp[j] - Cen->Centro[i].Comp[j])<=ERROR){
                    AcumComp++;
                }
            }
            if(AcumComp==Numcomponentes){
                AcumCentro++;
            }
            AcumComp=0;
        }
        iteracionesfinales++;
    }while(AcumCentro!=Numcentros);
}

void ImprimirDataIris(DIris* DI){
    for(int i=0; i<Numpuntos; i++){
        printf("P%d: [", i+1);
        for(int j=0; j<Numcomponentes;j++){
            printf("%.1f, ", DI->Puntos[i].Comp[j]);
            if(j==Numcomponentes-1){
                printf("%.1f]", DI->Puntos[i].Comp[j]);
            }
        }
        printf(" Clase: %d\n", DI->Puntos[i].Clase);
    }
    printf("\nTotal de iteraciones: %d", iteracionesfinales);
    iteracionesfinales=0;
}