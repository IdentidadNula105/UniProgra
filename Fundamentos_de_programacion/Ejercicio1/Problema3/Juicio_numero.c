#include <stdio.h>
/*Determina si un numero es positivo, negativo o es igual a cero*/
int main(){
    int i=0;
    int n=0;
    int agente=0;
    int heroes=0;
    int villanos=0;
    int neutrales=0;

    printf("Coloque el numero de agentes a enjuiciar: ");
    scanf("%d", &n);

    while(i<n){
        printf("Agente %d: ", i+1);
        scanf("%d", &agente);
        if(agente>0){
            heroes++;
        }else if(agente<0){
            villanos++;
        }else{
            neutrales++;
        }
        i++;
    }
    printf("%d %d %d", heroes, villanos, neutrales);
    return 0;
}