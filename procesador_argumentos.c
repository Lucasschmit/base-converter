#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "validador.h"
#include "conversor_tipos.h"

int cumple_restricciones_para_numero(char * cadena, int * estado);

/**
  Recibe los argumentos recibidos de la consola, los procesa, y los devuelve con los valores correspondientes
  Devuelve un puntero a entero que indica si se encontraron argumentos validos para proceder con la conversion o no
*/
int * procesarArgumentos(int * argc, char * argv[], char ** numero, int ** base_origen, int ** base_destino, int * modo_verbose, int * modo_ayuda) {
    int * i;
    int * aux;
    int * base_diez;
    int * base_maxima;
    int * estado_argumentos;
    char * parametro_actual;

    i = (int*) malloc(sizeof(int));
    base_diez = (int*) malloc(sizeof(int));
    base_maxima = (int*) malloc(sizeof(int));
    estado_argumentos = (int*) malloc(sizeof(int));

    if (*argc == 1) {
      *estado_argumentos = ERROR_CANTIDAD_DE_PARAMETROS | ERROR_FALTA_NUMERO;
      return estado_argumentos;
    }

    *base_diez = 10;
    *base_maxima = BASE_MAXIMA;
    *estado_argumentos = ERROR_FALTA_NUMERO;


    for (*i = 0; *i < *argc; (*i)++) {
        parametro_actual = argv[*i];

        if (strcmp(parametro_actual, PARAMETRO_NUMERO) == 0) {
          if ((*i) < (*argc) - 1) {
              *estado_argumentos = *estado_argumentos & (~ERROR_FALTA_NUMERO);
            if (es_un_numero_valido_en_base(argv[(*i) + 1], base_maxima)) {
              if (cumple_restricciones_para_numero(argv[(*i) + 1], estado_argumentos)) {
                *numero = argv[++(*i)];
              } else {
                *estado_argumentos = *estado_argumentos | ERROR_NUMERO_INVALIDO;
              }
            } else {
              *estado_argumentos = *estado_argumentos | ERROR_NUMERO_INVALIDO;
            }
          } else {
            *estado_argumentos = *estado_argumentos | ERROR_CANTIDAD_DE_PARAMETROS;
          }

        } else if (strcmp(parametro_actual, PARAMETRO_BASE_ORIGEN) == 0) {

          if ((*i) < (*argc) - 1) {
            if (es_un_numero_valido_en_base(argv[(*i) + 1], base_diez) && representa_un_numero_entero(argv[(*i) + 1])) {
              aux = string_a_int(argv[++(*i)]);
              if (BASE_MINIMA <= *aux && *aux <= BASE_MAXIMA) {
                **base_origen = *aux;
              } else {
                *estado_argumentos = *estado_argumentos | ERROR_BASE_ORIGEN;
              }
              free(aux);
            } else {
              *estado_argumentos = *estado_argumentos | ERROR_BASE_ORIGEN;
            }
          } else {
            *estado_argumentos = *estado_argumentos | ERROR_CANTIDAD_DE_PARAMETROS;
            *estado_argumentos = *estado_argumentos | ERROR_BASE_ORIGEN;
          }

        } else if (strcmp(parametro_actual, PARAMETRO_BASE_DESTINO) == 0) {

          if ((*i) < (*argc) - 1) {
            if (es_un_numero_valido_en_base(argv[(*i) + 1], base_diez) && representa_un_numero_entero(argv[(*i) + 1])) {
              aux = string_a_int(argv[++(*i)]);
              if (BASE_MINIMA <= *aux && *aux <= BASE_MAXIMA) {
                **base_destino = *aux;
              } else {
                *estado_argumentos = *estado_argumentos | ERROR_BASE_DESTINO;
              }
              free(aux);

            } else {
              *estado_argumentos = *estado_argumentos | ERROR_BASE_DESTINO;
            }
          } else {
            *estado_argumentos = *estado_argumentos | ERROR_CANTIDAD_DE_PARAMETROS;
            *estado_argumentos = *estado_argumentos | ERROR_BASE_DESTINO;
          }
        } else if (strcmp(parametro_actual, OPCION_AYUDA) == 0) {
          *modo_ayuda = 1;
        } else if (strcmp(parametro_actual, OPCION_VERBOSE) == 0) {
          *modo_verbose = 1;
        }
        free(parametro_actual);
    }

    if (!((*estado_argumentos) & ERROR_FALTA_NUMERO)) {
      if ( !((*estado_argumentos) & ERROR_NUMERO_INVALIDO) && !( (*estado_argumentos) & ERROR_BASE_ORIGEN ) ) {
        if (!es_un_numero_valido_en_base(*numero, *base_origen)) {
          *estado_argumentos = *estado_argumentos | ERROR_NUMERO_INVALIDO_EN_BASE_ORIGEN;
        }
      }
    }

    if (*estado_argumentos & ERROR_FALTA_NUMERO) {
      *estado_argumentos = *estado_argumentos | ERROR_CANTIDAD_DE_PARAMETROS;
    }

    if (*estado_argumentos == 0) {
      *estado_argumentos = ARGUMENTOS_CORRECTOS;
    }

    free(i);
    free(base_diez);
    free(base_maxima);
    return estado_argumentos;
}

/**
  Verifica si la cadena que podria representar un numero, tiene caracteres validos para ser interpretados como digitos.
  Ademas se encarga de verificar la longitud de la parte entera y fraccionaria del numero
*/
int cumple_restricciones_para_numero(char * cadena, int * estado) {
  int * i;
  int * largo_parte_entera;
  int * largo_parte_fraccionaria;

  i = (int*) malloc(sizeof(int));
  largo_parte_entera = (int*) malloc(sizeof(int));
  largo_parte_fraccionaria = (int*) malloc(sizeof(int));

  *i = 0;
  *largo_parte_entera = 0;
  *largo_parte_fraccionaria = 0;

  while (cadena[*i] != '\0') {
    if (cadena[*i] == '.') {
      *largo_parte_entera = *i;
    }
    (*i)++;
  }

  *largo_parte_fraccionaria = (*i) - (*largo_parte_entera) - 1;

  if (*largo_parte_entera > MAX_CANT_DIGITOS_ENTRADA_PARTE_ENTERA) {
    *estado = *estado | ERROR_CANT_DIGITOS_ENTRADA_PARTE_ENTERA;
    *i = -1;
  }
  if (*largo_parte_fraccionaria > MAX_CANT_DIGITOS_ENTRADA_PARTE_FRACCIONARIA) {
    *estado = *estado | ERROR_CANT_DIGITOS_ENTRADA_PARTE_FRACCIONARIA;
    *i = -1;
  }

  free(largo_parte_entera);
  free(largo_parte_fraccionaria);

  if (*i == -1) {
    free(i);
    return 0;
  } else {
    free(i);
    return 1;
  }
}
