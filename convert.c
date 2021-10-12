#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "de_base_diez.h"
#include "De_Base_N_a_10.h"
#include "conversor_tipos.h"
#include "procesador_argumentos.h"
#include "constantes.h"

void mostrarAyuda();

void test_desde_base_diez();

void test_desde_base_diez2();

/*PROYECTO OdC "convert"*/
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
      deNa10(base_origen, numero, resultado_en_base_diez, modo_verbose);
      //printf("Resultado de convertir (%s)%d a base 10 = (%s)10\n", numero, *base_origen, resultado_en_base_diez);
      resultado_definitivo = de_base_diez(resultado_en_base_diez, base_destino, modo_verbose);
      //printf("Resultado de convertir (%s)10 a base %d = (%s)%d\n", resultado_en_base_diez, *base_destino, resultado_definitivo, *base_destino);
      printf("(%s)%d = (%s)%d\n", numero, *base_origen, resultado_definitivo, *base_destino);
    }

  } else {
    printf("Ha ocurrido un error. Se detallan a continuacion:\n");
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
  }

  exit(EXIT_SUCCESS);
}

void mostrarAyuda() {
  printf("\nMostrando ayuda:\n");
  printf("\nconvert es un programa para convertir un numero de una base a otra.\n\n");
  printf("uso: convert -n <numero> [-s <base_origen>] [-d <base_destino>] [-v] [-h]\n\n");

  printf("[-n]                  - Indica que el siguiente parametro es el numero a convertir\n");
  printf("<numero>              - El numero a convertir.\n");
  printf("[-s]                  - Indica que el siguiente parametro es la base en la que esta expresado el numero a convertir.\n");
  printf("<base_origen>         - La base en la que esta expresado el numero a convertir. Rango: [%d,%d]. Valor por defecto: %d\n", BASE_MINIMA, BASE_MAXIMA,BASE_POR_DEFECTO);
  printf("[-d]                  - Indica que el siguiente parametro es la base a la que se desea convertir el numero <numero>.\n");
  printf("<base_destino>        - La base a la que se desea convertir el numero <numero>. Rango: [%d,%d]. Valor por defecto: %d\n", BASE_MINIMA, BASE_MAXIMA, BASE_POR_DEFECTO);
  printf("[-v]                  - Imprime el paso a paso de la conversion.\n");
  printf("\n");
}

void test_desde_base_diez() {
    char * cadena;
    char * res;
    int * base_destino;
    int * verbose;

    base_destino = (int *) malloc(sizeof(int));
    verbose = (int *) malloc(sizeof(int));

    *base_destino = 8;
    *verbose = 1;

    cadena = "6.5";//110.1
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "13.625";//1101.101
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "127.750";//1111111.11
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "12.0";//1100.0
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "1.5703125";//1.1001001
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "0.03125";//0.00001
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = ".03125";//0.00001
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "139857";//100010001001010001.0
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "139857.";//100010001001010001.0
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = ".";//0.0
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);

    cadena = "";//0.0
    printf("convirtiendo %s\n", cadena);
    res = de_base_diez(cadena, base_destino, verbose);
    printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);
}

void test_desde_base_diez2() {
    char * cadena;
    char * res;
    int * base_destino;
    int * verbose;

    base_destino = (int *) malloc(sizeof(int));
    verbose = (int *) malloc(sizeof(int));

    *base_destino = 8;
    *verbose = 1;

    cadena = "687.21875";//1010101111.00111

    for (*base_destino = BASE_MINIMA; *base_destino <= BASE_MAXIMA; ++(*base_destino)) {
      res = de_base_diez(cadena, base_destino, verbose);
      printf("\t(%s)10 = (%s)%d\n\n", cadena, res, *base_destino);
    }
}
