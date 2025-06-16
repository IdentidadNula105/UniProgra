/*Realizar menú de los diferentes metodos de la libreria y a su vez usando funciones.*/
#include <stdio.h>
#include <string.h>
#define MAX 1000

void Menu();
int Continuar();
void LongitudCadena();
void CopiarCadena();
void CompararCadena();
void ConcatenarCadena();
void BuscarCaracterCadena();
void CadenaEnCadena();

int main(){
    Menu();
    return 0;
}

void Menu(){
char respuesta=0;
int opcion=0;
do{
printf("---- Elija la opcion que desee realizar ----\n");
printf("Condiciones: frases de igual o menor de 1000 caracteres\n\n");
printf("1. Longitud de cadena (strlen)\n");
printf("2. Copiar cadenas (strcpy)\n");
printf("3. Comparar cadenas (strcmp)\n");
printf("4. Concatenar cadeanas (strcat)\n");
printf("5. Buscar caracter en una cadena (strchr)\n");
printf("6. Buscar cadena en otra cadena (strstr)\n");
printf("7. Salir del menu\n");

printf("Escriba del 1-7: ");
scanf("%d", &opcion);
getchar();
switch(opcion){
    case 1:
    LongitudCadena();
    opcion=Continuar();
    break;

    case 2:
    CopiarCadena();
    opcion=Continuar();
    break;

    case 3:
    CompararCadena();
    opcion=Continuar();
    break;

    case 4:
    ConcatenarCadena();
    opcion=Continuar();
    break;

    case 5:
    BuscarCaracterCadena();
    opcion=Continuar();
    break;

    case 6:
    CadenaEnCadena();
    opcion=Continuar();
    break;

    case 7:
    printf("Saliendo...\n");
    break;

    default:
    printf("Nou nou, opcion incorrecta\n");
    break;
}
} while (opcion != 7);
}

int Continuar(){
char respuesta=0;
do{
printf("Desea regresar al menu? s/n\n");
scanf("%c", &respuesta);
if(64<respuesta && respuesta<91){
    respuesta=respuesta+32;
}
if(respuesta == 'n'){
    return 7;
}else if(respuesta == 's'){
    return 0;
}
} while (respuesta !='s' || respuesta !='n');
printf("\n\n");
}

void LongitudCadena(){
    char cadena1[MAX+1];
    int longitud=0;
    printf("\nEscriba su frase: ");
    scanf("%[^\n]", &cadena1[0]);
    longitud = strlen(cadena1);
    printf(">>>> La logitud de la cadena es: %d\n\n", longitud);
    getchar();
}

void CopiarCadena(){
char cadena1[MAX+1];
char cadena2[2*MAX+2];
int i=0;

printf("\nCadena1: ");
scanf("%[^\n]", &cadena1[0]);
getchar();
printf("Cadena2: ");
scanf("%[^\n]", &cadena2[0]);
strcpy(cadena2, cadena1);
printf(">>>>La cadena 2 ahora dice: %s\n\n", cadena2);
getchar();
}

void CompararCadena(){
char cadena1[MAX+1];
char cadena2[MAX+1];
int valor =0;
printf("\nCadena1: ");
scanf("%[^\n]", &cadena1);
getchar();
printf("Cadena2: ");
scanf("%[^\n]", &cadena2);

valor=strcmp(cadena1, cadena2);
if(valor ==0){
    printf(">>>>Son iguales\n\n");
}else if(valor !=0){
    printf(">>>>Son distintas\n\n");
}
getchar();
}

void ConcatenarCadena(){
char cadena1[2*MAX+2];
char cadena2[MAX+1];
int i = 0;

printf("\nCadena1: ");
scanf("%[^\n]", &cadena1);
getchar();
printf("Cadena2: ");
scanf("%[^\n]", &cadena2);

strcat(cadena1, cadena2);
printf(">>>>Su cadena concatenada es: ");
//No se puede usar printf y %s por que cuando se concatena el \0 queda entre la cadena final
while(cadena1[i] != '\0'){
    printf("%c", cadena1[i]);
    i++;
}
printf("\n\n");
getchar();
}

void BuscarCaracterCadena(){
printf("Por cuestiones tecnicas, no pude hacerlo, pero ey, sabes que existe una funcion que hace eso...\n\n");
}

void CadenaEnCadena(){
printf("Por cuestiones tecnicas, no pude hacerlo, pero ey, sabes que existe una funcion que hace eso...\n\n");
}