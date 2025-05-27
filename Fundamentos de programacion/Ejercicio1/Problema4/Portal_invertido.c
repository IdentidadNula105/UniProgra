#include <stdio.h>
int main(){
    int n=0;
    int i=0;
    printf("Introduzca el numero de runas a invertir: ");
    scanf("%d", &n);

    int runas[n];
    while(i<n){
        printf("Introduzca la runa %d: ", i+1);
        scanf("%d", &runas[i]);
        i++;
    }
    i=0;
    while(i<n){
        printf("%d ", runas[n-1-i]);
        i++;
    }
    return 0;
}