#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "de_base_diez.h"
//#include "conversor_tipos.h"

void encontrarPunto(char * cadena, int * index);

char * convertir_parte_entera(char * cadena, int * base_destino, int * modo_verbose);

char * convertir_parte_fraccionaria(char * cadena, int * base_destino, int * modo_verbose);

int * string_a_int(char * cadena);

char * get_parte_entera(char * cadena, int * modo_verbose);

char * get_parte_fraccionaria(char * cadena, int * modo_verbose);

int * index_punto(char * cadena);


/**
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

    //separarParteEnteraYFraccionaria(cadena, &parteEntera, &parteFraccionaria, modo_verbose);

    parte_entera = get_parte_entera(cadena, modo_verbose);
    parte_fraccionaria = get_parte_fraccionaria(cadena, modo_verbose);

    //printf("\tParte entera: %s\n", parte_entera);
    //printf("\tParte fraccionaria: %s\n", parte_fraccionaria);

    resultado_entero = convertir_parte_entera(parte_entera, base_destino, modo_verbose);
    resultado_fraccionario = convertir_parte_fraccionaria(parte_fraccionaria, base_destino, modo_verbose);

    //printf("\tResultado parte entera: %s\n", resultado_entero);
    //printf("\tResultado parte fraccionaria: %s\n", resultado_fraccionario);

    *tam_resultado_entero = strlen(resultado_entero);

    //printf("tam resultado entero: %d.\n", *tam_resultado_entero);

    *tam_resultado_fraccionario = strlen(resultado_fraccionario);

    //printf("tam resultado fraccionario: %d.\n", *tam_resultado_fraccionario);

    *tam_resultado_definitivo = (*tam_resultado_entero) + (*tam_resultado_fraccionario) + 2;

    //printf("tam resultado definitivo: %d.\n", *tam_resultado_definitivo);

    resultado_definitivo = (char*) malloc(sizeof(char) * (*tam_resultado_definitivo));

    strcpy(resultado_definitivo, resultado_entero);

    resultado_definitivo[*tam_resultado_entero] = '.';

    strcpy(&resultado_definitivo[(*tam_resultado_entero) + 1], resultado_fraccionario);


    //convertir_parte_entera(parteEntera, baseDestino, &resultadoEntero, modo_verbose);

    //printf("La parte entera del numero %s en base 10 convertido a base %d es: %s", cadena, *baseDestino, resultadoEntero);

    //free(parteEntera);
    //free(parteFraccionaria);
    //free(resultadoEntero);
    //free(resultadoFraccionario);

    return resultado_definitivo;
}

//Necesita que cadena sea al menos "0", no puede estar vacia.
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

    //printf("convirtiendo parte entera a base %d: %d\n", *valor_en_entero, *base_destino);

    while (*valor_en_entero >= *base_destino) {
        *resto = *valor_en_entero % *base_destino;
        *valor_en_entero = *valor_en_entero / *base_destino;

        //printf("resto: %d, valor_entero: %d\n", *resto, *valor_en_entero);
        resultado_preliminar[*index_resultado_preliminar] = int_a_digito(resto);
        //printf("\tse agrego como digito mas significativo: %c\n", resultado_preliminar[*index_resultado_preliminar]);
        //printf("\t\tresultado preliminar: %s\n", &resultado_preliminar[*index_resultado_preliminar]);

        (*index_resultado_preliminar)--;
    }

    //printf("fuera del while\n");

    resultado_preliminar[*index_resultado_preliminar] = int_a_digito(valor_en_entero);

    //printf("resultado preliminar definitivo: %s\n", &resultado_preliminar[*index_resultado_preliminar]);

    *tam_resultado = (*tam_resultado_preliminar) - (*index_resultado_preliminar);

    //printf("tam del resultado definitivo: %d", *tam_resultado);

    resultado = (char*) malloc(sizeof(char) * (*tam_resultado));

    //printf("copiando resultado preliminar.\n");
    strcpy(resultado, &resultado_preliminar[*index_resultado_preliminar]);


    return resultado;
}

//Necesita que cadena sea al menos "0", no puede estar vacia.
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

    resultado_preliminar = (char*) malloc(sizeof(char) * (CANTIDAD_MAXIMA_DE_DIGITOS_FRACCIONARIOS + 2));

    valor_en_entero = string_a_int(cadena);
    *index_resultado_preliminar = 0;
    *divisor = pow(10, strlen(cadena));

    //printf("\t\t\tbase destino: %d\n", *base_destino);
    //printf("\t\t\tcadena: %s\n", cadena);
    //printf("\t\t\tdivisor: %d\n", *divisor);
    //printf("\t\t\tvalor entero: %d\n", *valor_en_entero);

    if (*valor_en_entero > 0) {
        while ((*valor_en_entero > 0) && ((CANTIDAD_MAXIMA_DE_DIGITOS_FRACCIONARIOS - (*index_resultado_preliminar)) > 1)) {

            *producto = (*valor_en_entero) * (*base_destino);
            *cociente = (*producto) / (*divisor);

            *valor_en_entero = (*producto) % (*divisor);

            //printf("\t\t\t\tproducto: %d\n", *producto);
            //printf("\t\t\t\tcociente: %d\n", *cociente);
            //printf("\t\t\t\tnuevo valor entero: %d\n", *valor_en_entero);

            //printf("\t\t\t\tresultado_preliminar[%d] = %d\n", (*index_resultado_preliminar), int_a_digito(cociente));

            resultado_preliminar[*index_resultado_preliminar] = int_a_digito(cociente);

            (*index_resultado_preliminar)++;
        }
    } else {
        resultado_preliminar[*index_resultado_preliminar] = '0';
        (*index_resultado_preliminar)++;
    }

    resultado_preliminar[*index_resultado_preliminar] = '\0';

    //printf("\tresultado fraccionario preliminar: %s\n", resultado_preliminar);

    resultado = (char*) malloc(sizeof(int) * ((*index_resultado_preliminar) + 1));

    strcpy(resultado, resultado_preliminar);

    free(valor_en_entero);

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
