#include <stdio.h>
# define MAX 1000
//Determina la cantidad de vocales en un mensaje
int main (){
    int i = 0;
    int vocales = 0;
    char mensaje[MAX+1];

    //scanf("%s", & mensaje[0]);
    gets(&mensaje[0]);

    while( mensaje[i] !=0 ){
        if(mensaje[i] == 'a' || mensaje[i] == 'A'){
            vocales++;
        }
        if(mensaje[i] == 'e' || mensaje[i] == 'E'){
            vocales++;
        }
        if(mensaje[i] == 'i' || mensaje[i] == 'I'){
            vocales++;
        }
        if(mensaje[i] == 'o' || mensaje[i] == 'O'){
            vocales++;
        }
        if(mensaje[i] == 'u' || mensaje[i] == 'U'){
            vocales++;
        }
        i++;
    }
    printf("Vocales: %d", vocales);
    return 0;
}