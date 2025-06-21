#ifndef derivsimb
#define derivsimb

NodoArb* ConstruirArbolFuncion(char* s);

NodoArb* DerivarArbolFuncion(NodoArb* fun);

void Convertir_Arbol_Lista(NodoArb* arb, NodoL** p);

NodoArb *SimplificarArbolFuncion(NodoArb *fun);

#endif