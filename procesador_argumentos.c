#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "validador.h"
#include "conversor_tipos.h"

int cumple_restricciones_para_numero(char * cadena, int * estado);

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

    *base_diez = 10;
    *base_maxima = BASE_MAXIMA;
    *estado_argumentos = ERROR_FALTA_NUMERO;


    for (*i = 0; *i < *argc; (*i)++) {
        parametro_actual = argv[*i];
        //printf("argumento %d: <%s>\n", *i, parametro_actual);

        if (strcmp(parametro_actual, PARAMETRO_NUMERO) == 0) {
          //printf("\tSe ingreso el parametro para numero(%s).\n", parametro_actual);
          if ((*i) < (*argc) - 1) {
            if (es_un_numero_valido_en_base(argv[(*i) + 1], base_maxima)) {
              *estado_argumentos = *estado_argumentos & (~ERROR_FALTA_NUMERO);
              //printf("\t\tEstado argumentos antes de numero: %2x\n", *estado_argumentos);
              if (cumple_restricciones_para_numero(argv[(*i) + 1], estado_argumentos)) {
                *numero = argv[++(*i)];
                //printf("\t\tEstado argumentos despues de numero: %2x\n", *estado_argumentos);
              } else {
                *estado_argumentos = *estado_argumentos | ERROR_NUMERO_INVALIDO;
                //printf("\t\tEl numero no cumple las restricciones de cantidad de digitos.\n");
              }
              //printf("\t\tnumero: %s\n", *numero);
            } else {
              *estado_argumentos = *estado_argumentos | ERROR_NUMERO_INVALIDO;
              //printf("\tEl argumento <%s> NO tiene asociado un valor valido: %s\n", parametro_actual, argv[(*i) + 1]);
            }
          } else {
            *estado_argumentos = *estado_argumentos | ERROR_CANTIDAD_DE_PARAMETROS;
            //printf("\tNO se asocio un valor al parametro <%s>.\n", parametro_actual);
          }

        } else if (strcmp(parametro_actual, PARAMETRO_BASE_ORIGEN) == 0) {

          //printf("\tSe ingreso el parametro para base de origen(%s).\n", parametro_actual);
          if ((*i) < (*argc) - 1) {
            if (es_un_numero_valido_en_base(argv[(*i) + 1], base_diez) && representa_un_numero_entero(argv[(*i) + 1])) {
              aux = string_a_int(argv[++(*i)]);
              **base_origen = *aux;
              free(aux);
              //printf("\t\tbase de origen: %d\n", **base_origen);
            } else {
              *estado_argumentos = *estado_argumentos | ERROR_BASE_ORIGEN;
              //printf("\tEl argumento <%s> NO tiene asociado un valor valido: %s\n", parametro_actual, argv[(*i) + 1]);
            }
          } else {
            *estado_argumentos = *estado_argumentos | ERROR_CANTIDAD_DE_PARAMETROS;
            *estado_argumentos = *estado_argumentos | ERROR_BASE_ORIGEN;
            //printf("\tNO se asocio un valor al parametro <%s>.\n", parametro_actual);
          }

        } else if (strcmp(parametro_actual, PARAMETRO_BASE_DESTINO) == 0) {

          //printf("\tSe ingreso el parametro para base de destino(%s).\n", parametro_actual);
          if ((*i) < (*argc) - 1) {
            if (es_un_numero_valido_en_base(argv[(*i) + 1], base_diez) && representa_un_numero_entero(argv[(*i) + 1])) {
              aux = string_a_int(argv[++(*i)]);
              **base_destino = *aux;
              free(aux);

              //printf("\t\tbase de destino: %d\n", **base_destino);
            } else {
              *estado_argumentos = *estado_argumentos | ERROR_BASE_DESTINO;
            }
          } else {
            *estado_argumentos = *estado_argumentos | ERROR_CANTIDAD_DE_PARAMETROS;
            *estado_argumentos = *estado_argumentos | ERROR_BASE_DESTINO;
            //printf("\tNO se asocio un valor al parametro <%s>.\n", parametro_actual);
          }
        } else if (strcmp(parametro_actual, OPCION_AYUDA) == 0) {
          *modo_ayuda = 1;
          //printf("\tSe ingreso la opcion de ayuda.\n");
        } else if (strcmp(parametro_actual, OPCION_VERBOSE) == 0) {
          //printf("\tSe ingreso la opcion de modo verbose.\n");
          *modo_verbose = 1;
        }
        free(parametro_actual);
    }

    if ( !((*estado_argumentos) & ERROR_NUMERO_INVALIDO) && !( (*estado_argumentos) & ERROR_BASE_ORIGEN ) ) {
      if (!es_un_numero_valido_en_base(*numero, *base_origen)) {
        *estado_argumentos = *estado_argumentos | ERROR_NUMERO_INVALIDO_EN_BASE_ORIGEN;
      }
    }

    if (*estado_argumentos == 0) {
      *estado_argumentos = ARGUMENTOS_CORRECTOS;
    }

    free(i);
    free(base_diez);
    free(base_maxima);
    return estado_argumentos;
}

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
/*
int representa_un_numero(char * cadena) {
    int * base_maxima;
    base_maxima = (int*) malloc(sizeof(int));
    *base_maxima = BASE_MAXIMA;

    if (es_un_numero_valido_en_base(cadena, base_maxima)) {
        free(base_maxima);
        return 1;
    } else {
        free(base_maxima);
        return 0;
    }
}
*/
