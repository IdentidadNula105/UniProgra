#include <stdio.h>
//Imprime al reves una frase
# define MAX 1000
int main(){
int i=0;
char nombre [MAX+1];
scanf("%[^\n]", &nombre);
while (nombre[i]!=0)
{
i++;
}
while (i>=0)
{
    printf("%c", nombre[i]);
    i--;
}
    return 0;
}