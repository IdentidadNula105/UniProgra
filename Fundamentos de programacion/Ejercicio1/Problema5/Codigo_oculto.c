#include <stdio.h>
/*Nota: declarar un arreglo con una variable indefinida, provoca que este arreglo tenga mas espacio del necesario
y no es recomendable hacerlo.
*/
/*
Marca YES si el numero dado por el usuario esta en un arreglo de numeros dado por el mismo usuario (XD)
*/
int main(){
    int n=0;
    int clave=0;
    int i=0;
    int indicador=0;

    printf("Escriba la longitud de la secuencia: ");
    scanf("%d", &n);
    printf("Escriba la palabra clave: ");
    scanf("%d", &clave);
    int secuencia[n];
    while(i<n){
        printf("Numero %d: ", i+1);
        scanf("%d", &secuencia[i]);
        i++;
    }
    i=0;
    while(i<n){
        if(secuencia[i]==clave){
            printf("Yes");
            return 0;
        }
        i++;
    }
    printf("NO");
    return 0;
}