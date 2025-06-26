#include <stdio.h>
#include <stdlib.h>

typedef struct NodoL {
    int fila, columna, valor;
    struct NodoL *siguiente;
} NodoL;

NodoL *crearNL(int fila, int columna, int valor){
    NodoL *nvo = malloc(sizeof *nvo);
    if (!nvo) { perror("malloc"); exit(EXIT_FAILURE); }
    nvo->fila = fila;
    nvo->columna = columna;
    nvo->valor = valor;
    nvo->siguiente = NULL;
    return nvo;
}

void insNL(NodoL **cab, int fila, int columna, int valor){
    NodoL *nvo = crearNL(fila, columna, valor);
    if (!*cab) {
        *cab = nvo;
    } else {
        NodoL *p = *cab;
        while (p->siguiente) p = p->siguiente;
        p->siguiente = nvo;
    }
}

NodoL* sumMtx(NodoL *mtx1, NodoL *mtx2){
    NodoL *res = NULL;
    while (mtx1 || mtx2) {
        if (mtx1 && mtx2) {
            if (mtx1->fila == mtx2->fila && mtx1->columna == mtx2->columna) {
                int suma = mtx1->valor + mtx2->valor;
                if (suma != 0)
                    insNL(&res, mtx1->fila, mtx1->columna, suma);
                mtx1 = mtx1->siguiente;
                mtx2 = mtx2->siguiente;
            } else if (mtx1->fila < mtx2->fila || (mtx1->fila == mtx2->fila && mtx1->columna < mtx2->columna)) {
                insNL(&res, mtx1->fila, mtx1->columna, mtx1->columna);
                mtx1 = mtx1->siguiente;
            } else {
                insNL(&res, mtx2->fila, mtx2->columna, mtx2->valor);
                mtx2 = mtx2->siguiente;
            }
        } else if (mtx1) {
            insNL(&res, mtx1->fila, mtx1->columna, mtx1->valor);
            mtx1 = mtx1->siguiente;
        } else {
            insNL(&res, mtx2->fila, mtx2->columna, mtx2->valor);
            mtx2 = mtx2->siguiente;
        }
    }
    return res;
}

NodoL *multMtxDif(NodoL *mtx1, NodoL *mtx2, int m1, int n1, int m2, int n2){
    if (n1 != m2) {
        printf("No se puede multiplicar: columnas mtx1 (%d) ≠ filas mtx2 (%d)\n", n1, m2);
        return NULL;
    }
    NodoL *res = NULL;
    for (int i = 0; i < m1; i++) {
        for (int k = 0; k < n2; k++) {
            int sumA = 0;
            for (int j = 0; j < n1; j++) {
                int aux1 = 0, aux2 = 0;
                for (NodoL *p = mtx1; p; p = p->siguiente)
                    if (p->fila == i && p->columna == j) { aux1 = p->valor; break; }
                for (NodoL *q = mtx2; q; q = q->siguiente)
                    if (q->fila == j && q->columna == k) { aux2 = q->valor; break; }
                sumA += aux1 * aux2;
            }
            insNL(&res, i, k, sumA);
        }
    }
    return res;
}

NodoL *multMtx(NodoL *mtx1, NodoL *mtx2, int m, int n){
    return multMtxDif(mtx1, mtx2, m, n, m, n);
}

void acomp(NodoL **matriz, int m, int n){
    int numValores;
    printf("Valores no nulos: ");
    scanf("%d", &numValores);

    for (int t = 0; t < numValores; t++) {
        int fila, col, val;
        printf("fila,col,valor: ");
        scanf("%d %d %d", &fila, &col, &val);
        if (fila>=0 && fila<m && col>=0 && col<n)
            insNL(matriz, fila, col, val);
        else {
            printf("Fuera de rango\n");
            t--;
        }
    }
}

void imp(NodoL *cab){
    for (NodoL *p = cab; p; p = p->siguiente) {
        printf("(%d,%d,%d) ", p->fila, p->columna, p->valor);
    }
    printf("\n");
}

void impMatrix(NodoL *mx, int m, int n){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int aux = 0;
            for (NodoL *p = mx; p; p = p->siguiente)
                if (p->fila == i && p->columna == j) {
                    aux = p->valor; break;
                }
            printf("%3d ", aux);
        }
        printf("\n");
    }
}

int main(){
    NodoL *mtx1 = NULL, *mtx2 = NULL;
    int m, n, m1, n1;

    printf("Filas de matriz1: "); scanf("%d", &m);
    printf("Cols de matriz1: "); scanf("%d", &n);
    printf("Filas de matriz2: "); scanf("%d", &m1);
    printf("Cols de matriz2: "); scanf("%d", &n1);

    printf("Matriz 1:\n"); acomp(&mtx1, m, n); imp(mtx1);
    printf("Matriz 2:\n"); acomp(&mtx2, m1, n1); imp(mtx2);

    NodoL *sum = sumMtx(mtx1, mtx2);
    printf("Suma:\n");
    impMatrix(sum, m, n);

    NodoL *prodDif = multMtxDif(mtx1, mtx2, m, n, m1, n1);
    if (prodDif) {
        printf("Producto genérico:\n"); impMatrix(prodDif, m, n1);
    }

    NodoL *prod = multMtx(mtx1, mtx2, m, n);
    printf("Producto (NxN):\n"); impMatrix(prod, m, n);

    return 0;
}
