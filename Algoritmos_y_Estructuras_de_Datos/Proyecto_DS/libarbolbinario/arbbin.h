#ifndef arbbin
#define arbbin

struct nodoArbol{
    void* dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
};typedef struct nodoArbol NodoArb;

NodoArb* CrearNodoArb(NodoArb* izq, NodoArb* der, void* dato);

void ImprimeArb(NodoArb* r, void(*f)(void*));

void impInt(void* dato);

void impChar(void* dato);

void impCad(void* dato);

void impFloat(void* dato);

#endif