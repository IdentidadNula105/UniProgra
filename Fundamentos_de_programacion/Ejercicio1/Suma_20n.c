#include <stdio.h>

int main() {
    int i, suma, numero;
    i=0;
    suma=0;
    numero=0;
    while(i<20){
    printf("\nEscribe el numero %d ", i+1);
    scanf("\n%d", &numero);
    suma= suma + numero;
    i=i+1;
    }
    printf("La suma total es: %d", suma);
    return 0;
}