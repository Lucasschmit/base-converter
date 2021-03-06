#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "de_base_diez.h"
#include "De_Base_N_a_10.h"
#include "procesador_argumentos.h"
#include "constantes.h"

void mostrarAyuda();

void test_desde_base_diez();

void test_desde_base_diez2();

/*PROYECTO OdC "convert"*/
/**
  Funcion Principal de la aplicacion
*/
int main(int argc, char * argv[]) {
  char * numero;
  char * resultado_en_base_diez;
  char * resultado_definitivo;
  int * base_origen;
  int * base_destino;
  int * modo_verbose;
  int * modo_ayuda;
  int * estado_argumentos;

  base_origen = (int*) malloc(sizeof(int));
  base_destino = (int*) malloc(sizeof(int));
  modo_verbose = (int*) malloc(sizeof(int));
  modo_ayuda = (int*) malloc(sizeof(int));

  *base_origen = BASE_POR_DEFECTO;
  *base_destino = BASE_POR_DEFECTO;
  *modo_ayuda = 0;
  *modo_verbose = 0;

  estado_argumentos = procesarArgumentos(&argc, argv, &numero, &base_origen, &base_destino, modo_verbose, modo_ayuda);
  //printf("Estado argumentos: %x\n", *estado_argumentos);
  if ((*estado_argumentos == ARGUMENTOS_CORRECTOS) || (*modo_ayuda)) {
    /*
    printf("Argumentos procesados.\n");
    printf("Numero: %s\n", numero);
    printf("Base origen: %d\n", *base_origen);
    printf("Base destino: %d\n", *base_destino);
    printf("Modo verbose: %d\n", *modo_verbose);
    printf("Modo ayuda: %d\n", *modo_ayuda);
    printf("\n\n");
    */

    if (*modo_ayuda) {
      mostrarAyuda();
    } else {
      resultado_en_base_diez = (char *) malloc(sizeof(char) * 5 * strlen(numero));
      if (*modo_verbose) {
        printf("Convertimos el numero de su base origen(%d) a una base intermedia(10), para luego convertirlo a la base de destino(%d).\n\n", *base_origen, *base_destino);
      }
      deNa10(base_origen, numero, resultado_en_base_diez, modo_verbose);
      if (*modo_verbose) {
        printf("Resultado de convertir (%s)%d a base 10 = (%s)10\n", numero, *base_origen, resultado_en_base_diez);
        printf("\nConvirtiendo el numero de base 10 a su base de destino(%d).\n\n", *base_destino);
      }
      resultado_definitivo = de_base_diez(resultado_en_base_diez, base_destino, modo_verbose);
      if (*modo_verbose) {
        printf("Resultado de convertir (%s)10 a base %d = (%s)%d\n", resultado_en_base_diez, *base_destino, resultado_definitivo, *base_destino);
      }
      printf("(%s)%d = (%s)%d\n", numero, *base_origen, resultado_definitivo, *base_destino);
    }

  } else {
    printf("Ha ocurrido uno o mas errores. Se detalla a continuacion:\n");
    if (*estado_argumentos & ERROR_CANTIDAD_DE_PARAMETROS) {
      printf("\tError: Faltan parametros.\n");
    }

    if (*estado_argumentos & ERROR_BASE_ORIGEN) {
      printf("\tError: No se ingreso la base de origen, o su valor es invalido.\n");
    }
    if (*estado_argumentos & ERROR_BASE_DESTINO) {
      printf("\tError: No se ingreso la base de destino, o su valor es invalido.\n");
    }

    if (*estado_argumentos & ERROR_FALTA_NUMERO) {
      printf("\tError: No se ingreso el numero a convertir.\n");
    }
    if (*estado_argumentos & ERROR_NUMERO_INVALIDO) {
      printf("\tError: Se ingreso un numero invalido.\n");
    }
    if (*estado_argumentos & ERROR_NUMERO_INVALIDO_EN_BASE_ORIGEN) {
      printf("\tError: El numero ingresado no esta expresado en la base de origen correspondiente.\n");
    }
    if (*estado_argumentos & ERROR_CANT_DIGITOS_ENTRADA_PARTE_ENTERA) {
      printf("\tError: La parte entera del numero tiene mas digitos de los permitidos. Cantidad maxima de digitos permitidos para la parte entera: %d\n", MAX_CANT_DIGITOS_ENTRADA_PARTE_ENTERA);
    }
    if (*estado_argumentos & ERROR_CANT_DIGITOS_ENTRADA_PARTE_FRACCIONARIA) {
      printf("\tError: La parte fraccionaria del numero tiene mas digitos de los permitidos. Cantidad maxima de digitos permitidos para la parte fraccionaria: %d\n", MAX_CANT_DIGITOS_ENTRADA_PARTE_FRACCIONARIA);
    }
    printf("Codigo de error: 0x%X\n", *estado_argumentos);
    mostrarAyuda();
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

/**
  Muestra la ayuda por pantalla
*/
void mostrarAyuda() {
  printf("\nMostrando ayuda:\n");
  printf("\nconvert es un programa para convertir un numero de una base a otra.\n\n");
  printf("uso: convert -n <numero> [-s <base_origen>] [-d <base_destino>] [-v] [-h]\n\n");

  printf("[-n]                  - Indica que el siguiente parametro es el numero a convertir\n\n");
  printf("<numero>              - El numero a convertir. Debe estar expresado en <base_origen>.\n\n");
  printf("[-s]                  - Indica que el siguiente parametro es la base en la que esta expresado el numero a convertir.\n\n");
  printf("<base_origen>         - La base en la que esta expresado el numero a convertir. Debe estar expresada en base 10. Rango: [%d,%d]. Valor por defecto: %d\n\n", BASE_MINIMA, BASE_MAXIMA,BASE_POR_DEFECTO);
  printf("[-d]                  - Indica que el siguiente parametro es la base a la que se desea convertir el numero <numero>.\n\n");
  printf("<base_destino>        - La base a la que se desea convertir el numero <numero>. Debe estar expresada en base 10. Rango: [%d,%d]. Valor por defecto: %d\n\n", BASE_MINIMA, BASE_MAXIMA, BASE_POR_DEFECTO);
  printf("[-v]                  - Imprime el paso a paso de la conversion.\n\n");
  printf("\n");
}
