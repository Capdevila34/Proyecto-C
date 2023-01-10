// Libreria de operation.c


typedef struct Abonados 
{
	int  identidad;    // entero de 32-bit
	int  cuenta;       // entero de 32-bit
	char nombre[15];    // cadena entre 1 y 15

	struct Abonados *next;

} Sub_struct;       // Para crear estos structs


typedef struct Mensajes 
{
	int  emisor;      // entero de 32-bit
	int  destino;    // entero de 32-bit
	char texto[100];   // cadena entre 1 y 100

	struct Mensajes *next;

} Mess_struct;      // Para crear estos structs


// Funciones
void suscribir      (struct Abonados **head);
void escribir       (struct Abonados **head, struct Mensajes **cabeza);
void listar         (struct Abonados **head, struct Mensajes **cabeza);
void borrar         (struct Abonados **head, struct Mensajes **cabeza);
void retirar 		(struct Abonados **head, struct Mensajes **cabeza);
void p_exit      	(struct Abonados **head, struct Mensajes **cabeza);
void p_init         (struct Abonados **head, struct Mensajes **cabeza);
