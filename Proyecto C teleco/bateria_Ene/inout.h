// Libreria de inout.c

void rotulo (char charac, int length);
void plano     (char charac, int length);

void muestra_abonado (Sub_struct  *ptr);
void muestra_corta      (Mess_struct *ptr);
void muestra_extensa  (Mess_struct *ptr);

void lee_cadena (char *promp, char *string, int MAX);

int lee_entero (char *prompt, int MAX);
int confirmar     (void);
