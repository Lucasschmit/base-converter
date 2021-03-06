#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

//Rango de bases
#define BASE_MINIMA 2
#define BASE_MAXIMA 16

//Maxima longitud en digitos de las partes de un numero
#define MAX_CANT_DIGITOS_ENTRADA_PARTE_ENTERA 10
#define MAX_CANT_DIGITOS_ENTRADA_PARTE_FRACCIONARIA 5

#define MAX_CANT_DIGITOS_SALIDA_PARTE_FRACCIONARIA 7

//Base por defecto
#define BASE_POR_DEFECTO 10

//Indicaciones para los parametros pasados por consola
#define PARAMETRO_NUMERO "-n"
#define PARAMETRO_BASE_ORIGEN "-s"
#define PARAMETRO_BASE_DESTINO "-d"
#define OPCION_AYUDA "-h"
#define OPCION_VERBOSE "-v"

//Estado de los argumentos pasados por consola
#define ARGUMENTOS_CORRECTOS                            0b00000000
#define ERROR_FALTA_NUMERO                              0b00000001
#define ERROR_CANT_DIGITOS_ENTRADA_PARTE_ENTERA         0b00000010
#define ERROR_CANT_DIGITOS_ENTRADA_PARTE_FRACCIONARIA   0b00000100
#define ERROR_CANTIDAD_DE_PARAMETROS                    0b00001000
#define ERROR_NUMERO_INVALIDO                           0b00010000
#define ERROR_NUMERO_INVALIDO_EN_BASE_ORIGEN            0b00100000
#define ERROR_BASE_ORIGEN                               0b01000000
#define ERROR_BASE_DESTINO                              0b10000000



#endif // CONSTANTES_H_INCLUDED
