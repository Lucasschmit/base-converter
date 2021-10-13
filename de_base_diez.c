#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "de_base_diez.h"
#include "conversor_tipos.h"
#include "constantes.h"

void encontrarPunto(char * cadena, int * index);

char * convertir_parte_entera(char * cadena, int * base_destino, int * modo_verbose);

char * convertir_parte_fraccionaria(char * cadena, int * base_destino, int * modo_verbose);

int * string_a_int(char * cadena);

char * get_parte_entera(char * cadena, int * modo_verbose);

char * get_parte_fraccionaria(char * cadena, int * modo_verbose);

int * index_punto(char * cadena);


/**
  Recibe una cadena en base 10 y la convierte a la base de destino solicitada.
  Si se indica el modo verbose, indica el paso a paso de la conversion

  Cadena se asume terminada en '\0' y con todos sus caracteres entre '0' y '9' o '.'

  Estrategia utilizada para convertir la parte entera: Metodo de la division

  Estrategia utilizada para convertir la parte fraccionaria: Metodo de la multiplicacion
*/
char * de_base_diez(char * cadena, int * base_destino, int * modo_verbose) {
    char * parte_entera;
    char * parte_fraccionaria;
    char * resultado_entero;
    char * resultado_fraccionario;
    char * resultado_definitivo;
    int * tam_resultado_definitivo;
    int * tam_resultado_entero;
    int * tam_resultado_fraccionario;

    tam_resultado_definitivo = (int*) malloc(sizeof(int));
    tam_resultado_entero = (int*) malloc(sizeof(int));
    tam_resultado_fraccionario = (int*) malloc(sizeof(int));

    parte_entera = get_parte_entera(cadena, modo_verbose);
    parte_fraccionaria = get_parte_fraccionaria(cadena, modo_verbose);

    if (*modo_verbose) {
      printf("Separando a %s en su parte entera y fraccionaria:\n", cadena);
      printf("\tParte entera: %s\n", parte_entera);
      printf("\tParte fraccionaria: %s\n", parte_fraccionaria);
    }

    resultado_entero = convertir_parte_entera(parte_entera, base_destino, modo_verbose);


    resultado_fraccionario = convertir_parte_fraccionaria(parte_fraccionaria, base_destino, modo_verbose);

    *tam_resultado_entero = strlen(resultado_entero);


    *tam_resultado_fraccionario = strlen(resultado_fraccionario);

    *tam_resultado_definitivo = (*tam_resultado_entero) + (*tam_resultado_fraccionario) + 2;

    resultado_definitivo = (char*) malloc(sizeof(char) * (*tam_resultado_definitivo));

    strcpy(resultado_definitivo, resultado_entero);

    resultado_definitivo[*tam_resultado_entero] = '.';

    strcpy(&resultado_definitivo[(*tam_resultado_entero) + 1], resultado_fraccionario);

    free(tam_resultado_definitivo);
    free(tam_resultado_entero);
    free(tam_resultado_fraccionario);

    free(parte_entera);
    free(parte_fraccionaria);
    free(resultado_entero);
    free(resultado_fraccionario);

    return resultado_definitivo;
}

/**
  Recibe una cadena que representa un entero en base 10 y devuelve otra cadena con su representacion en base destino
  Necesita que cadena sea al menos "0", no puede estar vacia.
*/
char * convertir_parte_entera(char * cadena, int * base_destino, int * modo_verbose) {
    char * resultado;
    char * resultado_preliminar;
    int * valor_en_entero;
    int * tam_resultado_preliminar;
    int * tam_resultado;
    int * index_resultado_preliminar;
    int * resto;

    tam_resultado_preliminar = (int*) malloc(sizeof(int));
    tam_resultado = (int*) malloc(sizeof(int));
    index_resultado_preliminar = (int*) malloc(sizeof(int));
    resto = (int*) malloc(sizeof(int));

    *tam_resultado_preliminar = 4 * strlen(cadena);
    *index_resultado_preliminar = (*tam_resultado_preliminar) - 1;

    resultado_preliminar = (char*) malloc(sizeof(char) * (*tam_resultado_preliminar));
    resultado_preliminar[*index_resultado_preliminar] = '\0';

    (*index_resultado_preliminar)--;

    valor_en_entero = string_a_int(cadena);

    if (*modo_verbose) {
        printf("\nConvirtiendo parte entera de base 10 a base %d.\n", *base_destino);
        printf("\tTrabajando sobre el numero %d\n", *valor_en_entero);
    }
    while (*valor_en_entero >= *base_destino) {
      if (*modo_verbose) {
        printf("\tDividiendo %d entre la base de destino(%d):\n", *valor_en_entero, *base_destino);
      }
      *resto = *valor_en_entero % *base_destino;

      if (*modo_verbose) {
        printf("\tResto de dividir %d entre la base de destino(%d): %d\n", *valor_en_entero, *base_destino, *resto);
      }

      *valor_en_entero = *valor_en_entero / *base_destino;

      resultado_preliminar[*index_resultado_preliminar] = int_a_digito(resto);

      if (*modo_verbose) {
        printf("\tEl resto (%d) obtenido es el nuevo digito mas significativo(indice: %d) del numero expresado en la base de destino: %s\n\n", *resto, (*tam_resultado_preliminar) - (*index_resultado_preliminar) - 2, &resultado_preliminar[*index_resultado_preliminar]);
        printf("\tNuevo numero sobre el que trabajaremos(cociente de la division que hicimos): %d\n", *valor_en_entero);
      }

      (*index_resultado_preliminar)--;
    }

    resultado_preliminar[*index_resultado_preliminar] = int_a_digito(valor_en_entero);

    if (*modo_verbose) {
      printf("\tComo el numero (%d) sobre el que estamos trabajando es menor que la base de destino(%d), simplemente lo agregamos como digito mas significativo (%c) al numero expresado en base de destino.\n", *valor_en_entero, *base_destino, resultado_preliminar[*index_resultado_preliminar]);
    }

    *tam_resultado = (*tam_resultado_preliminar) - (*index_resultado_preliminar);

    resultado = (char*) malloc(sizeof(char) * (*tam_resultado));

    strcpy(resultado, &resultado_preliminar[*index_resultado_preliminar]);

    if (*modo_verbose) {
      printf("\n\tResultado de convertir la parte entera: %s\n", resultado);
    }

    free(resultado_preliminar);

    free(valor_en_entero);
    free(tam_resultado_preliminar);
    free(tam_resultado);
    free(index_resultado_preliminar);
    free(resto);

    return resultado;
}

/**
  Recibe una cadena que representa una parte fraccionaria en base 10 y devuelve otra cadena con su representacion en base destino
  Necesita que cadena sea al menos "0", no puede estar vacia.
*/
char * convertir_parte_fraccionaria(char * cadena, int * base_destino, int * modo_verbose) {
    char * resultado;
    char * resultado_preliminar;
    int * valor_en_entero;
    int * index_resultado_preliminar;
    int * cociente;
    int * producto;
    int * divisor;

    valor_en_entero = (int*) malloc(sizeof(int));
    index_resultado_preliminar = (int*) malloc(sizeof(int));
    cociente = (int*) malloc(sizeof(int));
    producto = (int*) malloc(sizeof(int));
    divisor = (int*) malloc(sizeof(int));

    resultado_preliminar = (char*) malloc(sizeof(char) * (MAX_CANT_DIGITOS_SALIDA_PARTE_FRACCIONARIA + 2));

    valor_en_entero = string_a_int(cadena);
    *index_resultado_preliminar = 0;
    *divisor = pow(10, strlen(cadena));

    if (*modo_verbose) {
        printf("\nConvirtiendo parte fraccionaria de base 10 a base %d.\n", *base_destino);
        printf("\tTrabajando sobre la parte fraccionaria %d\n", *valor_en_entero);
    }
    if (*valor_en_entero > 0) {
        while ((*valor_en_entero > 0) && ((MAX_CANT_DIGITOS_SALIDA_PARTE_FRACCIONARIA - (*index_resultado_preliminar)) > 0)) {

            *producto = (*valor_en_entero) * (*base_destino);

            if (*modo_verbose) {
              printf("\tProducto entre la parte fraccionaria %d y la base de destino(%d): %d\n", *valor_en_entero, *base_destino, *producto);
            }

            *cociente = (*producto) / (*divisor);

            if (*modo_verbose) {
              printf("\tParte entera del producto anterior: %d\n", *cociente);
            }

            *valor_en_entero = (*producto) % (*divisor);

            resultado_preliminar[*index_resultado_preliminar] = int_a_digito(cociente);

            if (*modo_verbose) {
              printf("\tLa parte entera(%d) del producto anterior es el valor del proximo digito(%c) que se agrega al final del numero en la base de destino.\n\n", *cociente, resultado_preliminar[*index_resultado_preliminar]);
              printf("\tNuevo numero sobre el que trabajaremos(parte fraccionaria del producto anterior): %d\n", *valor_en_entero);
            }

            (*index_resultado_preliminar)++;
        }
    } else {
        resultado_preliminar[*index_resultado_preliminar] = '0';
        (*index_resultado_preliminar)++;
    }

    resultado_preliminar[*index_resultado_preliminar] = '\0';

    if (*modo_verbose) {
      if (*valor_en_entero == 0) {
        printf("\tComo el numero sobre el que estamos trabajando es cero, damos por terminada la conversion.\n");
      } else if (!((MAX_CANT_DIGITOS_SALIDA_PARTE_FRACCIONARIA - (*index_resultado_preliminar)) > 0)) {
        printf("\tComo se llego a la maxima precision definida para parte fraccionaria, damos por terminada la conversion.\n");
      }
    }

    resultado = (char*) malloc(sizeof(int) * ((*index_resultado_preliminar) + 1));

    strcpy(resultado, resultado_preliminar);

    if (*modo_verbose) {
      printf("\n\tResultado de convertir la parte fraccionaria: %s\n", resultado);
    }


    free(resultado_preliminar);

    free(valor_en_entero);
    free(index_resultado_preliminar);
    free(cociente);
    free(producto);
    free(divisor);

    return resultado;
}

/**
    Recibe una cadena y retorna otra cadena conteniendo el valor de su parte entera
    O cero (0) si no encontro la parte entera
*/
char * get_parte_entera(char * cadena, int * modo_verbose) {
    int * i;
    int * tam_parte_entera;
    char * parte_entera;

    tam_parte_entera = (int*) malloc(sizeof(int));

    i = index_punto(cadena);

    if (*i == 0) {
        *tam_parte_entera = 2;

        parte_entera = (char*) malloc(sizeof(char) * (*tam_parte_entera));

        parte_entera[0] = '0';
    } else {
        *tam_parte_entera = (*i) + 1;

        parte_entera = (char*) malloc(sizeof(char) * (*tam_parte_entera));

        strncpy(parte_entera, cadena, *i);
    }

    parte_entera[(*tam_parte_entera) - 1] = '\0';


    free(i);
    free(tam_parte_entera);

    return parte_entera;
}

/**
    Recibe una cadena y retorna otra cadena conteniendo el valor de su parte fraccionaria
    O cero (0) si no encontro la parte fraccionaria
*/
char * get_parte_fraccionaria(char * cadena, int * modo_verbose) {
    int * i;
    int * tam_parte_fraccionaria;
    char * parte_fraccionaria;

    i = (int*) malloc(sizeof(int));
    tam_parte_fraccionaria = (int*) malloc(sizeof(int));

    i = index_punto(cadena);

    if ((cadena[*i] == '\0') || (cadena[(*i) + 1] == '\0')) {
        *tam_parte_fraccionaria = 2;

        parte_fraccionaria = (char*) malloc(sizeof(char) * (*tam_parte_fraccionaria));

        parte_fraccionaria[0] = '0';
    } else {
        *tam_parte_fraccionaria = strlen(&cadena[*i]);

        parte_fraccionaria = (char*) malloc(sizeof(char) * (*tam_parte_fraccionaria));

        strcpy(parte_fraccionaria, &cadena[(*i) + 1]);
    }

    parte_fraccionaria[*tam_parte_fraccionaria - 1] = '\0';

    free(i);
    free(tam_parte_fraccionaria);

    return parte_fraccionaria;
}

/**
    Recibe una cadena y devuelve un puntero que apunta
    a una variable con el indice del punto(si lo encontro).
    O apuntando al caracter nulo al final de la cadena si no encontro el punto
*/
int * index_punto(char * cadena) {
    int * i;
    i = (int*) malloc(sizeof(int));
    *i = 0;

    while ((cadena[*i] != '\0') && (cadena[*i] != '.')) {
        (*i)++;
    }

    return i;
}
