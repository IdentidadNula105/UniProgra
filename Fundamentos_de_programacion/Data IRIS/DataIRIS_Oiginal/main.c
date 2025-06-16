/*10/12/2024
Esta practica consiste en utilizar el metodo K-means para clasificar datos con ciertas
caracteristicas.
*/
//NOTA: analizar el comportamiento de la funcion ASIGNARCLASE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define COMPONENTES 4
#define NUMDATOS 150
#define NUMCENTROS 3

typedef struct Punto{
    float Comp[COMPONENTES];
    int Clase; //Primera: 1; Segunda: 2; Tercera: 3;...
} Punto;

typedef struct Centros{
    Punto Centro[NUMCENTROS];
    Punto CentroOld[NUMCENTROS];
    int Clase[NUMCENTROS];
    float dismin;//No es una propiedad de la clase, solo es una variable que almacena la distancia para ser comparada posteriormente
} Centros;

typedef struct DIris{
    Punto Puntos[NUMDATOS];
} DIris;

void InicializarDataIris(DIris* DI);//Deposita los datos del archivo DATA_IRIS en el programa
void InicializarCentros(DIris* DI, Centros* Cen);//Escoge aleatoriamente n puntos como centros
float CalcularDistancia(DIris* DI, Centros* Cen, int indiceP, int indiceC);//Neta?.. Calcula la distancia entre dos puntos de n componentes
void IteradorClase(DIris* DI, Centros* Cen);//Se encarga de repetir el proceso de asignar clase y actualizar los centros hasta que los cambios de los mismos sean MINIMOS
void AsignarClase(DIris* DI, Centros* Cen);//Asigna una clase, funcion importante
void ActualizarCentro(DIris* DI, Centros* Cen, int indiceC);//Actualiza un centro de manera individual
void ImprimirDataIris(DIris* DI);//Imprime los datos con su respectiva clasificacion en DATA_CLASIFICADA

int iteracionesfinales=0;

int main(){
    DIris DI;
    Centros Centros;

    InicializarDataIris(&DI);
    InicializarCentros(&DI, &Centros);
    
    IteradorClase(&DI, &Centros);
    
    ImprimirDataIris(&DI);
    return 0;
}

//GENERALIZAR
void InicializarDataIris(DIris* DI){
    for(int i=0; i<NUMDATOS; i++){
        //printf("\nPunto %d: ", i+1); Para el archivo, no se requiere
        scanf("%f\t%f\t%f\t%f",&DI->Puntos[i].Comp[0], &DI->Puntos[i].Comp[1], &DI->Puntos[i].Comp[2], &DI->Puntos[i].Comp[3]);
    }
}

void InicializarCentros(DIris* DI, Centros* Cen){
    int numerocurioso;
    for(int i=0; i<NUMCENTROS; i++){
        numerocurioso= (0 + rand()%(NUMDATOS-0+1))-1; //Escoge un numero random entre el 1 y el 150 (0-149)
        for(int j=0; j<COMPONENTES;j++){
            Cen->Centro[i].Comp[j]=DI->Puntos[numerocurioso].Comp[j];
        }
        DI->Puntos[numerocurioso].Clase=-1;
        Cen->Clase[i]=i+1;
    }

}

float CalcularDistancia(DIris* DI, Centros* Cen, int indiceP, int indiceC){
    float distancia=0;
    for(int i=0; i<COMPONENTES; i++){
        distancia=pow(Cen->Centro[indiceC].Comp[i] - DI->Puntos[indiceP].Comp[i], 2)+distancia;
    }
    distancia=sqrt(distancia);
    return distancia;
}

void AsignarClase(DIris* DI, Centros* Cen){
    Cen->dismin=0;
    for(int i=0; i<NUMDATOS;i++){
        if(DI->Puntos[i].Clase!=-1){
            Cen->dismin=CalcularDistancia(DI, Cen, i, 0);
            DI->Puntos[i].Clase=Cen->Clase[0];
            for(int j=1; j<NUMCENTROS; j++){
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
    int h=0;
    for(int j=0; j<COMPONENTES; j++){
        Cen->CentroOld[indiceC].Comp[j]=Cen->Centro[indiceC].Comp[j];//Se copia la componente a la de un centro anterior
        Cen->Centro[indiceC].Comp[j]=0;//Se resetan la componentes de los centros
        for(int k=0; k<NUMDATOS; k++){
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
    int AcumComp=0;//Lo mismo pero para cada componente, es decir, si la diferenica es MINIMA entre los componentes del nuevo y viejo centro, entonces la variable de arriba aumenta su valor
    do{
        AcumCentro=0;
        AsignarClase(DI, Cen);
        for(int i=0; i<NUMCENTROS; i++){
            ActualizarCentro(DI, Cen, i);
            for(int j=0; j<COMPONENTES; j++){
                if(0<=(Cen->CentroOld[i].Comp[j] - Cen->Centro[i].Comp[j]) && (Cen->CentroOld[i].Comp[j] - Cen->Centro[i].Comp[j])<=0.1){
                    AcumComp++;
                }
            }
            if(AcumComp==COMPONENTES){
                AcumCentro++;
            }
            AcumComp=0;
        }
        //printf("\n%d", AcumCentro);
        //printf("\nC%d: %.1f,%.1f,%.1f,%.1f\n", 1, Cen->Centro[1].Comp[0], Cen->Centro[1].Comp[1], Cen->Centro[1].Comp[2], Cen->Centro[1].Comp[3]);
        iteracionesfinales++;
        //if(iteracionesfinales==2){
        //AcumCentro=NUMCENTROS;
        //}
    }while(AcumCentro!=NUMCENTROS);
}
//GENERALIZAR
void ImprimirDataIris(DIris* DI){
    for(int i=0; i<NUMDATOS; i++){
        printf("P%d: [%.1f\t%.1f\t%.1f\t%.1f] Clase: %d\n", i+1,DI->Puntos[i].Comp[0], DI->Puntos[i].Comp[1], DI->Puntos[i].Comp[2], DI->Puntos[i].Comp[3], DI->Puntos[i].Clase);
    }
    printf("\nTotal de iteraciones: %d", iteracionesfinales);
    iteracionesfinales=0;
}