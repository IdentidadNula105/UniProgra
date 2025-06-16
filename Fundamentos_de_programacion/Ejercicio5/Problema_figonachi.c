#include <stdio.h>
#define LIMITE 1000000
//la serie de fibonacci y cuantos terminos se imprimen
int main(){
    int n1=1;
    int n0=0;
    int r=0;
    int i=0;

    while(r<LIMITE){
        r=n1+n0;
        printf("\n%d", n1);
        n0=n1;
        n1=r;
        i++;
    }
    printf("\nTerminos impresos: %d", i);
    return 0;
}