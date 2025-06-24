#include <stdio.h>
#include <stdlib.h>
#include "derivsimb.h"
#include "is.h"

int main(){
    char* funcion;
    
    printf("\nEscriba f(x)=");
    scanf("%[^\n]", funcion);
    if(!IsFuncionValida(funcion)){
        printf("\nFUNCION NO VALIDA");
    } else {
        printf("\nf'(x)=");
        printf("%s", Derivar(funcion));
    }
    return 0;
}

