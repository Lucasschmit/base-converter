#include <stdlib.h>
#include <stdio.h>
#include "validador.h"
#include "conversor_tipos.h"

int es_un_digito_valido(char * digito, int * base);

int es_un_numero_valido_en_base(char * cadena, int * base) {
  int * i;
  int * es_valido;
  int * tiene_punto;
  char * c;

  i = (int*) malloc(sizeof(int));
  es_valido = (int*) malloc(sizeof(int));
  tiene_punto = (int*) malloc(sizeof(int));

  c = (char*) malloc(sizeof(char));

  *i = 0;
  *es_valido = 1;
  *tiene_punto = 0;

  //printf("\t\t\tVerificando si %s es un numero valido en base %d\n", cadena, *base);
  while ((cadena[*i] != '\0') && *es_valido) {
      *c = cadena[*i];

      *es_valido = es_un_digito_valido(c, base) || ((*c == '.') && !(*tiene_punto));

      *tiene_punto = (*c == '.');

      (*i)++;

      //printf("\t\t\t\tc: %c\n", *c);
  }

  free(c);
  free(i);

  if (*es_valido) {
    free(es_valido);
    //printf("\t\t\t%s ES un numero valido en base %d\n", cadena, *base);
    return 1;
  } else {
    //printf("\t\t\t%s NO es un numero valido en base %d\n", cadena, *base);
    free(es_valido);
    return 0;
  }
}

int es_un_digito_valido(char * digito, int * base) {
    return (es_numero(digito) || es_letra(digito)) && ((0 <= digito_a_int(digito)) && (digito_a_int(digito) < (*base)));
}

/**
    Recibe una cadena de digitos validos(puede contener punto)
    Devuelve 1 si la cadena representa un entero en alguna base
    Devuelve 0 en caso contrario
*/
int representa_un_numero_entero(char * cadena) {
    int * i;
    i = (int*) malloc(sizeof(int));
    *i = 0;

    //printf("\t\t\tverificando si %s es un numero entero.\n", cadena);
    while (cadena[*i] != '\0') {
      //printf("\t\t\t\tcadena[*%d] = %c\n", *i, cadena[*i]);
      if (cadena[*i] == '.') {
          //printf("\t\t\t%s NO es un numero entero.\n", cadena);
          free(i);
          return 0;
      }
      (*i)++;
    }
    //printf("\t\t\t%s ES un numero entero.\n", cadena);

    free(i);
    return 1;
}
