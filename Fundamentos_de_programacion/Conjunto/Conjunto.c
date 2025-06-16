#include <stdio.h>
#include <stdlib.h>
#include "Conjunto.h"
//Nota: los return en los vacios son iguales de utiles que COE
void InicializarConjunto(conjunto *X){
(*X).size=0;
printf("\nEl conjunto se ha inicializado correctamente.");
return;
}
void AgregarElemento(conjunto *X, int e){
if((*X).size==MAX_SIZE){
printf("\nERROR agregarElemento(A,e), no hay espacio...");
exit(1);
}
//Otra forma de escribir (*c) ==c->
X->size++;
X->C[X->size-1]=e;
return;
}
void EliminarElemento(conjunto *X, int e){
//Busqueda
int b=-1;
for(int i=0;i<X->size && b!=i;i++){
if(X->C[i]==e){
    b=i;
}
}
//Checar
if(b==-1){
printf("El elemento no existe.");
exit(1);
}
//Eliminar el elemento (recorre los elementos)
for(int i=b; i<X->size-1;i++){
    X->C[i]=X->C[i+1];
}
X->size--;
}
int PerteneceElemento(conjunto *X, int e){
int i, b=-1, r;
for(i=0; i<X->size && b!=i;i++){
    if(X->C[i]==e){
        b=i;
    }
}
if(b==-1)
    r=1;
else
    r=0;
return r;
}
void ImprimeConjunto(conjunto *X){
char a=44;
printf("{");
for(int i=0; i<X->size;i++){
    if(i==X->size-1){
        a=0;
    }
    printf("%d%c",X->C[i],a);
}
printf("}");
}
int ElementoPrimo(int e){
    //1 no es primo y -1 es primo
    int z=-1;
    if(e==1){
        z=1;
    }else{
    for(int i=2; i<e;i++){
    if(e%i==0){
        z=1;
    }
    }
    }
    
    return z;
}