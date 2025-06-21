/*
29/04/2025
El platillo fuerte de la práctica.
En resumidas cuentas, dada una función en x y por medio de arboles binarios,
derivarla.
*/

#include <stdio.h>
#include <stdlib.h>
int ind=0;
char coma=',';
char cero='0';
char uno='1';
char dos='2';
char sum='+';
char dif='-';
char prod='*';
char divi='/';
char expo='^';
char* ln="ln";
char* senl="sen";
char* cosl="cos";
char* tanl="tan";
char* cotl="cot";
char* secl="sec";
char* cscl="csc";

struct nodoArbol{
    void* dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
};typedef struct nodoArbol NodoArb;

struct nodoL{
    void * dato;
    struct nodoL * sig;
};typedef struct nodoL NodoL;

struct expifj{
    char* exp;
    char op;
}; typedef struct expifj Expifj;

//Arbol Binario
NodoArb* crearNodoArb(NodoArb* izq, NodoArb* der, void* dato){
    NodoArb* newn;
    newn=(NodoArb*)malloc(sizeof(NodoArb));
    newn->izq=izq;
    newn->der=der;
    newn->dato=dato;
    return newn; 
}

/*
void imprimeArb(NodoArb* r, void(*f)(void*)){
    if(!r) return;
    imprimeArb(r->izq, f);
    imprimeArb(r->der, f);
    f(r->dato);
    
}
void impCad(void* dato){
    printf("[%s]", (char*)dato);
}
*/

//Pila dinamica
NodoL* removeN(NodoL**cab){
    NodoL* p;
    if(!*cab)return NULL;
    p=*cab;
    *cab=p->sig;
    p->sig=NULL;
    return p;
}

NodoL* crearNodoL(NodoL* cab, void* dato){
    NodoL* np;
    np=(NodoL*)malloc(sizeof(NodoL));
    np->dato=dato;
    np->sig=cab;
    return np;
}

void crearPila(NodoL** stack){
    *stack=NULL;
}

/*
void imprimeLI(NodoL *cab){//Funcion mia
    if(cab->sig==NULL){
        printf("%c", *(char*)cab->dato);
        return;
    }
    imprimeLI(cab->sig);
    printf("%c", *(char*)cab->dato);    
}
*/

int CountL(NodoL* n){
    if(n->sig==NULL) return 1;
    return 1+CountL(n->sig);
}

NodoL* ConcListaInv(NodoL* L1, NodoL* L2){
    if(L2->sig==NULL) return crearNodoL(L1, L2->dato);
    L1=ConcListaInv(L1, L2->sig);
    L1=crearNodoL(L1, L2->dato);
}

int IsEmpty(NodoL* stack){
    return !stack;
}

NodoL* push(NodoL** stack, void* dato){
    *stack=crearNodoL(*stack, dato);
    return *stack;
}

void* top(NodoL* stack){
    return stack->dato;
}

void* pop(NodoL** stack){
    return removeN(stack)->dato;
}

//Notacion Postfija
int IsDigito(char carac){
    if((carac>47 && carac<58) || carac==69 || carac==101) return 1;//numero, e, x
    return 0;
}

int IsFunction(char *exp, int i){
    if(exp[i]=='l' && exp[i+1]=='n'){
        return 1;//Funcion ln
    } else if((exp[i]=='s' && exp[i+1]=='e' && exp[i+2]=='n') ||
            (exp[i]=='c' && exp[i+1]=='o' && exp[i+2]=='s') ||
            (exp[i]=='t' && exp[i+1]=='a' && exp[i+2]=='n') ||
            (exp[i]=='c' && exp[i+1]=='o' && exp[i+2]=='t') ||
            (exp[i]=='s' && exp[i+1]=='e' && exp[i+2]=='c') ||
            (exp[i]=='c' && exp[i+1]=='s' && exp[i+2]=='c') 
            ){
        return 2;//Funcion trigonometrica
    } else if((exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='s' && exp[i+4]=='e' && exp[i+5]=='n') ||
            (exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='c' && exp[i+4]=='o' && exp[i+5]=='s') ||
            (exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='t' && exp[i+4]=='a' && exp[i+5]=='n') ||
            (exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='c' && exp[i+4]=='o' && exp[i+5]=='t') ||
            (exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='s' && exp[i+4]=='e' && exp[i+5]=='c') ||
            (exp[i]=='a' && exp[i+1]=='r' && exp[i+2]=='c' && exp[i+3]=='c' && exp[i+4]=='s' && exp[i+5]=='c') 
            ){
        return 3;//Funcion trigonometrica
    } else {
        return 0;//No es funcion
    }
}

int CompOp(char op1, char op2){
    char arr[2];
    arr[0]=op1;
    arr[1]=op2;
    for(int i=0; i<2; i++){
        if(arr[i]=='N'){
            //Los operadores neutros hacen referencia a numeros o funciones, los cuales no necesitan parentesis
            arr[i]=4;
        } else if(arr[i]=='+'|| arr[i]=='-'){
            arr[i]=1;
        } else if(arr[i]=='*' || arr[i]=='/'){
            arr[i]=2;
        } else if(arr[i]=='^'){
            arr[i]=3;
        }
    }
    if(arr[0]>arr[1] || arr[0]==arr[1]){
        return 1;//op1 es mayor que op2 o son iguales
    } else if(arr[0]<arr[1]){
        return -1;//op1 es menor que op2
    }
}

NodoL* PostFijo(char* exp){
    NodoL* pilop;
    NodoL* expfn;
    int copind=0;
    crearPila(&pilop);
    crearPila(&expfn);//No es una pila, pero permite inicializarlo correctamente con NULL
    while(exp[ind]){
        if(exp[ind]=='('){
            ind++;
            expfn=ConcListaInv(expfn, PostFijo(exp));//Agrega los elementos de la expfn del () de forma invertida
        } else if(exp[ind]==')'){
            break;
        } else if(!IsDigito(exp[ind])){
            if(exp[ind]=='x'){
                expfn=crearNodoL(expfn, &exp[ind]);
                expfn=crearNodoL(expfn, &coma);
            } else if(IsFunction(exp, ind)){
                copind=ind;
                if(IsFunction(exp, ind)==1){
                    ind=ind+3;
                } else if(IsFunction(exp, ind)==2){
                    ind=ind+4;
                } else if(IsFunction(exp, ind)==3){
                    ind=ind+7;
                }
                expfn=ConcListaInv(expfn, PostFijo(exp));
                while(exp[copind]!='('){
                    expfn=crearNodoL(expfn, &exp[copind]);
                    copind++;
                } 
                expfn=crearNodoL(expfn, &coma);
            } else if(exp[ind]=='+' || exp[ind]=='-' || exp[ind]=='*' || exp[ind]=='/' || exp[ind]=='^'){
                if(exp[ind]=='-' && (ind-1<0 || exp[ind-1]=='(')){
                    expfn=crearNodoL(expfn, &cero);
                    expfn=crearNodoL(expfn, &coma);
                }
                while(!IsEmpty(pilop) && CompOp(*(char*)top(pilop), exp[ind])==1){
                expfn=crearNodoL(expfn, pop(&pilop));
                expfn=crearNodoL(expfn, &coma);
                }
                pilop=push(&pilop, &exp[ind]);
            } else if(exp[ind]=='.'){
                expfn=crearNodoL(expfn, &exp[ind]);
            }
        } else if(IsDigito(exp[ind])){
            expfn=crearNodoL(expfn, &exp[ind]);
            if(!IsDigito(exp[ind+1]) && exp[ind+1]!='.') expfn=crearNodoL(expfn, &coma);
        }
        ind++;
    }
    while(pilop){
        expfn=crearNodoL(expfn, pop(&pilop));
        expfn=crearNodoL(expfn, &coma);
    } 
    return expfn;
}


//Derivacion simbolica
void ConvCad(NodoL* exp, char* rec, int tam){
    if(exp->sig==NULL){
        rec[0]=*(char*)exp->dato;
        rec[tam]='\0';
        return;
    }else{
        ConvCad(exp->sig, rec, tam);
        rec[CountL(exp)-1]=*(char*)exp->dato;
    }
}

char* NLCAD(NodoL* expL){
    char* expcad;
    int tamL;
    tamL=CountL(expL);
    expcad=(char*)malloc((tamL+1)*sizeof(char));
    ConvCad(expL, expcad, tamL);
    return expcad;
}

char* crearsubcad(char* exp, int* i){
    char* c;
    int cont;
    cont=0;
    if(IsFunction(exp, *i)){
        if(IsFunction(exp, *i)==1){
            c=(char*)malloc(3*sizeof(char));
            c[0]=exp[*i];
            c[1]=exp[*i+1];
            c[2]='\0';
        } else if(IsFunction(exp, *i)==2){
            c=(char*)malloc(4*sizeof(char));
            c[0]=exp[*i];
            c[1]=exp[*i+1];
            c[2]=exp[*i+2];
            c[3]='\0';
        } else if(IsFunction(exp, *i)==3){
            c=(char*)malloc(7*sizeof(char));
            c[0]=exp[*i];
            c[1]=exp[*i+1];
            c[2]=exp[*i+2];
            c[3]=exp[*i+3];
            c[4]=exp[*i+4];
            c[5]=exp[*i+5];
            c[6]='\0';
        }
    } else if(IsDigito(exp[*i])){
        cont=1;
        while(exp[*i+cont]!=',') cont++;
        c=(char*)malloc((cont+1)*sizeof(char));
        for(int j=0; j<cont; j++){
            c[j]=exp[*i+j];
        }//Unica vez donde se modifica ind
        *i=*i+cont-1;
        c[cont]='\0';
    } else {
        c=(char*)malloc(2*sizeof(char));
        c[0]=exp[*i];
        c[1]='\0';
    }
    return c;
}

int tamcad(char* exp, int i){
    if(exp[i]=='\0') return 0;
    return 1+tamcad(exp, i+1);
}

char* crearchar(char c){
    char* s;
    s=(char*)malloc(2*sizeof(char));
    s[0]=c;
    s[1]='\0';
    return s;
}

NodoArb* BuildArb(char* s){
    int inda=0;
    NodoArb *izq, *der, *nvo;
    NodoL* p1;
    crearPila(&p1);
    while(s[inda]){
        if(s[inda]!=','){
            nvo=crearNodoArb(NULL, NULL, crearsubcad(s, &inda));
            if(s[inda]=='+' || s[inda]=='-' || s[inda]=='*' || s[inda]=='/' || s[inda]=='^'){
                der=(NodoArb*)pop(&p1);
                izq=(NodoArb*)pop(&p1);
                nvo->der=der;
                nvo->izq=izq;
            } else if(IsFunction(s, inda)){
                izq=(NodoArb*)pop(&p1);
                nvo->izq=izq;
                if(IsFunction(s, inda)==1){
                    inda++;
                } else if(IsFunction(s, inda)==2){
                    inda=inda+2;
                } else if(IsFunction(s, inda)==3){
                    inda=inda+5;
                }
            }
            p1=push(&p1, nvo);
        }
        inda++;
    }
    return (NodoArb*)(pop(&p1));
}

NodoArb* Derivador(NodoArb* fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb** nvo;
    if(((char*)fun->dato)[0]=='x'){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=crearNodoArb(NULL, NULL, crearchar(uno));
    } else if(IsDigito(((char*)fun->dato)[0])){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=crearNodoArb(NULL, NULL, crearchar(cero));
    } else if(((char*)fun->dato)[0]=='+' || ((char*)fun->dato)[0]=='-'){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=crearNodoArb(Derivador(fun->izq), Derivador(fun->der), fun->dato);
    } else if(((char*)fun->dato)[0]=='*'){
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=crearNodoArb(fun->izq, Derivador(fun->der), fun->dato);
        nvo[1]=crearNodoArb(fun->der, Derivador(fun->izq), fun->dato);
        nvo[0]=crearNodoArb(nvo[2], nvo[1], crearchar(sum));
    } else if(((char*)fun->dato)[0]=='/'){
        nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
        nvo[5]=crearNodoArb(fun->der, Derivador(fun->izq), crearchar(prod));
        nvo[4]=crearNodoArb(fun->izq, Derivador(fun->der), crearchar(prod));
        nvo[3]=crearNodoArb(nvo[5], nvo[4], crearchar(dif));
        nvo[2]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[1]=crearNodoArb(fun->der, nvo[2], crearchar(expo));
        nvo[0]=crearNodoArb(nvo[3], nvo[1], fun->dato);
    } else if(((char*)fun->dato)[0]=='^'){
        if(!IsDigito(((char*)(fun->izq)->dato)[0]) && IsDigito(((char*)(fun->der)->dato)[0])){
            nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
            nvo[4]=crearNodoArb(NULL, NULL, crearchar(uno));
            nvo[3]=crearNodoArb(fun->der, nvo[4], crearchar(dif));
            nvo[2]=crearNodoArb(fun->izq, nvo[3], crearchar(expo));
            nvo[1]=crearNodoArb(nvo[2], Derivador(fun->izq), crearchar(prod));
            nvo[0]=crearNodoArb(fun->der, nvo[1], crearchar(prod));
        } else if(IsDigito(((char*)(fun->izq)->dato)[0]) && !IsDigito(((char*)(fun->der)->dato)[0])){
            nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
            nvo[3]=crearNodoArb(fun->izq, fun->der, crearchar(expo));
            nvo[2]=crearNodoArb(fun->izq, NULL, ln);
            nvo[1]=crearNodoArb(nvo[3], nvo[2], crearchar(prod));
            nvo[0]=crearNodoArb(nvo[1], Derivador(fun->der), crearchar(prod));
        } else if(!IsDigito(((char*)(fun->izq)->dato)[0]) && !IsDigito(((char*)(fun->der)->dato)[0])){
            if(((char*)(fun->der)->dato)[0]=='/' && IsDigito(((char*)((fun->der)->izq)->dato)[0]) && IsDigito(((char*)((fun->der)->der)->dato)[0])){
                nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
                nvo[5]=crearNodoArb((fun->der)->der, (fun->der)->izq, crearchar(dif));
                nvo[4]=crearNodoArb(nvo[5], (fun->der)->der, crearchar(divi));
                nvo[3]=crearNodoArb(fun->izq, nvo[4], crearchar(expo));
                nvo[2]=crearNodoArb((fun->der)->der, nvo[3], crearchar(prod));
                nvo[1]=crearNodoArb((fun->der)->izq, Derivador(fun->izq), crearchar(prod));
                nvo[0]=crearNodoArb(nvo[1], nvo[2], crearchar(divi));
            } else {
                nvo=(NodoArb**)malloc(10*sizeof(NodoArb*));
                nvo[9]=crearNodoArb(NULL, NULL, crearchar(uno));
                nvo[8]=crearNodoArb(fun->der, nvo[9], crearchar(dif));
                nvo[7]=crearNodoArb(fun->izq, nvo[8], crearchar(expo));
                nvo[6]=crearNodoArb(fun->der, nvo[7], crearchar(prod));
                nvo[5]=crearNodoArb(nvo[6], Derivador(fun->izq), crearchar(prod));
                nvo[4]=crearNodoArb(fun->izq, fun->der, crearchar(expo));
                nvo[3]=crearNodoArb(fun->izq, NULL, ln);
                nvo[2]=crearNodoArb(nvo[4],nvo[3], crearchar(prod));
                nvo[1]=crearNodoArb(nvo[2], Derivador(fun->der), crearchar(prod));
                nvo[0]=crearNodoArb(nvo[5], nvo[1], crearchar(sum));
            }
        }
    } else if(((char*)fun->dato)[0]=='s' && ((char*)fun->dato)[1]=='e' && ((char*)fun->dato)[2]=='n'){
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=crearNodoArb(fun->izq, NULL, cosl);
        nvo[0]=crearNodoArb(nvo[1], Derivador(fun->izq), crearchar(prod));
    } else if(((char*)fun->dato)[0]=='c' && ((char*)fun->dato)[1]=='o' && ((char*)fun->dato)[2]=='s'){
        nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
        nvo[3]=crearNodoArb(fun->izq, NULL, senl);
        nvo[2]=crearNodoArb(nvo[3], Derivador(fun->izq), crearchar(prod));
        nvo[1]=crearNodoArb(NULL, NULL, crearchar(cero));
        nvo[0]=crearNodoArb(nvo[1], nvo[2], crearchar(dif));
    } else if(((char*)fun->dato)[0]=='t' && ((char*)fun->dato)[1]=='a' && ((char*)fun->dato)[2]=='n'){
        nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
        nvo[3]=crearNodoArb(fun->izq, NULL, secl);
        nvo[2]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[1]=crearNodoArb(nvo[3], nvo[2], crearchar(expo));
        nvo[0]=crearNodoArb(nvo[1], Derivador(fun->izq), crearchar(prod));
    } else if(((char*)fun->dato)[0]=='c' && ((char*)fun->dato)[1]=='o' && ((char*)fun->dato)[2]=='t'){
        nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
        nvo[5]=crearNodoArb(fun->izq, NULL, cscl);
        nvo[4]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[3]=crearNodoArb(nvo[5], nvo[4], crearchar(expo));
        nvo[2]=crearNodoArb(nvo[3], Derivador(fun->izq), crearchar(prod));
        nvo[1]=crearNodoArb(NULL, NULL, crearchar(cero));
        nvo[0]=crearNodoArb(nvo[1], nvo[2], crearchar(dif));
    } else if(((char*)fun->dato)[0]=='s' && ((char*)fun->dato)[1]=='e' && ((char*)fun->dato)[2]=='c'){
        nvo=(NodoArb**)malloc(4*sizeof(NodoArb*));
        nvo[3]=crearNodoArb(fun->izq, NULL, secl);
        nvo[2]=crearNodoArb(fun->izq, NULL, tanl);
        nvo[1]=crearNodoArb(nvo[3], nvo[2], crearchar(prod));
        nvo[0]=crearNodoArb(nvo[1], Derivador(fun->izq), crearchar(prod));
    } else if(((char*)fun->dato)[0]=='c' && ((char*)fun->dato)[1]=='s' && ((char*)fun->dato)[2]=='c'){
        nvo=(NodoArb**)malloc(6*sizeof(NodoArb*));
        nvo[5]=crearNodoArb(fun->izq, NULL, cscl);
        nvo[4]=crearNodoArb(fun->izq, NULL, cotl);
        nvo[3]=crearNodoArb(nvo[5], nvo[4], crearchar(prod));
        nvo[2]=crearNodoArb(nvo[3], Derivador(fun->izq), crearchar(prod));
        nvo[1]=crearNodoArb(NULL, NULL, crearchar(cero));
        nvo[0]=crearNodoArb(nvo[1], nvo[2], crearchar(dif));
    } else if(((char*)fun->dato)[0]=='a' && ((char*)fun->dato)[1]=='r' && ((char*)fun->dato)[2]=='c' && ((char*)fun->dato)[3]=='s' && ((char*)fun->dato)[4]=='e' && ((char*)fun->dato)[5]=='n'){
        nvo=(NodoArb**)malloc(7*sizeof(NodoArb*));
        nvo[6]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[5]=crearNodoArb(fun->izq, nvo[6], crearchar(expo));
        nvo[4]=crearNodoArb(NULL, NULL, crearchar(uno));
        nvo[3]=crearNodoArb(nvo[4], nvo[5], crearchar(dif));
        nvo[2]=crearNodoArb(nvo[4], nvo[6], crearchar(divi));
        nvo[1]=crearNodoArb(nvo[3], nvo[2], crearchar(expo));
        nvo[0]=crearNodoArb(Derivador(fun->izq), nvo[1], crearchar(divi));
    } else if(((char*)fun->dato)[0]=='a' && ((char*)fun->dato)[1]=='r' && ((char*)fun->dato)[2]=='c' && ((char*)fun->dato)[3]=='c' && ((char*)fun->dato)[4]=='o' && ((char*)fun->dato)[5]=='s'){
        nvo=(NodoArb**)malloc(9*sizeof(NodoArb*));
        nvo[8]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[7]=crearNodoArb(fun->izq, nvo[8], crearchar(expo));
        nvo[6]=crearNodoArb(NULL, NULL, crearchar(uno));
        nvo[5]=crearNodoArb(nvo[6], nvo[7], crearchar(dif));
        nvo[4]=crearNodoArb(nvo[6], nvo[8], crearchar(divi));
        nvo[3]=crearNodoArb(nvo[5], nvo[4], crearchar(expo));
        nvo[2]=crearNodoArb(Derivador(fun->izq), nvo[3], crearchar(divi));
        nvo[1]=crearNodoArb(NULL, NULL, crearchar(cero));
        nvo[0]=crearNodoArb(nvo[1], nvo[2], crearchar(dif));
    } else if(((char*)fun->dato)[0]=='a' && ((char*)fun->dato)[1]=='r' && ((char*)fun->dato)[2]=='c' && ((char*)fun->dato)[3]=='t' && ((char*)fun->dato)[4]=='a' && ((char*)fun->dato)[5]=='n'){
        nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
        nvo[4]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[3]=crearNodoArb(fun->izq, nvo[4], crearchar(expo));
        nvo[2]=crearNodoArb(NULL, NULL, crearchar(uno));
        nvo[1]=crearNodoArb(nvo[3], nvo[2], crearchar(sum));
        nvo[0]=crearNodoArb(Derivador(fun->izq), nvo[1], crearchar(divi));
    } else if(((char*)fun->dato)[0]=='a' && ((char*)fun->dato)[1]=='r' && ((char*)fun->dato)[2]=='c' && ((char*)fun->dato)[3]=='c' && ((char*)fun->dato)[4]=='o' && ((char*)fun->dato)[5]=='t'){
        nvo=(NodoArb**)malloc(7*sizeof(NodoArb*));
        nvo[6]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[5]=crearNodoArb(fun->izq, nvo[6], crearchar(expo));
        nvo[4]=crearNodoArb(NULL, NULL, crearchar(uno));
        nvo[3]=crearNodoArb(nvo[5], nvo[4], crearchar(sum));
        nvo[2]=crearNodoArb(Derivador(fun->izq), nvo[3], crearchar(divi));
        nvo[1]=crearNodoArb(NULL, NULL, crearchar(cero));
        nvo[0]=crearNodoArb(nvo[1], nvo[2], crearchar(dif));
    } else if(((char*)fun->dato)[0]=='a' && ((char*)fun->dato)[1]=='r' && ((char*)fun->dato)[2]=='c' && ((char*)fun->dato)[3]=='s' && ((char*)fun->dato)[4]=='e' && ((char*)fun->dato)[5]=='c'){
        nvo=(NodoArb**)malloc(8*sizeof(NodoArb*));
        nvo[7]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[6]=crearNodoArb(fun->izq, nvo[7], crearchar(expo));
        nvo[5]=crearNodoArb(NULL, NULL, crearchar(uno));
        nvo[4]=crearNodoArb(nvo[6], nvo[5], crearchar(dif));
        nvo[3]=crearNodoArb(nvo[5], nvo[7], crearchar(divi));
        nvo[2]=crearNodoArb(nvo[4], nvo[3], crearchar(expo));
        nvo[1]=crearNodoArb(fun->izq, nvo[2], crearchar(prod));
        nvo[0]=crearNodoArb(Derivador(fun->izq), nvo[1], crearchar(divi));
    } else if(((char*)fun->dato)[0]=='a' && ((char*)fun->dato)[1]=='r' && ((char*)fun->dato)[2]=='c' && ((char*)fun->dato)[3]=='c' && ((char*)fun->dato)[4]=='s' && ((char*)fun->dato)[5]=='c'){
        nvo=(NodoArb**)malloc(10*sizeof(NodoArb*));
        nvo[9]=crearNodoArb(NULL, NULL, crearchar(dos));
        nvo[8]=crearNodoArb(fun->izq, nvo[9], crearchar(expo));
        nvo[7]=crearNodoArb(NULL, NULL, crearchar(uno));
        nvo[6]=crearNodoArb(nvo[8], nvo[7], crearchar(dif));
        nvo[5]=crearNodoArb(nvo[7], nvo[9], crearchar(divi));
        nvo[4]=crearNodoArb(nvo[6], nvo[5], crearchar(expo));
        nvo[3]=crearNodoArb(fun->izq, nvo[4], crearchar(prod));
        nvo[2]=crearNodoArb(Derivador(fun->izq), nvo[3], crearchar(divi));
        nvo[1]=crearNodoArb(NULL, NULL, crearchar(cero));
        nvo[0]=crearNodoArb(nvo[1], nvo[2], crearchar(dif));
    } else if(((char*)fun->dato)[0]=='l' && ((char*)fun->dato)[1]=='n'){
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=crearNodoArb(Derivador(fun->izq), fun->izq, crearchar(divi));
    }
    //free(fun);
    return nvo[0];
}

NodoL* Infija(char* exp){
    NodoL* p1;
    Expifj* out, *el1, *el2;
    int tamt=0;
    int inda=0;
    crearPila(&p1);
    while(exp[inda]!='\0'){
        if(exp[inda]!=','){
            out=(Expifj*)malloc(sizeof(Expifj));
            if(IsDigito(exp[inda]) || exp[inda]=='x'){
                out->exp=crearsubcad(exp, &inda);
                out->op='N';
            } else if(IsFunction(exp, inda)){
                el1=(Expifj*)pop(&p1);//Argumento de la funcion
                tamt=tamcad(el1->exp, 0)+3;
                if(IsFunction(exp, inda)==1){
                    tamt=tamt+2;
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    out->exp[0]='l';
                    out->exp[1]='n';
                    out->exp[2]='(';
                    for(int i=3, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    inda=inda+1;
                } else if(IsFunction(exp, inda)==2){
                    //Trigonometrica
                    tamt=tamt+3;
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    out->exp[0]=exp[inda];
                    out->exp[1]=exp[inda+1];
                    out->exp[2]=exp[inda+2];
                    out->exp[3]='(';
                    for(int i=4, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    inda=inda+2;
                } else if(IsFunction(exp, inda)==3){
                    //arc trigonometrica
                    tamt=tamt+6;
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    out->exp[0]=exp[inda];
                    out->exp[1]=exp[inda+1];
                    out->exp[2]=exp[inda+2];
                    out->exp[3]=exp[inda+3];
                    out->exp[4]=exp[inda+4];
                    out->exp[5]=exp[inda+5];
                    out->exp[6]='(';
                    for(int i=7, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    inda=inda+5;
                }
                out->exp[tamt-2]=')';
                out->exp[tamt-1]='\0';
                out->op='N';
            } else {
                //Operador
                el2=(Expifj*)pop(&p1);//Operando derecho
                el1=(Expifj*)pop(&p1);//Operando izquierdo
                tamt=tamcad(el1->exp, 0)+tamcad(el2->exp, 0)+2;
                if((CompOp(el1->op, exp[inda])==1 && CompOp(el2->op, exp[inda])==-1) || (exp[inda]=='-' && (el2->op=='+' || el2->op=='-')) || (exp[inda]=='/' && el1->op=='N' && el2->op!='N')){
                    //Cuando el operador de entrada es mayor que el de ele2 o sean iguales a '-'
                    out->exp=(char*)malloc((tamt+2)*sizeof(char));
                    for(int i=0; el1->exp[i]!='\0'; i++) out->exp[i]=el1->exp[i];
                    out->exp[tamcad(el1->exp, 0)]=exp[inda];
                    out->exp[tamcad(el1->exp, 0)+1]='(';
                    for(int i=tamcad(el1->exp, 0)+2, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt]=')';
                    out->exp[tamt+1]='\0';
                } else if((CompOp(el1->op, exp[inda])==-1 && CompOp(el2->op, exp[inda])==-1) || (exp[inda]=='/' && el1->op!='N' && el2->op!='N')){
                    //Los operadores de el1 y el2 son menores al de la entrada
                    out->exp=(char*)malloc((tamt+4)*sizeof(char));
                    out->exp[0]='(';
                    for(int i=1, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    out->exp[tamcad(el1->exp, 0)+1]=')';
                    out->exp[tamcad(el1->exp, 0)+2]=exp[inda];
                    out->exp[tamcad(el1->exp, 0)+3]='(';
                    for(int i=tamcad(el1->exp, 0)+4, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt+2]=')';
                    out->exp[tamt+3]='\0';
                } else if((CompOp(el1->op, exp[inda])==1 && CompOp(el2->op, exp[inda])==1) || (exp[inda]=='/' && el1->op=='N' && el2->op=='N')){
                    //Cuando el1 y el2 son numeros o funciones (trigo, log, arc)
                    out->exp=(char*)malloc(tamt*sizeof(char));
                    for(int i=0; el1->exp[i]!='\0'; i++) out->exp[i]=el1->exp[i];
                    out->exp[tamcad(el1->exp, 0)]=exp[inda];
                    for(int i=tamcad(el1->exp, 0)+1, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt-1]='\0';
                } else if((CompOp(el1->op, exp[inda])==-1 && CompOp(el2->op, exp[inda])==1) || (exp[inda]=='/' && el1->op!='N' && el2->op=='N')){
                    //Cuando el operador de entrada es mas grande que el del el1
                    out->exp=(char*)malloc((tamt+2)*sizeof(char));
                    out->exp[0]='(';
                    for(int i=1, j=0; el1->exp[j]!='\0'; i++, j++) out->exp[i]=el1->exp[j];
                    out->exp[tamcad(el1->exp, 0)+1]=')';
                    out->exp[tamcad(el1->exp, 0)+2]=exp[inda];
                    for(int i=tamcad(el1->exp, 0)+3, j=0; el2->exp[j]!='\0'; i++, j++) out->exp[i]=el2->exp[j];
                    out->exp[tamt+1]='\0';
                }
                out->op=exp[inda];
            }
            p1=push(&p1, out);
        }
        inda++;
    }
    return p1;
}

void ARBNL(NodoArb* arb, NodoL** p){
    int i=0;
    if(!arb) return;
    ARBNL(arb->izq, p);
    ARBNL(arb->der, p);
    while(((char*)arb->dato)[i]!='\0'){
        *p=push(p, &((char*)arb->dato)[i]);
        i++;
    }
    
    *p=push(p, crearchar(coma));
}

NodoArb *SimplificarRaiz(NodoArb *fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb **nvo; 
    if(((char*)fun->dato)[0]=='*' && (((char*)(fun->izq)->dato)[0]=='1' || ((char*)(fun->der)->dato)[0]=='1')){
        //1*u=u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        if(((char*)(fun->izq)->dato)[0]=='1')
            *nvo=fun->der;
        else if(((char*)(fun->der)->dato)[0]=='1')
            *nvo=fun->izq;
    } else if((((char*)fun->dato)[0]=='*' || ((char*)fun->dato)[0]=='/') && (((char*)(fun->izq)->dato)[0]=='0' || ((char*)(fun->der)->dato)[0]=='0')){
        //0*u=0, 0/u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=crearNodoArb(NULL, NULL, crearchar(cero));
        //Nota: el caso de u/0 entra en este if, sin embargo, esto jamas ocurrira a menos que el usuario ingrese una expresion similar
    } else if(((char*)fun->dato)[0]=='+' && (((char*)(fun->izq)->dato)[0]=='0' || ((char*)(fun->der)->dato)[0]=='0')){
        //0+u=u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        if(((char*)(fun->izq)->dato)[0]=='0')
            *nvo=fun->der;
        else if(((char*)(fun->der)->dato)[0]=='0')
            *nvo=fun->izq;
    } else if(((char*)fun->dato)[0]=='-' && ((char*)(fun->der)->dato)[0]=='0'){
        //u-0=u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=fun->izq;
    } else if(((char*)fun->dato)[0]=='/' && (((char*)(fun->izq)->dato)[0]=='/' || ((char*)(fun->der)->dato)[0]=='/')){
        if(((char*)(fun->izq)->dato)[0]=='/' && ((char*)(fun->der)->dato)[0]!='/'){
            //(a/b)/c=a/b*c
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=crearNodoArb(fun->izq->der, fun->der, crearchar(prod));
            nvo[0]=crearNodoArb(fun->izq->izq, nvo[1], crearchar(divi));
        } else if(((char*)(fun->izq)->dato)[0]!='/' && ((char*)(fun->der)->dato)[0]=='/'){
            //a/(b/c)=a*c/b
            nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
            nvo[1]=crearNodoArb(fun->izq, fun->izq->izq, crearchar(prod));
            nvo[0]=crearNodoArb(nvo[1], fun->der->izq, crearchar(divi));
        } else if(((char*)(fun->izq)->dato)[0]=='/' && ((char*)(fun->der)->dato)[0]=='/'){
            //(a/b)/(c/d)=a*d/b*c
            nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
            nvo[2]=crearNodoArb(fun->izq->izq, fun->der->der, crearchar(prod));
            nvo[1]=crearNodoArb(fun->izq->der, fun->der->izq, crearchar(prod));
            nvo[0]=crearNodoArb(nvo[2], nvo[1], crearchar(divi));
        }
    } else {
        //No se cumple ninguna condicion para simplificar o fun es un numero/funcion
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=crearNodoArb(fun->izq, fun->der, fun->dato);
    }
    (*nvo)->der=SimplificarRaiz((*nvo)->der);
    (*nvo)->izq=SimplificarRaiz((*nvo)->izq);
    //free(fun);
    return *nvo;
}

NodoArb *SimplificarFun(NodoArb *fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb *nvo=crearNodoArb(SimplificarFun(fun->izq), SimplificarFun(fun->der), fun->dato);
    nvo=SimplificarRaiz(nvo);
    return nvo;
}

int main(){
    char* expinc,*exp1, *res;
    NodoArb* exp2, *exp3;
    NodoL* p;
    //Se recibe la función
    crearPila(&p);
    printf("\nf(x)=");
    scanf("%[^\n]", expinc);
    
    //Se convierte a notación postfija y después se construye el árbol
    exp1=NLCAD(PostFijo(expinc));    
    exp2=BuildArb(exp1);

    //Se construye el árbol derivado, se simplifica y se convierte a cadena en notación infija
    ARBNL(SimplificarFun(Derivador(exp2)), &p);
    res=NLCAD(p);
    printf("f'(x)=");
    printf("%s", ((Expifj*)Infija(res)->dato)->exp);
    
    return 0;
}