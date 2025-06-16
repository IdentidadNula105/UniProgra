#include<stdio.h>
#define MAX 1000
//Determina si una palabra es palindromo
//La palabra puede tener mayusculas, minusculas o de plano con varios espacios

int main(){
    char nombre[MAX+1];
    int i=0;
    int j=0;
    int tamano=0;
    scanf("%[^\n]", nombre[0]);

    //Se recorre toda la frase
    while(nombre[i] != '\0'){
        //Repite el proceso de recorrer letras hasta que la posicion actual sea diferente de espacio
        while(nombre[i] == 32){
            j=i;
            //Recorre las letras hasta que tope con el final
            while(nombre[j] != '\0'){
            nombre[j]=nombre[j+1];
            j++;
            }
            j=0;
        }
        //Convierte las mayusculas en minusculas
        if(64<nombre[i]<91){
            nombre[i]=nombre[i]+32;
        }
        i++;
        tamano++;
    }
    i=0; //Derecha a izquierda
    j=tamano-1; // Izquierda a derecha
    while(i<tamano && j>=0 && nombre[i] == nombre[j]){
        i++;
        j--;
    }
    if(i==tamano){
        printf("SI");
    } else {
        printf("NO");
    }
    return 0;
}
