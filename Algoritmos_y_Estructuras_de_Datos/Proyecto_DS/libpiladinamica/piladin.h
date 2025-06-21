#ifndef piladin
#define piladin
struct nodoL{
    void * dato;//Almacena cualquier valor, resguardando la direccion del valor
    struct nodoL * sig;
};typedef struct nodoL NodoL;

NodoL* RemoveN(NodoL**cab);

NodoL* CrearNodoL(NodoL* cab, void* dato);

void CrearPila(NodoL** stack);

int NumeroNL(NodoL* n);

NodoL* ConcatenarListInvertida(NodoL* L1, NodoL* L2);

int IsEmpty(NodoL* stack);

NodoL* Push(NodoL** stack, void* dato);

void* Top(NodoL* stack);

void* Pop(NodoL** stack);
#endif