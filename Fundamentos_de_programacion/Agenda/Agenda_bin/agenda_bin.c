#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define ARCHIVO "agenda.dat"

typedef struct persona
{
	char nombre[51];
	char appaterno[51];
	char apmaterno[51];	
	int edad;
	char CURP[21];
	float peso;
}persona;


typedef struct agenda
{
	persona p[MAX];
	int n;
}agenda;

int MuestraMenuPrincipal(void);
void CapturaPersona(persona *p);
void MostrarPersona(persona *p);
void InsertaPersona(agenda *a);
void EliminaPersona(agenda *a);
void ModificaPersona(agenda *a);
void BuscarPersona(agenda *a);
void GuardarAgenda(agenda *a);
void CargarAgenda(agenda *a);
void MostrarAgenda(agenda *a);

int main(void)
{
	agenda A;
	CargarAgenda(&A);
	int opc;
	while(1)
	{
		opc=MuestraMenuPrincipal();
		switch(opc)
		{
			//1.- Insertar Persona
			case 1:
				InsertaPersona(&A);
			break;
			//2.- Buscar Persona
			case 2:
			
			break;
			//3.- Modificar Persona
			case 3:
			
			break;
			//4.- Eliminar Persona
			case 4:
			
			break;
			//5.- Mostrar agenda
			case 5:
				MostrarAgenda(&A);
			break;
			//6.- Salir
			case 6:
				GuardarAgenda(&A);
				exit(0);
			break;
		}
	}
}


int MuestraMenuPrincipal(void)
{
	int r;
	do
	{
		printf("\n 1.- Insertar Persona");
		printf("\n 2.- Buscar Persona");
		printf("\n 3.- Modificar Persona");
		printf("\n 4.- Eliminar Persona");
		printf("\n 5.- Mostrar agenda");
		printf("\n 6.- Salir\n");
		
		scanf("%d",&r);
		if(r>6||r<1)
		{
			printf("\n%d Opcion no valida\n\n",r);
		}
	}while(r>6||r<1);
	
	return r;
}

void CargarAgenda(agenda *a)
{
	FILE *archivo; 
	int i;
	archivo = fopen(ARCHIVO,"rb");
	if (archivo != NULL) 
	{
		fseek(archivo, 0, SEEK_SET);
		fread(a,sizeof(agenda),1,archivo);
		fclose(archivo);
	}
	else
	{
		a->n=0;
	}
	return;
}


void GuardarAgenda(agenda *a)
{
	FILE *archivo; 
	archivo = fopen(ARCHIVO,"wb");
	fseek(archivo, 0, SEEK_SET);
	fwrite(a,sizeof(agenda),1,archivo);
	fclose(archivo);
	return;
}


void MostrarAgenda(agenda *a)
{
	int i;
	for(i=0;i<a->n;i++)
	{
		printf("\n%s",a->p[i].nombre);
		printf("\t%s",a->p[i].appaterno);
		printf("\t%s",a->p[i].apmaterno);
		printf("\t%d",a->p[i].edad);
		printf("\t%s",a->p[i].CURP);
		printf("\t%f\n",a->p[i].peso);
	}
	return;
}

void InsertaPersona(agenda *a)
{
	int num_p=a->n;
	printf("\nDame el nombre: ");
	scanf("%s",a->p[num_p].nombre);
	printf("\nDame el appaterno: ");
	scanf("%s",a->p[num_p].appaterno);
	printf("\nDame el apmaterno: ");
	scanf("%s",a->p[num_p].apmaterno);
	printf("\nDame la edad: ");
	scanf("%d",&(a->p[num_p].edad));
	printf("\nDame el CURP: ");
	scanf("%s",a->p[num_p].CURP);
	printf("\nDame el peso: ");
	scanf("%f",&(a->p[num_p].peso));
	a->n++;
	return;
}
