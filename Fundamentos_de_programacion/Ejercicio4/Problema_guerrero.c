#include <stdio.h>
#define MAX 1000
//Concatena dos caracteres compuestos
int main (){
    char nombre1[MAX+1];
    int i=0;
    printf("Nombre1: ");
    scanf("%[^\n]", nombre1);
    //Debido a complicaciones por usar esta forma de escanear characteres compuestos con espacios, se tiene que limpiar el buffer para que el salto de liea no sea leido por el otro escaner
    //Obviamente, si solo fueran caracteres compuestos solo se necesitaria el modificador %s en cada escaner
    getchar();
    while (nombre1[i] != '\0'){
        i++;
    }

    printf("Nombre2: ");
    scanf("%[^\n]", &nombre1[i]);
    i=0;
    printf("%s", nombre1);
    /*
    while(nombre1[i] != '\0'){
        printf("%c", nombre1[i]);
        i++;
    }*/
    return 0;
}