#include <stdio.h>
/*
Dado un conjunto de numeros por el usuario, se realiza el promedio de los tres numeros mas grandes
*/
int main(){
    int n=0;
    int i=0;
    int j=0;
    float promedio=0.0;
    int numero=0;
    // Variables para ir comparando los numeros remplazados con los otros numeros mayores restantes
    int nauxiliar=0;
    int nauxiliar2=0;
    //Para intercambiar entre dos numeros
    int auxiliar=0;
    //Mayor
    int numero1=0;
    //Intermedio
    int numero2=0;
    //Menor
    int numero3=0;

    printf("Ingrese la cantidad de numeros a analizar: ");
    scanf("%d", &n);

    while(i<n){
        printf("N%d: ",i+1);
        scanf("%d",&numero);
        //Asignamos los primeros 3
        if(i==0){
            numero1=numero;
        } else if(i==1){
            numero2=numero;
        } else if(i==2){
            numero3=numero;
            //Los ordenamos
            while(j<2){
                j=0;
                if(numero2>numero1){
                    auxiliar=numero1;
                    numero1=numero2;
                    numero2=auxiliar;
                    
                }else{
                    j=j+1;
                }
                if(numero3>numero2){
                    auxiliar=numero2;
                    numero2=numero3;
                    numero3=auxiliar;
                }else{
                    j=j+1;
                }
            }
        }else{
        //Conforme se ingresa el numero, se compara con los tres mayores y si dicho numero es mayor, remplaza al numero que esta comparando y este a su vez se almacena en otra variable para que este se compare con los otros numeros mayores y asi sucesivamente.
        if(numero>numero1){
            nauxiliar=numero1;
            numero1=numero;
            if(nauxiliar>numero2){
                nauxiliar2=numero2;
                numero2=nauxiliar;
                if(nauxiliar2>numero3){
                    numero3=nauxiliar2;
                }
                //Si llega hasta aqui, significa que el valor es menor a los tres mayores y por tanto se elimina
            }else if(nauxiliar>numero3){
                numero3=nauxiliar;
            }
        }else if(numero>numero2){
            nauxiliar=numero2;
            numero2=numero;
            if(nauxiliar>numero3){
                numero3=nauxiliar;
            }
        }else if(numero>numero3){
            numero3=numero;
        }
        }
        i=i+1;
    }
    //Se calcula el promedio insanamente
    promedio=(numero1+numero2+numero3)/3;
    //Por alguna extraña razon redondea el promedio
    printf("\n%.2f", promedio);
    return 0;
}