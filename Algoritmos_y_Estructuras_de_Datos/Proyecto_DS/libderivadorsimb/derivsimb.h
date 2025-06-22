#ifndef derivsimb
#define derivsimb

typedef struct nodoArbol NodoArb;
typedef struct nodoL NodoL;

NodoArb* ConstruirArbolFuncion(char* s);

NodoArb* DerivArb_x(NodoArb* fun);

NodoArb* DerivArb_Numero(NodoArb* fun);

NodoArb* DerivArb_Producto(NodoArb* fun);

NodoArb* DerivArb_Cociente(NodoArb* fun);

NodoArb* DerivArb_Fun_C(NodoArb* fun);

NodoArb* DerivArb_C_Fun(NodoArb* fun);

NodoArb* DerivArb_Fun_Fun(NodoArb* fun);

NodoArb* DerivArb_Raiz(NodoArb* fun);

NodoArb* DerivArb_sen(NodoArb* fun);

NodoArb* DerivArb_cos(NodoArb* fun);

NodoArb* DerivArb_tan(NodoArb* fun);

NodoArb* DerivArb_cot(NodoArb* fun);

NodoArb* DerivArb_sec(NodoArb* fun);

NodoArb* DerivArb_csc(NodoArb* fun);

NodoArb* DerivArb_arcsen(NodoArb* fun);

NodoArb* DerivArb_arccos(NodoArb* fun);

NodoArb* DerivArb_arctan(NodoArb* fun);

NodoArb* DerivArb_arccot(NodoArb* fun);

NodoArb* DerivArb_arcsec(NodoArb* fun);

NodoArb* DerivArb_arccsc(NodoArb* fun);

NodoArb* DerivArb_ln(NodoArb* fun);

NodoArb* DerivarArbolFuncion(NodoArb* fun);

void Convertir_Arbol_Lista(NodoArb* arb, NodoL** p);

NodoArb *SimplificarArbolFuncion(NodoArb *fun);

NodoArb *SimplificarFun(NodoArb *fun);

char *Derivar(char *funcionx);

#endif