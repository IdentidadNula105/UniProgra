/*
Este archivo es un antecedente para la practica 4, la cual por masoquismo se decidio
que sea el derivador simbolico.
En resumen, la notacion postfija se escribe primero los operandos y luego los operadores
5-(5*7+8) - > 557*8+-
El operador toma los dos ultimos valores que le anteceden, de izquierda a derecha.
*/

#include <stdio.h>
#include <stdlib.h>
int ind=0;
char coma=44;
struct nodoL{
    void * dato;//Almacena cualquier valor, resguardando la direccion del valor
    struct nodoL * sig;
};typedef struct nodoL NodoL;

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

//PERDONAME DIOS
void imprimeLI(NodoL *cab){//Funcion mia
    if(cab->sig==NULL){
        printf("%c", *(char*)cab->dato);
        return;
    }
    imprimeLI(cab->sig);
    printf("%c", *(char*)cab->dato);    
}

NodoL* ConcListaInv(NodoL* L1, NodoL* L2){
    if(L2->sig==NULL) return crearNodoL(L1, L2->dato);
    L1=ConcListaInv(L1, L2->sig);
    L1=crearNodoL(L1, L2->dato);
}

//OPERACIONES
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

//Para Postfija
int IsDigito(char carac){
    if((carac>47 && carac<58) || carac==69 || carac==101) return 1;
    return 0;
}

int IsFunction(char *exp, int ind){
    if(exp[ind]=='l' && exp[ind+1]=='n' && exp[ind+2]=='('){
        return 1;//Funcion ln
    } else if(((exp[ind]=='s' && exp[ind+1]=='e' && exp[ind+2]=='n') ||
               (exp[ind]=='c' && exp[ind+1]=='o' && exp[ind+2]=='s') ||
               (exp[ind]=='t' && exp[ind+1]=='a' && exp[ind+2]=='n') ||
               (exp[ind]=='c' && exp[ind+1]=='o' && exp[ind+2]=='t') ||
               (exp[ind]=='s' && exp[ind+1]=='e' && exp[ind+2]=='c') ||
               (exp[ind]=='c' && exp[ind+1]=='s' && exp[ind+2]=='c')) 
               && exp[ind+3]=='('){
        return 2;//Funcion trigonometrica
    } else {
        return 0;//No es funcion
    }
}

int CompOp(char op1, char op2){
    char arr[2];
    arr[0]=op1;
    arr[1]=op2;
    for(int i=0; i<2; i++){
        if(arr[i]=='+'|| arr[i]=='-'){
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
                }else if(IsFunction(exp, ind)==2){
                    ind=ind+4;
                }
                expfn=ConcListaInv(expfn, PostFijo(exp));
                while(exp[copind]!='('){
                    expfn=crearNodoL(expfn, &exp[copind]);
                    copind++;
                } 
                expfn=crearNodoL(expfn, &coma);
            } else if(exp[ind]=='+' || exp[ind]=='-' || exp[ind]=='*' || exp[ind]=='/' || exp[ind]=='^'){
                while(!IsEmpty(pilop) && CompOp(*(char*)top(pilop), exp[ind])==1){
                expfn=crearNodoL(expfn, pop(&pilop));
                expfn=crearNodoL(expfn, &coma);
                }
                pilop=push(&pilop, &exp[ind]);
            }
        } else if(IsDigito(exp[ind])){
            expfn=crearNodoL(expfn, &exp[ind]);
            if(!IsDigito(exp[ind+1])) expfn=crearNodoL(expfn, &coma);
        }
        ind++;
    }
    while(pilop){
        expfn=crearNodoL(expfn, pop(&pilop));
        expfn=crearNodoL(expfn, &coma);
    } 
    return expfn;
}
int main(){
    char *exp;
    printf("\nIntroduzca su expresion: ");
    scanf("%[^\n]", exp);
    imprimeLI(PostFijo(exp));
    return 0;
}