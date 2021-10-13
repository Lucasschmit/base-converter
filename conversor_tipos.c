#include <stdlib.h>

#include "conversor_tipos.h"

void a_mayuscula(char * c);

int es_numero(char * c);

char convertir_a_digito(int * digito);

/**
  Recibe un puntero a caracter
  Devuelve un valor entre 0 y (BASE_MAXIMA - 1)
*/
int digito_a_int(char * digito) {
    if (es_numero(digito)) {
        return *digito - '0';
    } else {
        a_mayuscula(digito);
        return *digito - 'A' + 10;
    }
}

/**
  Recibe un puntero a entero
  Devuelve un digito entre 0 y el mayor digito en base BASE_MAXIMA
*/
char int_a_digito(int * digito) {
    if (*digito < 10) {
        return '0' + *digito;
    } else {
        return 'A' + *digito - 10;
    }
}

/**
  Recibe una letra y la cambia por su equivalente mayuscula
*/
void a_mayuscula(char * c) {
    if ('a' <= *c && *c <= 'z') {
        *c = *c - 'a' + 'A';
    }
}

/**
  Recibe un puntero a caracter y chequea si apunta a un caracter que representa un numero
*/
int es_numero(char * c) {
   return ('0' <= *c) && (*c <= '9');
}

/**
  Recibe un puntero a caracter y chequea si apunta a un caracter que representa una letra
*/
int es_letra(char * c) {
    return ( (('a' <= *c) && (*c <= 'z')) || (('A' <= *c) && (*c <= 'Z')) );
}

/**
    Recibe una cadena de digitos en base 10 y devuelve su valor en un entero.
    Solo para base 10
*/
int * string_a_int(char * cadena) {
    int * numero;
    int * i;

    numero = (int*) malloc(sizeof(int));
    i = (int*) malloc(sizeof(int));

    *numero = 0;
    *i = 0;

    //printf("Convirtiendo de string a entero: %s\n", cadena);

    while (cadena[*i] != '\0') {
        *numero *= 10;
        *numero += digito_a_int(cadena + *i);
        (*i)++;
    }

    //printf("\tSe convirtio a: %i\n", *numero);

    free(i);
    return numero;
}
