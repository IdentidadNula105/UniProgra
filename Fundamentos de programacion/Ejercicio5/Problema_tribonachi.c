#include <stdio.h>
#define LIMITE 1000000
//Realiza la serie tribonachi e imprime el numero de terminos que salieron
// n3, n2, n1
int main(){
    int n1=1;
    int n2=0;
    int n3=0;
    int r=0;
    int i=0;

    while (n1<LIMITE){
        printf("\n%d", n1);
        r=n1+n2+n3;
        n3=n2;
        n2=n1;
        n1=r;
        i++;
    }
    printf("\nTerminos: %d", i);
    return 0;
}