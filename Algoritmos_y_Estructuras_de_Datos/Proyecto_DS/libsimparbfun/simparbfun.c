#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../libarbolbinario/arbbin.h"
#include "../libis/is.h"
#include "../libcadespecial/cadesp.h"
#include "simparbfun.h"

#define fundato ((char*)fun->dato)
#define funizqdato ((char*)fun->izq->dato)
#define funderdato ((char*)fun->der->dato)
#define funderderdato ((char*)fun->der->der->dato)
#define funderizqdato ((char*)fun->der->izq->dato)
#define funizqizqdato ((char*)fun->izq->izq->dato)
#define funizqderdato ((char*)fun->izq->der->dato)

NodoArb* SimplificarArbSuma(NodoArb* fun){
    if(!fun) return NULL;
    NodoArb** nvo;
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    if(IsDigito(funizqdato[0]) && IsDigito(funderdato[0])){
        //a+b=c
        //printf("(%d)",Convertir_Cad_Numero(funizqdato)+Convertir_Cad_Numero(funderdato));
        nvo[0]=CrearNodoArb(NULL, NULL, Convertir_Numero_Cad(Convertir_Cad_Numero(funizqdato)+Convertir_Cad_Numero(funderdato)));
    } else if(IsDigito(funizqdato[0]) && !IsDigito(funderdato[0])){
        //c+u=u+c
        (*nvo)=fun;
        NodoArb* temp=(*nvo)->der;
        (*nvo)->der=(*nvo)->izq;
        (*nvo)->izq=temp;
    } else if(funderdato[0]!='+' && (funizqdato[0]=='+' || funizqdato[0]=='-') && IsDigito(funizqderdato[0]) && IsDigito(funderdato[0])){
        //Nota: para este punto, la constante siempre esta en el subarbol izquierdo
        //(u+a)+b=u+(a+b)
        //      +
        //   +/-   b
        //  u  a
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));

        if(funizqdato[0]=='+'){
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der, Cadsum());
        } else {
            nvo[1]=CrearNodoArb(fun->der, fun->izq->der, Caddif());
        }
        nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], Cadsum());
    } else if((funizqdato[0]=='+' || funizqdato[0]=='-') && (funderdato[0]=='+' || funderdato[0]=='-') && IsDigito(funizqderdato[0]) && IsDigito(funderderdato[0])){
        //(u+a)+(v+b)=(u+z)+(a+b)
        //       +
        //   +/-  +/-
        //   u a  v b
        if(funizqdato[0]=='+' && funderdato[0]=='-'){
            nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
            nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->izq, Cadsum());
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der->der, Caddif());
        } else if(funizqdato[0]=='-' && funderdato[0]=='+'){
            nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
            nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->izq, Cadsum());
            nvo[1]=CrearNodoArb(fun->der->der, fun->izq->der, Caddif());
        }else if(funizqdato[0]=='-' && funderdato[0]=='-'){
            nvo=(NodoArb**)malloc(5*sizeof(NodoArb*));
            nvo[4]=CrearNodoArb(NULL, NULL, Cadcero());
            nvo[3]=CrearNodoArb(fun->izq->der, fun->der->der, Cadsum());
            nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->izq, Cadsum());
            nvo[1]=CrearNodoArb(nvo[4], nvo[3], Caddif());
        } else {
            nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
            nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->izq, Cadsum());
            nvo[1]=CrearNodoArb(fun->izq->der, fun->der->der, Cadsum());
        }
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Cadsum());
    } else if((funizqdato[0]=='+' || funizqdato[0]=='-') && funderdato[0]!='+' && IsDigito(funizqderdato[0]) && !IsDigito(funizqizqdato[0])){
        //(u+c)+v=(u+v)+c
        //      +
        //   +/-   v
        //   u c
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->izq, fun->der, Cadsum());
        nvo[0]=CrearNodoArb(nvo[1], fun->izq->der , funizqdato);
    } else if(funizqdato[0]!='+' && (funderdato[0]=='+' || funderdato[0]=='-') && IsDigito(funderderdato[0]) && !IsDigito(funderizqdato[0])){
        //u+(v+c)=(u+v)+c
        //      +
        //    u  +/-
        //       v c
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq, fun->der->izq, Cadsum());
        nvo[0]=CrearNodoArb(nvo[1], fun->der->der, funderdato);
    } else if(CompararArbol(fun->izq, fun->der)){
        //u+u=2*u
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(NULL, NULL, Caddos());
        nvo[0]=CrearNodoArb(nvo[1], fun->der, Cadprod());
    } else if(Iscero(funizqdato, 0) || Iscero(funderdato, 0)){
        if(Iscero(funderdato, 0))*nvo=fun->izq;//u+0=u
        else if(Iscero(funizqdato, 0)) *nvo=fun->der;//0+u=u
    } else if(Isln(funizqdato, 0) && Isln(funderdato, 0)){
        //ln(u)+lun(v)=ln(u*v)
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->izq, fun->der->izq, Cadprod());
        nvo[0]=CrearNodoArb(nvo[1], NULL, Cadln());
    } else if(funizqdato[0]=='-' && funizqizqdato[0]=='0' && funderdato[0]!='-'){
        //(0-u)+v=v-u
        nvo[0]=CrearNodoArb(fun->der, fun->izq->der, Caddif());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]!='-'){
        //u+(0-v)=u-v
        nvo[0]=CrearNodoArb(fun->izq, fun->der->der, Caddif());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]=='-' && funizqizqdato[0]=='0'){
        //(0-u)+(0-v)=0-(u+v)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Cadcero());
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der->der, Cadsum());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddif());
    } else {
        return (*nvo)=fun;
    }
    return *nvo;
}

NodoArb* SimplificarArbResta(NodoArb* fun){
    if(!fun) return NULL;
    NodoArb** nvo;
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    if(IsDigito(funizqdato[0]) && IsDigito(funderdato[0])){
        //a-b=c
        if(Convertir_Cad_Numero(funizqdato)<Convertir_Cad_Numero(funderdato)){
            nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
            nvo[2]=CrearNodoArb(NULL, NULL, Cadcero());
            nvo[1]=CrearNodoArb(NULL, NULL, Convertir_Numero_Cad(Convertir_Cad_Numero(funderdato)-Convertir_Cad_Numero(funizqdato)));
            nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddif());
        } else {
            nvo[0]=CrearNodoArb(NULL, NULL, Convertir_Numero_Cad(Convertir_Cad_Numero(funizqdato)-Convertir_Cad_Numero(funderdato)));
        }
    } else if(IsDigito(funizqdato[0]) && !IsDigito(funderdato[0])){
        //c-u=0-(u-c)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Cadcero());
        nvo[1]=CrearNodoArb(fun->der, fun->izq, Caddif());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddif());
    } else if(CompararArbol(fun->izq, fun->der)){
        //u-u=0
        nvo[0]=CrearNodoArb(NULL, NULL, Cadcero());
    } else if(Iscero(funderdato, 0)){
        //u-0=u
        *nvo=fun->izq;
    } else if(Isln(funizqdato, 0) && Isln(funderdato, 0)){
        //ln(u)-lun(v)=ln(u/v)
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->izq, fun->der->izq, Caddivi());
        nvo[0]=CrearNodoArb(nvo[1], NULL, Cadln());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]!='-'){
        //u-(0-v)=u+v
        nvo[0]=CrearNodoArb(fun->izq, fun->der->der, Cadsum());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]=='-' && funizqizqdato[0]=='0'){
        //0-u-(0-v)=v-u
        nvo[0]=CrearNodoArb(fun->der->der, fun->izq->der, Caddif());
    } else {
        return (*nvo)=fun;
    }
    return *nvo;
}

NodoArb* SimplificarArbMulti(NodoArb* fun){
    if(!fun) return NULL;
    NodoArb**nvo;
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    if(IsDigito(funizqdato[0]) && IsDigito(funderdato[0])){
        //a*b=c
        nvo[0]=CrearNodoArb(NULL, NULL, Convertir_Numero_Cad(Convertir_Cad_Numero(funizqdato)*Convertir_Cad_Numero(funderdato)));
    } else if(!IsDigito(funizqdato[0]) && IsDigito(funderdato[0])){
        //u*c=c*u
        (*nvo)=fun;
        NodoArb* temp=(*nvo)->der;
        (*nvo)->der=(*nvo)->izq;
        (*nvo)->izq=temp;
    } else if(Iscero(funderdato, 0) || Iscero(funizqdato, 0)){
        //u*0=0*u=0
        *nvo=CrearNodoArb(NULL, NULL, Cadcero());
    } else if(CompararArbol(fun->izq, fun->der)){
        //u*u=u^2
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(NULL, NULL, Caddos());
        nvo[0]=CrearNodoArb(fun->izq, nvo[1], Cadexpo());
    } else if(Isuno(funizqdato, 0) && !Isuno(funderdato, 0)){
        //1*u=u
        *nvo=fun->der;
    } else if(!Isuno(funizqdato, 0) && Isuno(funderdato, 0)){
        //u*1=u
        *nvo=fun->izq;
    } else if(funizqdato[0]!='*' && funderdato[0]=='*' && IsDigito(funderizqdato[0]) && IsDigito(funizqdato[0])){
        //Nota: para este punto, la constante siempre esta en el subarbol izquierdo
        //a*(b*u)=(a*b)*u
        //      *
        //    a   *
        //       b u
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq, fun->der->izq, Cadprod());
        nvo[0]=CrearNodoArb(nvo[1], fun->der->der, Cadprod());
    } else if(funizqdato[0]=='*' && funderdato[0]=='*' && IsDigito(funizqizqdato[0]) && IsDigito(funderizqdato[0])){
        //(a*u)*(b*v)=(a*b)*(u*z)
        //      *
        //    *   *
        //   a u b v
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->izq, Cadprod());
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der->der, Cadprod());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Cadexpo());
    } else if(funizqdato[0]=='*' && funderdato[0]!='*' && IsDigito(funizqizqdato[0]) && !IsDigito(funizqderdato[0])){
        //(c*u)*v=c*(u*v)
        //      *
        //    *   v
        //   c u
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der, Cadprod());
        nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], Cadprod());
    } else if(funizqdato[0]!='*' && funderdato[0]=='*' && IsDigito(funderizqdato[0]) && !IsDigito(funderderdato[0])){
        //u*(c*v)=c*(u*v)
        //      *
        //    u   *
        //       c v
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq, fun->der->der, Cadprod());
        nvo[0]=CrearNodoArb(fun->der->izq, nvo[1], Cadprod());
    } else if((funizqdato[0]=='^' && CompararArbol(fun->izq->izq, fun->der))){
        //u^v*u=u^(v+1)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Caduno());
        nvo[1]=CrearNodoArb(fun->izq->der, nvo[2], Cadsum());
        nvo[0]=CrearNodoArb(fun->der, nvo[1], Cadexpo());
    } else if((funderdato[0]=='^' && CompararArbol(fun->izq, fun->der->izq))){
        //u*u^v=u^(v+1)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Caduno());
        nvo[1]=CrearNodoArb(fun->der->der, nvo[2], Cadsum());
        nvo[0]=CrearNodoArb(fun->izq, nvo[1], Cadexpo());
    } else if((funizqdato[0]=='^' && funderdato[0]=='^' && CompararArbol(fun->izq->izq, fun->der->izq))){
        //(u^v)*(u^z)=u^(v+z)
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der->der, Cadsum());
        nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], Cadexpo());
    } else if(funizqdato[0]=='/' && funderdato[0]!='/'){
        //(u/v)*z=u*z/v
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->izq, fun->der, Cadprod());
        nvo[0]=CrearNodoArb(nvo[1], fun->izq->der, Caddivi());
    } else if(funizqdato[0]!='/' && funderdato[0]=='/'){
        //u*(v/z)=u*v/z
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq, fun->der->izq, Cadprod());
        nvo[0]=CrearNodoArb(nvo[1], fun->der->der, Caddivi());
    } else if(funizqdato[0]=='/' && funderdato[0]=='/'){
        //(u/v)*(z/w)=(u*z)/(v*w)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->izq, Cadprod());
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der->der, Cadprod());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddivi());
    } else if(funizqdato[0]=='-' && funizqizqdato[0]=='0' && funderdato[0]!='-'){
        //(0-u)*v=0-u*v
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Cadcero());
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der, Cadprod());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddif());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]!='-'){
        //u*(0-v)=0-u*v
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Cadcero());
        nvo[1]=CrearNodoArb(fun->izq, fun->der->der, Cadprod());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddif());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]=='-' && funizqizqdato[0]=='0'){
        //(0-u)*(0-v)=u*v
        nvo[0]=CrearNodoArb(fun->izq->der, fun->der->der, Cadprod());
    } else {
        (*nvo)=fun;
    }
    return *nvo;
}

NodoArb* SimplificarArbDivision(NodoArb* fun){
    if(!fun) return NULL;
    NodoArb**nvo;
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    if(IsDigito(funizqdato[0]) && IsDigito(funderdato[0])){
        //a/b=c
        if(!(Convertir_Cad_Numero(funizqdato)%Convertir_Cad_Numero(funderdato))){
            nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
            nvo[0]=CrearNodoArb(NULL, NULL, Convertir_Numero_Cad(Convertir_Cad_Numero(funizqdato)/Convertir_Cad_Numero(funderdato)));
        } else {
            return fun;
        }
    } else if(CompararArbol(fun->izq, fun->der)){
        //u/u=1
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=CrearNodoArb(NULL, NULL, Caduno());
    } else if(Iscero(funizqdato, 0)){
        //0/u=0
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=CrearNodoArb(NULL, NULL, Cadcero());
    } else if(Isuno(funderdato, 0)){
        //u/1=u
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        *nvo=fun->izq;
    } else if(Issen(funizqdato, 0) && Iscos(funderdato, 0) && CompararArbol(fun->izq->izq, fun->der->izq)){
        //senu/cosu=tanu
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=CrearNodoArb(fun->izq->izq, NULL, Cadtan());
    } else if(Iscos(funizqdato, 0) && Issen(funderdato, 0) && CompararArbol(fun->izq->izq, fun->der->izq)){
        //cosu/senu=cot
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=CrearNodoArb(fun->izq->izq, NULL, Cadcot());
    } else if((funizqdato[0]=='^' && CompararArbol(fun->izq->izq, fun->der))){
        //u^v/u=u^(v-1)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Caduno());
        nvo[1]=CrearNodoArb(fun->izq->der, nvo[2], Caddif());
        nvo[0]=CrearNodoArb(fun->der, nvo[1], Cadexpo());
    } else if((funderdato[0]=='^' && CompararArbol(fun->izq, fun->der->izq))){
        //u/u^v=u^(1-v)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Caduno());
        nvo[1]=CrearNodoArb(nvo[2], fun->der->der, Caddif());
        nvo[0]=CrearNodoArb(fun->izq, nvo[1], Cadexpo());
    } else if((funizqdato[0]=='^' && funderdato[0]=='^' && CompararArbol(fun->izq->izq, fun->der->izq))){
        //(u^v)/(u^z)=u^(v-z)
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der->der, Caddif());
        nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], Cadexpo());
    } if(funizqdato[0]=='/' && funderdato[0]!='/'){
        //(a/b)/c=a/b*c
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der, Cadprod());
        nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], Caddivi());
    } else if(funizqdato[0]!='/' && funderdato[0]=='/'){
        //a/(b/c)=a*c/b
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq, fun->der->der, Cadprod());
        nvo[0]=CrearNodoArb(nvo[1], fun->der->izq, Caddivi());
    } else if(funizqdato[0]=='/' && funderdato[0]=='/'){
        //(a/b)/(c/d)=a*d/b*c
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(fun->izq->izq, fun->der->der, Cadprod());
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der->izq, Cadprod());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddivi());
    } else if(funizqdato[0]=='-' && funizqizqdato[0]=='0' && funderdato[0]!='-'){
        //(0-u)/v=0-(u/v)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Cadcero());
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der, Caddivi());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddif());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]!='-'){
        //u/(0-v)=0-(u/v)
        nvo=(NodoArb**)malloc(3*sizeof(NodoArb*));
        nvo[2]=CrearNodoArb(NULL, NULL, Cadcero());
        nvo[1]=CrearNodoArb(fun->izq, fun->der->der, Caddivi());
        nvo[0]=CrearNodoArb(nvo[2], nvo[1], Caddif());
    } else if(funderdato[0]=='-' && funderizqdato[0]=='0' && funizqdato[0]=='-' && funizqizqdato[0]=='0'){
        //(0-u)/(0-v)=u/v
        nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
        nvo[0]=CrearNodoArb(fun->izq->der, fun->der->der, Caddivi());
    } else {
        return (*nvo)=fun;
    }
    return *nvo;
}

NodoArb* SimplificarArbPoten(NodoArb* fun){
    if(!fun) return NULL;
    NodoArb**nvo;
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    if(IsDigito(funizqdato[0]) && IsDigito(funderdato[0])){
        //a^b=c
        nvo[0]=CrearNodoArb(NULL, NULL, Convertir_Numero_Cad(pow(Convertir_Cad_Numero(funizqdato),Convertir_Cad_Numero(funderdato))));
    } else if(Isuno(funderdato, 0)){
        //u^1=u
        *nvo=fun->izq;
    } else if(Iscero(funderdato, 0)){
        //u^0=1
        *nvo=CrearNodoArb(NULL, NULL, Caduno());
    } else if(funizqdato[0]=='^'){
        //u^v^z=(u^v)^z=u^(v*z)
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->der, fun->der, Cadprod());
        nvo[0]=CrearNodoArb(fun->izq->izq, nvo[1], Cadexpo());
    } else {
        (*nvo)=fun;
    }
    return *nvo;
}

NodoArb* SimplificarArbln(NodoArb* fun){
    if(!fun) return NULL;
    NodoArb**nvo;
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    if(Ise(funizqdato, 0)){
        //ln(e)=1
        *nvo=CrearNodoArb(NULL, NULL, Caduno());
    } else if(Isuno(funizqdato, 0)){
        //ln(1)=0
        *nvo=CrearNodoArb(NULL, NULL, Cadcero());
    }else if(funizqdato[0]=='^'){
        //ln(u^v)
        nvo=(NodoArb**)malloc(2*sizeof(NodoArb*));
        nvo[1]=CrearNodoArb(fun->izq->izq, NULL, Cadln());
        nvo[0]=CrearNodoArb(fun->izq->der, nvo[1], Cadprod());
    } else {
        (*nvo)=fun;
    }
    return *nvo;
}

NodoArb *SimplificarArbolFuncion(NodoArb *fun){
    if(!fun) return (NodoArb*)NULL;
    NodoArb **nvo;
    fun->izq=SimplificarArbolFuncion(fun->izq);
    fun->der=SimplificarArbolFuncion(fun->der);
    nvo=(NodoArb**)malloc(1*sizeof(NodoArb*));
    if(fundato[0]=='+'){
        *nvo=SimplificarArbSuma(fun);
    } else if(fundato[0]=='-'){
        *nvo=SimplificarArbResta(fun);
    } else if(fundato[0]=='*'){
        *nvo=SimplificarArbMulti(fun);
    } else if(fundato[0]=='/'){
        *nvo=SimplificarArbDivision(fun);
    } else if(fundato[0]=='^'){
        *nvo=SimplificarArbPoten(fun);
    } else if(Isln(fundato, 0)){
        *nvo=SimplificarArbln(fun);
    } else {
        (*nvo)=fun;
    }
    //free(fun);
    return *nvo;
}

NodoArb *SimplificarFun(NodoArb *fun){
    NodoArb* fun1, *fun2;
    fun1=fun;
    for(int j=0; j<20; j++){
        fun2=fun1;
        fun1=SimplificarArbolFuncion(fun2);
    }
    return fun1;
}