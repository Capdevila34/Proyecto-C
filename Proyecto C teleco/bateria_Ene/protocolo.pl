#!/usr/bin/perl
#
# Recibe un argumento: el nombre del programa que queremos evaluar, y que
# contiene la versión de enero del proyecto Cartas
#
# Asume la existencia de un Makefile con reglas para generar un objetivo
# con nombre = letters
#
# De no ser así, es decir, si no se genera dicho programa, sale dando el
# correspondiente mensaje de error.
#
#
# Autor: Pedro Rodríguez
#

use v5.22;
use File::Copy;
use experimental qw(smartmatch);

# use utf8;


# Funcion compara_archivos()
# Recibe dos argumentos: los nombres de los dos archivos que se quiere comparar
#
sub compara_archivos {
  if (@_ != 2) {
    say <<'end_of_ca_help_message'; 
Mal uso de la funcion compara_archivos()
uso: compara_archivos (modelo archivo);
          modelo    nombre del modelo con el que se quiere comparar el archivo
          archivo   nombre del archivo que se quiere comparar con el modelo
end_of_ca_help_message
    exit 1;
  }

  my ${modelo} = shift @_;
  my ${archivo} = shift @_;

  say "\nComparamos el fichero ${archivo} generado por el programa";
  say "que hemos evaluado con el ${modelo} que debería haberse generado,";
  say "y mostramos las diferencias (si las hay)\n";

  my ${estado} = 0;
  system ("diff -Bw ${modelo} ${archivo}");
  if ($? == 0) {
    say "El fichero [01;32m${archivo}[00m es correcto";
  }
  else {
    say "El fichero [01;32m${archivo}[00m [01;31mNO[00m es correcto";
    ${estado} = 1;
  }

  say "\nPulsa enter para continuar...";
  my ${continuar} = <STDIN>;
  return ${estado};
}

# Funcion mueve_y_compara()
# Recibe dos argumentos: los nombres de los dos archivos que se quiere comparar
# tras asegurarse de que el que se quiere evaluar existe
#
sub mueve_y_compara {
  if (@_ != 2) {
    say <<'end_of_mc_help_message'; 
Mal uso de la funcion mueve_y_compara()
uso: mueve_y_compara (modelo archivo);
         modelo    nombre del modelo con el que se quiere comparar el archivo
         archivo   nombre del archivo que se quiere comparar con el modelo
end_of_mc_help_message
    exit 1;
  }

  my ${modelo} = shift @_;
  my ${archivo} = shift @_;
  my ${estado} = 0;

  if ( -e "${archivo}") {
    rename "${archivo}", "mis_${modelo}";
    ${archivo}="mis_${modelo}";
    ${estado} = compara_archivos ("${modelo}", "${archivo}");
  }
  else {
    say "El fichero [01;31m${archivo}[00m no existe";
    say "Pulsa enter para continuar...";
    my ${continuar} = <STDIN>;
    ${estado} = 1;
  }
  return ${estado};
}

# Funcion prueba_existe()
# Recibe dos argumentos: el nombre del archivo que se quiere comprobar si
# existe y el del modelo de archivo que sería si existiese
#
sub prueba_existe {
  if (@_ != 2) {
    say <<'end_of_pe_help_message'; 
Mal uso de la funcion prueba_existe()
uso: prueba_existe (modelo archivo);
          modelo    nombre del modelo de archivo que sería si existiese
          archivo   nombre del archivo que se quiere comprobar si existe
end_of_pe_help_message
    exit 1;
  }

  my ${modelo} = shift @_;
  my ${archivo} = shift @_;

  say "\nComprobamos que el programa no ha generado un fichero [01;32mmis_${modelo}[00m\n";

  my ${estado} = 0;

  if ( -e "${archivo}") {
    rename "${archivo}", "mis_${modelo}";
    ${archivo}="mis_${modelo}";
    say "El fichero [01;32m${archivo}[00m [01;31mNO debería existir[00m\n";
    say "Pulsa enter para continuar...";
    my ${continuar} = <STDIN>;
    ${estado} = 1;
  }
  return ${estado};
}


if (@ARGV != 1) {
say <<'end_of_help_message'; 
   uso: $0 programa
          programa    nombre del programa que queremos evaluar

end_of_help_message
exit 1;
}


# El protocolo, propiamente dicho
#
my ${programa} = shift @ARGV;
my ${pruebas_falladas}=0;
my ${total_pruebas}=10;

say "\nProtocolo para evaluar un programa que contiene la versión de enero";
say "del proyecto Cartas\n";

say "El programa se llama: \"${programa}\"\n";

if ( ! -e "Makefile") {
  say "No existe un 'Makefile' capaz de generar el objetivo \"${programa}\"\n";
  exit 2;
}

say "Limpiamos el escenario";
system ("make clean");
unlink ("abonados.txt", glob("mis_abonados[0-2][0-9].txt"), "mensajes.txt", glob("mis_mensajes[0-2][0-9].txt"), glob("mi_salida[0-2][0-9].txt"));

say "\nConstruimos la aplicación";
system ("make ${programa}");
say "\n";

if ( ! -e "${programa}") {
  say "El programa ${programa} no existe\n";
  exit 3;
}
elsif ( ! -x "${programa}") {
  say "El programa ${programa} no se puede ejecutar\n";
  exit 4;
}
else {
  say "Ejecutamos la batería de pruebas\n";

  for my ${num} (0..9) {
    say "[01;36mPrueba número ${num}[00m: ./${programa} < proto0${num}.txt > mi_salida0${num}.txt";
    given (${num}) {
      when ([1, 4]) {
	copy ("abonados0${num}.txt", "abonados.txt");
	copy ("mensajes0${num}.txt", "mensajes.txt");
      }
      when ([2]) {
	copy ("mensajesA.base", "mensajes.txt");
      }
      when ([5, 6]) {
	copy ("abonadosA.base", "abonados.txt");
	copy ("mensajesA.base", "mensajes.txt");
      }
      when ([8]) {
	copy ("abonadosB.base", "abonados.txt");
      }
      when ([9]) {
	copy ("abonadosC.base", "abonados.txt");
	copy ("mensajesC.base", "mensajes.txt");
      }
    }
    system ("ulimit -f 120 ; ./${programa} < proto0${num}.txt > mi_salida0${num}.txt");
    my ${cuenta_fallos} = 0;
    ${cuenta_fallos} += mueve_y_compara ("abonados0${num}.txt", "abonados.txt");
    ${cuenta_fallos} += mueve_y_compara ("mensajes0${num}.txt", "mensajes.txt");
    ${cuenta_fallos} += compara_archivos ("salida0${num}.txt", "mi_salida0${num}.txt");
    if (${cuenta_fallos} > 0) { ${pruebas_falladas}++; }
  }


  if (${pruebas_falladas} > 0) {
    say "\n[01;31m${pruebas_falladas} pruebas falladas de ${total_pruebas}[00m\n"
  }
  else {
    say "\n[01;32mTodas las pruebas se han superado correctamente[00m\n"
  }
}
