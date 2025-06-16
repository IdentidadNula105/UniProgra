#include <stdio.h>
#define MAX 1000
//Determine la cantidad de palabras que hay en una cadena compuesta
int main(){
    char libro[MAX+1];
    int npalabra=0;
    int i=0;
    int k=1;
    printf("Escriba el contenido del 'Libro': ");
    scanf("%[^\n]", libro);
    
    while (libro[i] !='\0'){
        /*
        Usaremos una variable bandera, la cual inicialmente esta inciada en 1. Si esta variable es 1 y el caracter es 
        una letra, suma un punto a npalabras y se desactiva la bandera, lo que provoca que si el siguiente caracter es letra 
        no se sume un punto, porque la bandera no esta activa y esta solo se vuelve a activar si el siguiente
        caracter es un espacio.
        */
        if(libro[i] != 32 && k==1){
            npalabra++;
            k=0;
        }else if(libro[i]==32){
            k=1;
        }
        i++;
    }
    printf("%d", npalabra);
    return 0;
}