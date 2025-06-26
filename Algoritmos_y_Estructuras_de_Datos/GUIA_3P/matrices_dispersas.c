
/*
25/06/2025
Nota: desafortunadamente, el siguiente codigo no es de mi autoria, por cuestiones de
tiempo se decidio solicitarselo a mi buen amigo Garcia.
*/

#include <stdio.h>
#include <stdlib.h>

// Nodo para representar un elemento no nulo de la matriz
typedef struct Nodo {
    int fila, columna;
    int valor;
    struct Nodo* siguiente;
} Nodo;

// Lista para representar una matriz dispersa
typedef struct {
    int filas, columnas;
    Nodo* cabeza;
} MatrizDispersa;

// Crear una nueva matriz dispersa
MatrizDispersa* crearMatriz(int filas, int columnas) {
    MatrizDispersa* matriz = (MatrizDispersa*)malloc(sizeof(MatrizDispersa));
    matriz->filas = filas;
    matriz->columnas = columnas;
    matriz->cabeza = NULL;
    return matriz;
}

// Insertar un elemento no nulo en la matriz
void insertarElemento(MatrizDispersa* matriz, int fila, int columna, int valor) {
    if (valor == 0) return;

    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->fila = fila;
    nuevo->columna = columna;
    nuevo->valor = valor;
    nuevo->siguiente = matriz->cabeza;
    matriz->cabeza = nuevo;
}

// Imprimir la matriz dispersa
void imprimirMatriz(MatrizDispersa* matriz) {
    Nodo* actual = matriz->cabeza;
    printf("Elementos no nulos:\n");
    while (actual != NULL) {
        printf("(%d, %d) = %d\n", actual->fila, actual->columna, actual->valor);
        actual = actual->siguiente;
    }
}

// Comparar si dos matrices dispersas son iguales
int sonIguales(MatrizDispersa* A, MatrizDispersa* B) {
    if (A->filas != B->filas || A->columnas != B->columnas) return 0;

    Nodo* a = A->cabeza;
    Nodo* b = B->cabeza;

    while (a != NULL && b != NULL) {
        if (a->fila != b->fila || a->columna != b->columna || a->valor != b->valor) {
            return 0;
        }
        a = a->siguiente;
        b = b->siguiente;
    }

    return (a == NULL && b == NULL);
}

// Sumar dos matrices dispersas
MatrizDispersa* sumar(MatrizDispersa* A, MatrizDispersa* B) {
    if (A->filas != B->filas || A->columnas != B->columnas) {
        printf("No se pueden sumar: dimensiones incompatibles.\n");
        return NULL;
    }

    MatrizDispersa* resultado = crearMatriz(A->filas, A->columnas);

    Nodo* a = A->cabeza;
    while (a != NULL) {
        insertarElemento(resultado, a->fila, a->columna, a->valor);
        a = a->siguiente;
    }

    Nodo* b = B->cabeza;
    while (b != NULL) {
        Nodo* r = resultado->cabeza;
        while (r != NULL) {
            if (r->fila == b->fila && r->columna == b->columna) {
                r->valor += b->valor;
                break;
            }
            r = r->siguiente;
        }
        if (r == NULL) {
            insertarElemento(resultado, b->fila, b->columna, b->valor);
        }
        b = b->siguiente;
    }

    return resultado;
}

// Restar dos matrices dispersas
MatrizDispersa* restar(MatrizDispersa* A, MatrizDispersa* B) {
    if (A->filas != B->filas || A->columnas != B->columnas) {
        printf("No se pueden restar: dimensiones incompatibles.\n");
        return NULL;
    }

    MatrizDispersa* resultado = crearMatriz(A->filas, A->columnas);

    Nodo* a = A->cabeza;
    while (a != NULL) {
        insertarElemento(resultado, a->fila, a->columna, a->valor);
        a = a->siguiente;
    }

    Nodo* b = B->cabeza;
    while (b != NULL) {
        Nodo* r = resultado->cabeza;
        while (r != NULL) {
            if (r->fila == b->fila && r->columna == b->columna) {
                r->valor -= b->valor;
                break;
            }
            r = r->siguiente;
        }
        if (r == NULL) {
            insertarElemento(resultado, b->fila, b->columna, -b->valor);
        }
        b = b->siguiente;
    }

    return resultado;
}

// Multiplicar dos matrices dispersas
MatrizDispersa* multiplicar(MatrizDispersa* A, MatrizDispersa* B) {
    if (A->columnas != B->filas) {
        printf("No se pueden multiplicar: dimensiones incompatibles.\n");
        return NULL;
    }

    MatrizDispersa* resultado = crearMatriz(A->filas, B->columnas);

    for (Nodo* a = A->cabeza; a != NULL; a = a->siguiente) {
        for (Nodo* b = B->cabeza; b != NULL; b = b->siguiente) {
            if (a->columna == b->fila) {
                int fila = a->fila;
                int columna = b->columna;
                int valor = a->valor * b->valor;

                Nodo* r = resultado->cabeza;
                while (r != NULL) {
                    if (r->fila == fila && r->columna == columna) {
                        r->valor += valor;
                        break;
                    }
                    r = r->siguiente;
                }
                if (r == NULL) {
                    insertarElemento(resultado, fila, columna, valor);
                }
            }
        }
    }

    return resultado;
}

// Verificar si una matriz dispersa es la matriz identidad
int esIdentidad(MatrizDispersa* matriz) {
    if (matriz->filas != matriz->columnas) return 0;

    for (int i = 0; i < matriz->filas; i++) {
        for (int j = 0; j < matriz->columnas; j++) {
            int encontrado = 0;
            Nodo* actual = matriz->cabeza;
            while (actual != NULL) {
                if (actual->fila == i && actual->columna == j) {
                    if (i == j && actual->valor != 1) return 0;
                    if (i != j && actual->valor != 0) return 0;
                    encontrado = 1;
                    break;
                }
                actual = actual->siguiente;
            }
            if (!encontrado && i == j) return 0;
        }
    }

    return 1;
}

// Función principal para probar las funciones
int main() {
    int filasA, columnasA, filasB, columnasB;

    printf("Dimensiones de la matriz A (filas columnas): ");
    scanf("%d %d", &filasA, &columnasA);
    MatrizDispersa* A = crearMatriz(filasA, columnasA);
    printf("Introduce los elementos no nulos de A (fila columna valor), -1 para terminar:\n");
    while (1) {
        int f, c, valor;
        scanf("%d", &f);
        if (f == -1) break;
        scanf("%d %d", &c, &valor);
        insertarElemento(A, f, c, valor);
    }

    printf("Dimensiones de la matriz B (filas columnas): ");
    scanf("%d %d", &filasB, &columnasB);
    MatrizDispersa* B = crearMatriz(filasB, columnasB);
    printf("Introduce los elementos no nulos de B (fila columna valor), -1 para terminar:\n");
    while (1) {
        int f, c, valor;
        scanf("%d", &f);
        if (f == -1) break;
        scanf("%d %d", &c, &valor);
        insertarElemento(B, f, c, valor);
    }

    printf("Matriz A:\n");
    imprimirMatriz(A);
    printf("Matriz B:\n");
    imprimirMatriz(B);

    MatrizDispersa* C = sumar(A, B);
    if (C != NULL) {
        printf("Suma de A y B:\n");
        imprimirMatriz(C);
    }

    MatrizDispersa* D = restar(A, B);
    if (D != NULL) {
        printf("Resta de A y B:\n");
        imprimirMatriz(D);
    }

    MatrizDispersa* E = multiplicar(A, B);
    if (E != NULL) {
        printf("Multiplicación de A y B:\n");
        imprimirMatriz(E);
    }

    printf("¿A es identidad? %s\n", esIdentidad(A) ? "Sí" : "No");
    printf("¿B es identidad? %s\n", esIdentidad(B) ? "Sí" : "No");

    return 0;
}
