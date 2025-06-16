/*
A partir de una cadena, obtener sus prefijos, subfijos y subcadenas
*/
#include <stdio.h>
#define TAM_MAX 100
int main(){
    char palabra[TAM_MAX+1];
    int tamanio=0;
    int i=0;
    int j=0;
    int indice=0;
    //Escaneamos la palabra
    printf("Escriba la palabra: ");
    scanf("%s", & palabra[0] );
    printf("\nPrefijos:\n");
    while(palabra[tamanio] != '\0'){
        tamanio++;
    }

    //Copiamos el tamaño de la palabra
    indice=tamanio;
    printf("%d", indice);

    //Este while se encarga imprimir cada palabra con su modificacion
    while(i<indice){
        //Este while se encargara de imprimir la palabra modificada
        while(j<tamanio){
            printf("%c",palabra[j]);
            j++;
        }
        j=0;
        tamanio=tamanio-1;
        printf("\n");
        i++;
    }
    i=0;
    j=0;
    tamanio=indice;
    printf("\nSubfijos:\n");
    while(i<indice){
        while(j<tamanio){
            printf("%c", palabra[i+j]);
            j++;
        }
        j=0;
        i++;
        tamanio--;
        printf("\n");
    }
}