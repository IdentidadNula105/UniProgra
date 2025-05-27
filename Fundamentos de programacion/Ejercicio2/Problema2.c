#include  <stdio.h>
/*
Dada una lista de numeros, se determina cuantos son pares, la suma de los impares y el numero mas pequeno
*/
int main (){
    int n=0;
    int valor=0;
    int a=0;
    int b=0;
    int c=0;
    int i=0;

    printf("Ingrese la cantidad de numeros a analizar: ");
    scanf("%d", &n);
    while(i<n){
        printf("n%d", i+1);
        scanf("%d", &valor);
        if(valor%2==0){
            a=a+1;
        }else{
            b=b+valor;
        }
        if(i<1){
            c=valor;
        }else{
            if(valor<c){
                c=valor;
            }
        }
        i=i+1;
     }
    printf("%d %d %d", a, b, c);
    return 0;
}