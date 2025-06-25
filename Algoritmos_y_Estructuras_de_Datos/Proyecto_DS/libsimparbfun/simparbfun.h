#ifndef simparbfun
#define simparbfun

typedef struct nodoArbol NodoArb;

NodoArb* SimplificarArbSuma(NodoArb* fun);

NodoArb* SimplificarArbResta(NodoArb* fun);

NodoArb* SimplificarArbMulti(NodoArb* fun);

NodoArb* SimplificarArbDivision(NodoArb* fun);

NodoArb* SimplificarArbPoten(NodoArb* fun);

NodoArb* SimplificarArbln(NodoArb* fun);

NodoArb *SimplificarArbolFuncion(NodoArb *fun);

NodoArb *SimplificarFun(NodoArb *fun);

#endif