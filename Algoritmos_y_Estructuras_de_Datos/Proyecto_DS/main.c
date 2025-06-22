#include <stdio.h>
#include <stdlib.h>
#include "derivsimb.h"
#include "is.h"

int main(){
    char* funcion;
    printf("\nf(x)=");
    scanf("%[^\n]", funcion);
    if(!IsFuncionValida(funcion)){
        printf("\nFUNCION NO VALIDA");
    } else {
        printf("f'(x)=");
        printf("%s", Derivar(funcion));
    }
    return 0;
}