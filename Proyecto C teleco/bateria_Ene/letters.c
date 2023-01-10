#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "operation.h"
#include "inout.h"

int main () 
{
	struct Abonados *head   = NULL;    // comienzo de la lista
	struct Mensajes    *cabeza = NULL;    // comienzo de la lista
  
	int a=0, conf, num;
	char buffer[256], rubbish[256], ans;

//localiza la informacion al empezar
	p_init (&head, &cabeza);

	plano     ('+', 60);
	rotulo ('+', 60);
	plano     ('+', 60);
	printf   ("\n");

  
	do 
	{
		printf ("A) Dar de alta un abonado\nE) Escribir un mensaje\nL) Listar los mensajes para un abonado\nB) Borrar un mensaje\nJ) Dar de baja a un abonado\n\nS) Salir del programa\n\nElige una opcion: ");

		fgets  (buffer, 256, stdin);
    	num = sscanf (buffer, "%c %s", &ans, rubbish);
 
    	ans = toupper(ans);

    	if (num != 2)
		{
    		switch (ans)
			{    
      				case 'A':
				printf     ("\nSuscribir\n\n");
				suscribir (&head);
				break;
      
      				case 'E':
				printf  ("\nEscribir\n\n");
				escribir (&head, &cabeza);
				break;
      
      				case 'L':
				printf ("\nListar\n\n");
				listar (&head, &cabeza);
				break;
      
      				case 'B':
				printf  ("\nBorrar\n\n");
				borrar (&head, &cabeza);
				break;

			    	case 'J':
				printf ("\nRetirar\n\n");
				retirar (&head, &cabeza);
				break;
      
					case 'S':
    			printf ("\nSalir\n\n");		
    			conf = confirmar ();	// 0-> Si -y asi sale
            				       // 1-> No  -y asi no sale
      			if (conf == 0)
				{
					p_exit (&head, &cabeza);
					a = 1;
      			}
      			break;

			    	default:
				printf ("\nHas elegido una opcion invalida\n\n");
				a = 0;
      		}
    	}
    	else
		{
      		printf ("\nHas elegido una opcion invalida\n\n");
      		a = 0;
    	}
  	}while (a==0);

 	return 0;
}
