#include <stdio.h>
#include <stdlib.h>
#include "arbbin.h"
#include "piladin.h"
#include "notainfpost.h"
#include "derivsimb.h"

int main(){
    char* expinc,*exp1, *res;
    NodoArb* exp2, *exp3;
    NodoL* p;
    //Se recibe la función
    CrearPila(&p);
    printf("\nf(x)=");
    scanf("%[^\n]", expinc);
    
    //Se convierte a notación postfija y después se construye el árbol
    exp1=Convertir_Lista_Cadena(PostFijo(expinc));    
    exp2=ConstruirArbolFuncion(exp1);

    //Se construye el árbol derivado, se simplifica y se convierte a cadena en notación infija
    Convertir_Arbol_Lista(SimplificarArbolFuncion(DerivarArbolFuncion(exp2)), &p);
    res=Convertir_Lista_Cadena(p);
    printf("f'(x)=");
    printf("%s", ((Expifj*)Infija(res)->dato)->exp);
    
    return 0;
}