#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "operation.h"


//  Funcion Marco
	void rotulo (char charac, int length);
	void plano     (char charac, int length);

// Funcion Salida
	int confirmar (void);

// Funciones tipo Get
	int  lee_entero (char *prompt, int MAX);
	void lee_cadena  (char *promp,  char *string, int MAX);

// Muestra Funciones
	void muestra_abonado (Sub_struct  *ptr);
	void muestra_extensa  (Mess_struct *ptr);
	void muestra_corta      (Mess_struct *ptr);



//-------------------------------------------------------------------------------------------------------------------------------------
									//Funciones tipo marco
//-------------------------------------------------------------------------------------------------------------------------------------


void rotulo (char charac, int length)
{
	int NB, i=0;
	char NAME[] = "CARTAS";

	NB = ((length-2)-(strlen(NAME)));

	printf ("%c", charac);
	for (i=0; i<(NB/2); i++)
	{
    	printf (" ");
  	}
  	printf ("%s", NAME);
  	for (i=0; i<(NB/2); i++)
	{
    	printf(" ");
  	}
  	printf ("%c\n", charac);

	return;
};


void plano (char charact, int length)
{
	int i;

	printf("%c", charact);
	for ( i=0; i<=(length-2); i++)
	{
    	printf ("%c", charact);
  	}
  	printf ("\n");
  	return;
};


//-------------------------------------------------------------------------------------------------------------------------------------
									//Funcion tipo confirmar
//-------------------------------------------------------------------------------------------------------------------------------------


int confirmar (void)
{
	int exit = 2, num_allocations;
	char buffer[256], rubbish[256], answer;

	printf ("\nSalir\n");

	do
	{
    	printf ("\nSeguro que desea salir del programa? (s /n): ");
    
    	fgets (buffer, 256, stdin);
    	num_allocations = sscanf (buffer, "%c %s", &answer, rubbish);
    
    	answer = toupper(answer);

    	if (num_allocations == 1)
		{
      		switch (answer)
			{
      				case 'S':
				exit = 0;
				break;

      				case 'N':
				exit = 1;
				printf ("\n");
				break;

      				default:
				exit = 2;
				break;
      		}
    	}    
  	}while(exit == 2);

  	return exit;
}



//-------------------------------------------------------------------------------------------------------------------------------------
									//Funcion tipo get
//-------------------------------------------------------------------------------------------------------------------------------------


void lee_cadena (char *promp, char *string, int MAX)
{
	char buffer[256], rubbish[256];
	int length, num_allocations, ok = 0;

	do
	{ 
    	printf ("%s (1-%d car):", promp, (MAX-1));

    	fgets (buffer, 256, stdin);
    	length = strlen (buffer);

    	if (length > MAX)
		{
      		printf ("\nLongitud Excesiva\n\n");
      		ok = 0;
    	}
    	else if (length == 1)
		{  
      		printf ("\nLongitud Nula\n\n");
      		ok = 0;
    	}
    	else
		{
      		num_allocations = sscanf (buffer, "%s %s", string, rubbish);

      		if (num_allocations == 2)
			{
				printf ("Hay espacios en blanco\n");
				ok = 0;
      		}
      		else if (num_allocations == 0)
			{
				printf ("\nLongitud Nula\n\n");
      		}
      		else
			{
				ok = 1;
      		}
    	}
  	}while (ok != 1);

  	return;
}



int lee_entero (char *prompt, int MAX)
{
	char buffer[256], rubbish[256];
	int number, num_allocations, ok = 0;

	do
	{
    	printf ("%s [1-%d]: ", prompt, MAX);  // Hace que MAX sea el numero maximo de enteros permitidos
    	fgets (buffer, 256, stdin);
    	num_allocations =  sscanf (buffer,"%d %s", &number, rubbish);

    	if (num_allocations == 1)
		{
      		if ((number<1) || (number>MAX))
			{ 
				printf ("\nValor Incorrecto\n\n");
				ok = 0;
      		}
      		else
			{
				ok = 1;
      		}
    	}
    	else
		{
      		printf ("\nValor Incorrecto\n\n");
      		ok = 0;
    	}
  	}while (ok != 1);

  	return number;
}


//-------------------------------------------------------------------------------------------------------------------------------------
									//Funcion tipo muestra
//-------------------------------------------------------------------------------------------------------------------------------------

void muestra_abonado (Sub_struct *ptr)
{
   printf ("\nSuscriptor registrado:\n#%3d:%15s\n\n", ptr->identidad, ptr->nombre);

   return;
}



void muestra_corta (Mess_struct *ptr)
{
	printf ("#%3d:%3d:%.12s\n", ptr->emisor, ptr->destino, ptr->texto);   

	return;
}




void muestra_extensa(Mess_struct *ptr)
{
	printf ("\n> Emisor: %d\n> Destino: %d\n> Texto: %s\n\n", ptr->emisor, ptr->destino, ptr->texto);

	return;
}
