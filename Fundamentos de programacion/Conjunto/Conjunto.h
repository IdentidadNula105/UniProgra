#define MAX_SIZE 100 // conjuntos con capacidad máxima para 100 elementos
#include <stdio.h>
#include <stdlib.h>
struct Conjunto {
//	int *elementos; //apuntador
	int C [MAX_SIZE]; //arreglo con elementos del conjunto
	int size;
};
typedef struct Conjunto conjunto; //redefinimos el nombre del tipo de dato


void InicializarConjunto(conjunto *X); //no es necesesario poner el nombre del tipo de dato ((conjunto * )) o (conjunto *, int ) pues no importa pero se pone por educación
void AgregarElemento(conjunto *X, int e);
void EliminarElemento(conjunto *X, int e);
int PerteneceElemento(conjunto *X, int e);
void ImprimeConjunto(conjunto *X);
int ElementoPrimo(int e);
