/*Diaz Amaro Josue Ramses 1CM3 10/11/2024
*/
/*Hola, de manera resumida los apuntadores son variables que guardan direcciones de memoria. Se usa * y & para 
obtener el valor almacenado en la direccion y obtener la direccion respectivamente.
*/
#include <stdio.h>
#include <stdlib.h>

void IntroduccionAp(int numero);
void ArreglosBig(int numero);
void FuncionTuneada(int a, int b, int *r1, int *r2);

int main(){
    int numero;
    int numero1;
    //IntroduccionAp(numero);
    //ArreglosBig(numero);

    /*Como hacer que una funcion pase dos valores
    FuncionTuneada(5,6,&numero,&numero1);
    printf("\nLa suma de 5 y 6 es: %d", numero);
    printf("\nLa resta entre 5 y 6 es: %d", numero1);*/


    return 0;
}
void FuncionTuneada(int a, int b, int *r1, int *r2){
    /*Los ultimos dos parametros son direcciones de memoria, entonces lo que hace esta funcion es modificar
    los valores que estan en dicha direccion.*/
    *r1=a+b;
    *r2=a-b;
}
void ArreglosBig(int numero){ 
    int *arreglotuneado;
    int tamano=1000000000;
    /*El parametro que recibe malloc son el numero de bytes que requerimos, entonces, ocupamos multiplicarlos
    por el numero de bytes que ocupa nuestro tipo de dato*/
    arreglotuneado=malloc(tamano*sizeof(int));

    if(arreglotuneado==0){
        printf("\nSolicitud denegada. P E N D E J O");
    }else{
        printf("\nSolicitud aceptada.");
        printf("\nDireccion donde inicia nuestra memoria fiada: %p", arreglotuneado);
        //tamano[i]=*(tamano+i), recuerda, un arreglo en si ya conlleva su direccion de memoria
        printf("\nIntrduzca el numero que quiera que este en la ultima posicion (%d) del arreglo: ", tamano-1);
        /*Al sumar 99999, no sumas dicho valor en bytes, si no el valor respectivo al tipo de dato, en este caso
        un 1 es igual a 4*/
        //Afortunadamente, como arreglo tuneado ya tiene una direccion de memoria, no es necesario poner &(*(...))
        scanf("%d", arreglotuneado+(tamano-1));
        printf("\nEn la posicion 100000 el numero es: %d", *(arreglotuneado+(tamano-1)));
    }
}
void IntroduccionAp(int numero){
    int *direccion;
    numero=3;
    direccion=&numero;
    printf("\nNumero tiene como valor: %d", numero);
    printf("\nSu direccion de memoria es: %p", &numero);
    printf("\nLa direccion guardada en direccion: %p", direccion);
    //Algo cool
    printf("\nEl valor 64 en hexadecimal es: %x", 64);
}