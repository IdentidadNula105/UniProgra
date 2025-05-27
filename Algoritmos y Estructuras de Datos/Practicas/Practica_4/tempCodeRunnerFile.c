exp2=BuildArb(exp1);
    printf("Recorrido del arbol en postorden:");
    imprimeArb(exp2, &impCad);
    
    ARBNL(Derivador(exp2), &p);
    res=NLCAD(p);
    printf("\nLa derivada es: ");
    //imprimeArb(Derivador(exp2), &impCad);
    printf("%s", ((Expifj*)Infija(res)->dato)->exp);