/*
Díaz Amaro Josué Ramsés
26/02/2025
Recopiatorio de algoritmos recursivos

Pasos para hacer una función recursiva:
1. Plantear el problema de forma recursiva (xd)
2. Detener la recursividad (caso base)
3. Llamada recursiva (tender al caso base)
4. Probar función recursiva (arbol de llamadas)
*/

#include <stdio.h>
void ArrayInv(int a[], int n, int v);
int Pasc(int m, int n);//Dada una coordenada del triangulo de pascal (m=fila y n=columna), regresa el valor que contiene
int Pot(int a, int b);
int SumArray(int a[], int n);
int SumCon(int n);
int fact(int n);
int MaxArray(int n, int a[]);

int main()
{
    int a[5] = {11,-2,36,40,-51};
    int b[5] = {1, 2, 3, 4, 5};
    int c[4] = {1, 2, 3, 4};
    int r=0;
    
    r=fact(5);
    r=SumCon(100);
    r=SumArray(a, 5);
    r=Pot(2,4);
    r=MaxArray(5, a);
    r=Pasc(5,3);
    ArrayInv(c, 4, 0);
    for(int i=0; i<4; i++){
        printf("%d\n", c[i]);
    }

    
    printf("%d\n",r);
    
    return 0;
}

void ArrayInv(int a[], int n, int v){
    if(v>n) return;
    int aux=0;
    aux=a[v];
    a[v]=a[n-1];
    a[n-1]=aux;
    return ArrayInv(a, n-1, v+1);

}

int Pasc(int m, int n){
    if(n==0 || m==n) return 1;
    return Pasc(m-1, n-1)+Pasc(m-1, n);
}

int Pot(int a, int b){
    if(b==0){
        return 1;
    }
    return a*Pot(a,b-1);
}

int SumArray(int a[], int n){
    if(n==0){
        return 0;
    }
    return a[n-1]+SumArray(a, n-1);
}

int SumCon(int n){
    if(n==0){
        return 0;
    }
    return n+SumCon(n-1);
}

int fact(int n){
    if(n==0){
        return 1;
    }
    return n*fact(n-1);
}

int MaxArray(int n, int a[]){
    if(n==0){
        return a[0];
    }
    if(a[n-1]<MaxArray(n-1, a)){
        return MaxArray(n-1, a);
    }else{
        return a[n-1];
    }
}