#ifndef notainfpost
#define notainfpost

struct expifj{
    char* exp;
    char op;
}; typedef struct expifj Expifj;

int CompararOp(char op1, char op2);

void ConvCad(NodoL* exp, char* rec, int tam);

char* Convertir_Lista_Cadena(NodoL* expL);

NodoL* PostFijo(char* exp);

NodoL* Infija(char* exp);

#endif