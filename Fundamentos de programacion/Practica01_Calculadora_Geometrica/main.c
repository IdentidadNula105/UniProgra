#include <stdio.h>
#include <windows.h>
#include "LR/LineaRecta.h"
#include "Circ/Circunferencia.h"
#include "Cp/CoorPolar.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int op=0;
    int resultado=0;
    do{
        printf("\nMENU PRINCIPAL");
        printf("\n1. La Linea Recta");
        printf("\n2. La circunferencia");
        printf("\n3. Coordenadas Polares");
        printf("\n4. Salir");
        //hola
        while (1) {
        printf("\nEscoja una opción [1-4]: ");
        resultado = scanf("%d", &op);
        if (resultado == 1) {
            // Entrada válida
            break;  // Salir del bucle
        } else {
            // Entrada inválida
            printf("\nOpción inválida.\n");
            
            // Limpiar el buffer de entrada
            while (getchar() != '\n');  // Leer hasta el salto de línea
        }
        }

        switch (op){
        //LR
        case 1:
        MenuLR();
        break;
        
        //Cir
        case 2:
        MenuC();
        break;

        //CP
        case 3:
        MenuCP();
        break;

        case 4:
        printf("Saliendo del programa...");
        break;
        
        default:
        printf("\nOpción inválida.\n");
        break;
        }
    } while (op != 4);
    return 0;
}
