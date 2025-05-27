#include <stdio.h>//print y scan
#include <math.h>//pow, sqrt
#include <stdlib.h>//Apuntadores
#include <string.h>//Manejo de cadenas
#define MAX 50

int main(){
    char palabra1[MAX+1];
    char palabra2[MAX+1];
    char palabra3[MAX+1];
    int tam1=0, tam2=0; 
    int letrep=0;
    int* bandera;
    scanf("%s", palabra1);
    scanf("%s", palabra2);

    while(palabra2[tam1]!='\0'){
        tam1++;
    }
    while(palabra1[tam2]!='\0'){
        tam2++;
    }
    
    for(int i=0; i<tam2; i++){
        palabra3[i]=palabra2[i];
    }

    for(int i=0; i<tam1; i++){
        for(int j=0; j<tam2; j++){
            if(palabra1[i]==palabra2[j]){
                letrep++;
                palabra2[j]=' ';
            }
        }
    }

    printf("\n%s %s %d", palabra1, palabra3, letrep);
    return 0;
}