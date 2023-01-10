#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#include "operation.h"
#include "inout.h"


// Funciones principales
	void suscribir   (struct Abonados **head);
	void escribir      (struct Abonados **head, struct Mensajes **cabeza);
	void listar       (struct Abonados **head, struct Mensajes **cabeza);
	void borrar      (struct Abonados **head, struct Mensajes **cabeza);
	void retirar (struct Abonados **head, struct Mensajes **cabeza);

	void p_exit       (struct Abonados **head, struct Mensajes **cabeza);
	void p_init       (struct Abonados **head, struct Mensajes **cabeza);

// Funciones comunes
	int check_identity (int identidad, struct Abonados *ptr);
	int check_name     (char *nombre,   struct Abonados *ptr);

// borrar Funcion
	void erase_some_nodes (struct Mensajes **cabeza, int receiv_identity, int mensj_num);

// retirar Funcion
	void erase_all_nodes  (struct Mensajes **cabeza, int receiv_identity);
	void unregist         (struct Abonados **head, int sub_identity);




//---------------------------------------------------------------------------------------------------------------
//-------------------------------------------Funciones principales-----------------------------------------------
//---------------------------------------------------------------------------------------------------------------



void suscribir (struct Abonados **head)
{
	char nombre[15];

	struct Abonados *pointer;
	Sub_struct *new = malloc (sizeof (Sub_struct));

  // Escanea la memoria
	lee_cadena ("Nombre del abonado", nombre, 16);

	if (*head == NULL )
	{ // Si la lista esta vacia (*head is null) ,*head apuntara a nuevo
    	new->identidad = 1;
    	new->cuenta = 0;
    	strcpy (new->nombre, nombre);

    	new->next = NULL;
    	*head = new;
  	}
	else
	{
    	pointer = *head;
    
    	while (pointer->next != NULL)
		{ //Si ya hay informacion , va hasta el final de la lista
    		pointer = pointer->next;
    	}
    	new->identidad = pointer->identidad + 1;
    	new->cuenta = 0;
    	strcpy (new->nombre, nombre);

    	new->next = NULL;
    	pointer->next = new;
  	}
  	muestra_abonado (new);
  	return;
}



void escribir (struct Abonados **head, struct Mensajes **cabeza) 
{
	char texto[100];
	int MAX, sender_identity, receiv_identity, cmp;

	struct Abonados *pointer;
	struct Mensajes    *puntero;
  
	Mess_struct *nuevo = malloc (sizeof (Mess_struct));

	if (*head == NULL)
	{
    	printf ("No hay abonados \n\n");
  	}
  	else 
	{
    	pointer = *head;
    
    	while (pointer->next != NULL)
		{
      		pointer = pointer->next;
    	}
    	MAX = pointer->identidad;    

    	sender_identity = lee_entero ("Identidad del emisor", MAX);							       
    	cmp  = check_identity (sender_identity, *head);

    	if (cmp == 0)
		{
      		printf ("\nAbonado desconocido\n");
    	}
    	else 
		{
			receiv_identity = lee_entero("\nIdentidad del receptor", MAX);
      		cmp = check_identity (receiv_identity, *head);

      		if (cmp == 0)
			{
				printf ("\nAbonado desconocido\n");
      		}
      	else 
		{
			lee_cadena ("\nMensaje de texto", texto, 101);

			strcpy (nuevo->texto, texto);
	
			nuevo->emisor   = sender_identity;
			nuevo->destino = receiv_identity;

			if (*cabeza == NULL)
			{
	  			nuevo->next = NULL;
	  			*cabeza = nuevo;
			}
			else 
			{
	  			puntero = *cabeza;

	  		while (puntero->next != NULL)
			{
	    		puntero = puntero->next;
	  		}

	  		nuevo->next   = NULL;
	  		puntero->next = nuevo;
			}

	
	// Actualizando la cuenta del abonado dado
			pointer = *head;
			while (pointer != NULL)
			{
	  			if (pointer->identidad == receiv_identity)
				{
	    			pointer->cuenta += 1;
	  			}
	  			pointer = pointer->next;
			}

			printf ("\nMensaje registrado:\n");
			muestra_extensa(nuevo);	
      	}
    	}
  	}
  	return;
}



void listar (struct Abonados **head, struct Mensajes **cabeza)
{
	struct Abonados *pointer;
	struct Mensajes    *puntero;

  
	char nombre[15];
	int receiv_identity, cmp;

	if (*head == NULL)
	{
    	printf ("No hay abonados\n\n");
  	}
  	else 
	{
    	pointer = *head;
    	puntero = *cabeza;
    
    	lee_cadena ("Identidad del destino", nombre, 16);
    	cmp = check_name (nombre, *head);

    	if (cmp == 0)
		{
      		printf ("\nAbonado desconocido\n\n");
    	}
    	else
		{
      		printf ("\nMensajes para %s:\n", nombre);

      		while (pointer != NULL)
			{
				if ((strcmp (pointer->nombre, nombre)) == 0)
				{
	  				receiv_identity = pointer->identidad;
	  				break;
				}
				pointer = pointer->next;
      		}	   

      		while (puntero != NULL)
			{	
				if (puntero->destino == receiv_identity)
				{
	  				muestra_corta (puntero);
				}
				puntero = puntero->next;
      		}
      		printf ("\n");
    	}
  	}
  	return;
}



void borrar (struct Abonados **head, struct Mensajes **cabeza)
{
	struct Abonados *pointer;

  	int MAX, receiv_identity, mensj_position, cmp, NUM_MENSJ = 0;

	if (*head == NULL)
	{
    	printf ("No hay abonados\n\n");
  	}
  	else
	{
    	pointer = *head;

    	while (pointer->next != NULL)
		{
      		pointer = pointer->next;
    	}
    
    	MAX = pointer->identidad;

    	receiv_identity = lee_entero ("Identidad del destino", MAX);
   		cmp = check_identity (receiv_identity, *head);
    
    	if (cmp == 0)
		{
      		printf ("\nAbonado desconocido\n");
    	}
    	else
		{
      		pointer = *head;

      	while (pointer->identidad != receiv_identity)
		{
			pointer = pointer->next;
      	}
      	NUM_MENSJ = pointer->cuenta;

      
      	switch (NUM_MENSJ)
		{
      			case 0: 
			printf ("\nNo se han encontrado mensajes\n\n");
			break;
	
      			default:
  			mensj_position = lee_entero ("\nPosicion del mensaje", NUM_MENSJ);
			erase_some_nodes (cabeza, receiv_identity, mensj_position);

	// Actualizando cuenta del abonado dado
			pointer = *head;
			while (pointer->identidad != receiv_identity)
			{
	  			pointer = pointer->next;
			}
			pointer->cuenta -= 1;
	
			printf ("\nMensaje borrado\n\n");
			break;
      	}
    	}
  	}
	return;
}



void retirar (struct Abonados **head, struct Mensajes **cabeza)
{
	struct Abonados *pointer;
  
	int MAX, sub_identity, cmp;
  
	if (*head == NULL)
	{
    	printf ("No hay abonados\n\n");
  	}
  	else
	{
    	pointer = *head;

		while (pointer->next != NULL)
		{
      		pointer = pointer->next;
    	}

    	MAX = pointer->identidad;

    	sub_identity = lee_entero ("Identidad del abonado", MAX);
    	cmp = check_identity (sub_identity, *head);
    
    	switch (cmp)
		{
    			case 0:
      		printf ("\nAbonado desconocido\n");
      		break;

    			default:
       // 1;borra todos los mensajes del usuario dado
      		erase_all_nodes (cabeza, sub_identity);
      // 2; borra el abonado dado
      		unregist (head, sub_identity);
     // 3;informa al usuario
      		printf ("\nAbonado retirado\n\n");
      		break;
    	}
  	}
  	return;
}


void p_exit (struct Abonados **head, struct Mensajes **cabeza)
{
	struct Abonados *current;
	struct Mensajes    *actual;

	current = *head;
	actual  = *cabeza;

	FILE *file_s, *file_m;

// 1; localiza los abonados en el archivo
	file_s = fopen ("abonados.txt" , "w");

	if (*head != NULL)
	{
    	while (current != NULL)
		{
      	fprintf (file_s,"%d %d %s\n", current->identidad, current->cuenta, current->nombre);
      	current = current->next;
    	}
  	}
  	fclose (file_s);

  // 2; localiza los mensajes en el archivo
  	file_m = fopen ("mensajes.txt", "w");

	if (*head != NULL)
	{
    	while (actual != NULL)
		{
      		fprintf (file_m, "%d %d %s\n", actual->emisor, actual->destino, actual->texto);
      		actual = actual->next;
    	}
  	}
  	fclose (file_m);

  // 3; sal del programa  
  	return;
}



void p_init (struct Abonados **head, struct Mensajes **cabeza)
{
	struct Abonados *pointer;
  	struct Mensajes    *puntero;

  	pointer = *head;
  	puntero = *cabeza;

  
	char line[128];
  
	FILE *file_s, *file_m;

//  Mira y copia el archivo abonados , si es que existe
  	file_s = fopen ("abonados.txt", "r");

  	if (file_s == NULL);
  	else
	{
		while (fgets(line, sizeof(line), file_s) != NULL)
		{
      		Sub_struct *current = malloc(sizeof(Sub_struct));
      
      		sscanf(line,"%d %d %s", &current->identidad, &current->cuenta, current->nombre);
      
      		if (*head == NULL)
			{
				*head = current;
				current->next = NULL;
      		}
      		else
			{
				pointer = *head;
				while (pointer->next != NULL)
				{
	  				pointer = pointer->next;
				}
				pointer->next = current;
				current->next = NULL;
      		}
    	}
    	fclose(file_s);
  	}

// Mira y copia el archivo mensajes , si es que existe
	file_m = fopen("mensajes.txt", "r");

	if (file_m == NULL);
	else
	{
		while (fgets(line, sizeof(line), file_m) != NULL)
		{
      		Mess_struct *actual = malloc(sizeof(Mess_struct));
			sscanf (line, "%d %d %s", &actual->emisor, &actual->destino, actual->texto);

      		if (*cabeza == NULL)
			{
				*cabeza = actual;
				actual->next = NULL;
      		}
      		else
			{
			puntero = *cabeza;

			while (puntero->next != NULL)
			{
	  			puntero = puntero->next;
			}			
			puntero->next = actual;
			actual->next  = NULL;
      		}
    	}
    	fclose(file_m);
  	}
  
  	return;
}

//---------------------------------------------------------------------------------------------------------------
//----------------------------------Funciones Auxiliares---------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------


int check_identity (int identidad, struct Abonados *ptr)
{ 
	int check = 0;
    
	while (ptr != NULL)
	{
    	if (identidad == ptr->identidad)
		{
      		check = 1;
    	}
    	ptr = ptr->next;
  	}
  	return check;
}


int check_name (char *nombre, struct Abonados *ptr)
{
	int check = 0, cmp;
  
	while (ptr != NULL)
	{
    	cmp = strcmp (ptr->nombre, nombre);

    	if (cmp == 0)
		{
      		check = 1;
    	}
    	ptr = ptr->next;
  	}
  	return check;
}
  

  
void erase_some_nodes (struct Mensajes **cabeza, int receiv_identity, int mensj_num){

	struct Mensajes *puntero, *previo;
	puntero = *cabeza;
	previo  = *cabeza;
  
	int cuenta = 0;

	while (puntero != NULL)
	{
		if (puntero->destino == receiv_identity)
		{
      		cuenta += 1;
      		if (cuenta == mensj_num)
			{
				if (previo == *cabeza)
				{
	  				*cabeza = puntero->next;
	  				free (puntero);
				}
				else
				{
	  				previo->next = puntero->next;
	  				free(puntero);
				}
      		}
    	}

    	previo  = puntero;
    	puntero = puntero->next;
  	}
  
	return;
}



void erase_all_nodes (struct Mensajes **cabeza, int receiv_identity)
{
	struct Mensajes *puntero, *previo;
	puntero = *cabeza;
	previo  = *cabeza;
  
    while (puntero != NULL)
	{
    	if (puntero->destino == receiv_identity)
		{
      		if (previo == *cabeza)
			{
				*cabeza = puntero->next;
				free(puntero);
      		}
      		else
			{
				previo->next = puntero->next;
				free(puntero);
      		}
    	}    
    	previo  = puntero;
    	puntero = puntero->next;
  	}
    
	return;
}


void unregist (struct Abonados **head, int sub_identity)
{
	struct Abonados *pointer, *priv;
	pointer = *head;
	priv    = *head;


	while (pointer != NULL)
	{
		if (pointer->identidad == sub_identity)
		{
			if (priv == *head)
			{
				*head = pointer->next;
				free(pointer);
      		}
      		else
			{
				priv->next = pointer->next;
				free(pointer);
      		}
    	}
    	else
		{
      		priv    = pointer;
      		pointer = pointer->next;
    	}
  	}
  	return;
}
