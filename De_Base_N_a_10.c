#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define precision 16
#define precisionEntera 10
#define precisionDecimal 5

void deNa10(int *baseOrigen, char *numero, char *resultado, int * modo_verbose);
void deNa10Entero(int *BaseOrigen,char *numeroEntero, char *stringResultadoNa10);
void deNa10Decimal(int *BaseOrigen,char *numeroDecimal, char *resultadoNa10String);
void concatenarCadenas(char *numEntero, char *numDecimal, char *numCompleto);
void mapearDigito(char * pDigito, int *digitoInt);
void toString(double *resultadoFloat, char * resultadoString, char * parteNum );
void dividirCadenas(char *numEntero, char *numDecimal, char *numCompleto);
/**
  Cadena se asume terminada en '\0' y con todos sus caracteres en el rango [0, 9] o '.' o ['a'('A'), 'f'('F')]

  Estrategia utilizada para convertir la parte entera: Metodo de la multiplicación

  Estrategia utilizada para convertir la parte fraccionaria: Metodo de la división

*/

void deNa10(int *baseOrigen, char *numero, char *resultado, int * modo_verbose){

    char *numeroParteEntera;
    numeroParteEntera=(char *)malloc(sizeof(char)*11);

    char *numeroParteDecimal;
    numeroParteDecimal=(char *)malloc(sizeof(char)*40);

    char *numeroConvertidoParteEntera;
    numeroConvertidoParteEntera=(char *)malloc(sizeof(char)*14);

    char *numeroConvertidoParteDecimal;
    numeroConvertidoParteDecimal=(char *)malloc(sizeof(char)*20);

    dividirCadenas(numeroParteEntera,numeroParteDecimal,numero);
    if (*modo_verbose) {
      printf("Parte entera de %s: %s\n", numero, numeroParteEntera);
      printf("Parte fraccionaria de %s: %s\n", numero, numeroParteDecimal);
      //printf("El numero %s se dividio en la parte entera : %s\n y la parte decimal: %s\n",numero,numeroParteEntera,numeroParteDecimal);
      //printf("___________________________________________________________________________________________________________\n");
    }

    deNa10Entero(baseOrigen,numeroParteEntera,numeroConvertidoParteEntera);
    if (*modo_verbose){
      printf("Resultado de convertir la parte entera de (%s)%d a base 10: %s\n", numero, *baseOrigen, numeroConvertidoParteEntera);
      //printf("El numero entero %s en base: %d\n Es %s en base 10\n",numeroParteEntera,*baseOrigen,numeroConvertidoParteEntera);
      //printf("___________________________________________________________________________________________________________\n");
    }

    deNa10Decimal(baseOrigen,numeroParteDecimal,numeroConvertidoParteDecimal);
    if (*modo_verbose) {
      printf("Resultado de convertir la parte fraccionaria de (%s)%d a base 10: %s\n", numero, *baseOrigen, numeroConvertidoParteDecimal);
      //printf("El numero decimal %s en base: %d\n Es %s en base 10\n",numeroParteDecimal,*baseOrigen,numeroConvertidoParteDecimal);
      //printf("___________________________________________________________________________________________________________\n");
    }

    concatenarCadenas(numeroConvertidoParteEntera,numeroConvertidoParteDecimal,resultado);
    if (*modo_verbose) {
      printf("Resultado final de convertir (%s)%d a base 10: (%s)10\n", numero, *baseOrigen, resultado);
      //printf("El numero %s en base %d, convertido a base 10 es: %s\n",numero,*baseOrigen,resultado);
      //printf("___________________________________________________________________________________________________________\n");
    }

    free(numeroParteEntera);
    free(numeroParteDecimal);
    free(numeroConvertidoParteEntera);
    free(numeroConvertidoParteDecimal);
}
void deNa10Entero(int *BaseOrigen,char *numeroEntero, char *stringResultadoNa10){

    char *pDigito;
    pDigito=(char *)malloc(sizeof(char));

    int *baseElevada;
    baseElevada=(int *)malloc(sizeof(int));

    int *indicePotencia;
    indicePotencia=(int *)malloc(sizeof(int));

    int *pDigitoNum;
    pDigitoNum=(int *)malloc(sizeof(int));

    int *indiceNumeroEntero;
    indiceNumeroEntero=(int *)malloc(sizeof(int));

    int *tamNumeroEntero;
    tamNumeroEntero=(int *)malloc(sizeof(int));

    double *resultadoNa10;
    resultadoNa10=(double *)malloc(sizeof(double));

    char *parteDelNumero;
    parteDelNumero=(char *)malloc(sizeof(char));

    *parteDelNumero='e';
    *pDigitoNum=0;
    *tamNumeroEntero=strlen(numeroEntero);
    *indiceNumeroEntero=*tamNumeroEntero-1;
    *indicePotencia=0;
    *resultadoNa10=0;
    *pDigito=numeroEntero[*indiceNumeroEntero];
    while( *indiceNumeroEntero>=0){
        //printf("indiceNumeroEntero: %d\n",*indiceNumeroEntero);
        //printf("tamNumeroEntero: %d\n",*tamNumeroEntero);
        mapearDigito(pDigito,pDigitoNum);

        *baseElevada=pow(*BaseOrigen,*indicePotencia);

        *indicePotencia=*indicePotencia+1;
        //printf("pDigito Es: %c\n", *pDigito);
        //printf("baseOrigen Es: %d\n", *BaseOrigen);
        //printf("baseElevada Es: %d\n", *baseElevada);
        //printf("pDigitoNum Es: %d\n", *pDigitoNum);
        *resultadoNa10= *resultadoNa10 + (double)(*pDigitoNum * *baseElevada);
       // printf("el resultado es: %f\n", *resultadoNa10);
        //printf("---------------------------------------------------\n");
        *indiceNumeroEntero=*indiceNumeroEntero-1;
        *pDigito=numeroEntero[*indiceNumeroEntero];
    }
    toString(resultadoNa10,stringResultadoNa10,parteDelNumero);

    //printf("el resultado es: %s\n", stringResultadoNa10);
    free(baseElevada);
    free(pDigito);
    free(pDigitoNum);
    free(indicePotencia);
    free(indiceNumeroEntero);
    free(tamNumeroEntero);
    free(resultadoNa10);
    free(parteDelNumero);
}

void deNa10Decimal(int *BaseOrigen,char *numeroDecimal, char *resultadoNa10String){
    char *pDigito;
    pDigito=(char *)malloc(sizeof(char));

    int *baseElevada;
    baseElevada=(int *)malloc(sizeof(int));

    int *indicePotencia;
    indicePotencia=(int *)malloc(sizeof(int));

    int *pDigitoNum;
    pDigitoNum=(int *)malloc(sizeof(int));

    int *indiceNumeroDecimal;
    indiceNumeroDecimal=(int *)malloc(sizeof(int));

    int *tamNumeroDecimal;
    tamNumeroDecimal=(int *)malloc(sizeof(int));

    double *resultadoNa10;
    resultadoNa10=(double *)malloc(sizeof(double));

    char *parteDelNumero;
    parteDelNumero=(char *)malloc(sizeof(char));

    *parteDelNumero='d';
    *pDigitoNum=0;
    *tamNumeroDecimal=strlen(numeroDecimal);
    *indiceNumeroDecimal=0;
    *indicePotencia=1;
    *resultadoNa10=0;

    *pDigito=numeroDecimal[*indiceNumeroDecimal];
    //printf("pDigito Es: %c\n", *pDigito);
    while( numeroDecimal[*indiceNumeroDecimal]!='\0'){
        mapearDigito(pDigito,pDigitoNum);

        *baseElevada=pow(*BaseOrigen,*indicePotencia);

        *indicePotencia=*indicePotencia+1;
        //printf("baseOrigen Es: %d\n", *BaseOrigen);
        //printf("baseElevada Es: %d\n", *baseElevada);
        //printf("pDigitoNum Es: %d\n", *pDigitoNum);
        *resultadoNa10= *resultadoNa10 + ((double) *pDigitoNum /(double) *baseElevada);
        //printf("El resultado es: %f\n", *resultadoNa10);
        //printf("---------------------------------------------------\n");
        *indiceNumeroDecimal=*indiceNumeroDecimal+1;
        *pDigito=numeroDecimal[*indiceNumeroDecimal];
    }

    toString(resultadoNa10,resultadoNa10String,parteDelNumero);

    //printf("resultado parte decimal:%s\n", resultadoNa10String);
    free(baseElevada);
    free(pDigito);
    free(pDigitoNum);
    free(indicePotencia);
    free(indiceNumeroDecimal);
    free(tamNumeroDecimal);
    free(resultadoNa10);
    free(parteDelNumero);
}
 void toString(double *resultadoFloat, char * resultadoString, char * parteNum ){
     int *tamResultado;
    tamResultado=(int *)malloc(sizeof(int));

    int *indiceResultado;
    indiceResultado=(int *)malloc(sizeof(int));

    sprintf(resultadoString,"%f",*resultadoFloat);
    //printf("resultadoString: %s\n",resultadoString);
    //printf("resultadoFloat: %f\n",*resultadoFloat);
    *tamResultado=strlen(resultadoString);
    *indiceResultado=0;
    //printf("tamResultado: %d\n",*tamResultado);
    if(*parteNum=='d'){
        while(*indiceResultado < *tamResultado){
            if(*indiceResultado>=1){
                resultadoString[(*indiceResultado) -1]=resultadoString[*indiceResultado];
                resultadoString[*indiceResultado]='0';
            }
            *indiceResultado=*indiceResultado +1;
        }
    resultadoString[*tamResultado-1]='\0';
    }else{
        resultadoString[*tamResultado]='\0';
    }

    free(tamResultado);
    free(indiceResultado);
 }
 void mapearDigito(char * pDigito, int *digitoInt){

    if(*pDigito==('A') || *pDigito==('B') || *pDigito==('C') || *pDigito==('D') || *pDigito==('E') || *pDigito==('F')){
        *digitoInt= *pDigito - 55;
    }else{
        if(*pDigito==('a') || *pDigito==('b') || *pDigito==('c') || *pDigito==('d') || *pDigito==('e') || *pDigito==('f')){
            *digitoInt=*pDigito-87;
            //printf("digitoInt Es: %d\n", *digitoInt);
            //printf("digitoInt Es: %d\n", *digitoInt);
        }else{
            *digitoInt=*pDigito - 48;
    }
    }
 }
 void concatenarCadenas(char *numEntero, char *numDecimal, char *numCompleto){
    int *indiceNumCompleto;
    indiceNumCompleto=(int *)malloc(sizeof(int));

    int *indiceNum;
    indiceNum=(int *)malloc(sizeof(int));

    *indiceNum=0;
    *indiceNumCompleto=0;

    while(numEntero[*indiceNum]!='.'){
        numCompleto[*indiceNumCompleto]=numEntero[*indiceNum];
        *indiceNum=*indiceNum+1;
        *indiceNumCompleto=*indiceNumCompleto+1;
    }

    *indiceNum=0;

    while(numDecimal[*indiceNum]!='\0'){
        numCompleto[*indiceNumCompleto]=numDecimal[*indiceNum];
        *indiceNum=*indiceNum+1;
        *indiceNumCompleto=*indiceNumCompleto+1;
    }

     numCompleto[*indiceNumCompleto]='\0';

    free(indiceNum);
    free(indiceNumCompleto);
 }
 void dividirCadenas(char *numEntero, char *numDecimal, char *numCompleto){
    // printf("Entra en dividirCadenas\n");
    int *indiceNumCompleto;
    indiceNumCompleto=(int *)malloc(sizeof(int));

    int *indiceNum;
    indiceNum=(int *)malloc(sizeof(int));

    *indiceNum=0;
    *indiceNumCompleto=0;

    while(numCompleto[*indiceNumCompleto]!='.'){
        numEntero[*indiceNum]=numCompleto[*indiceNumCompleto];
        *indiceNum=*indiceNum+1;
        *indiceNumCompleto=*indiceNumCompleto+1;
    }

    *indiceNumCompleto=*indiceNumCompleto+1;
    numEntero[*indiceNum]='\0';
    *indiceNum=0;

    while(numCompleto[*indiceNumCompleto]!='\0'){
        // printf("Numero: %c\n", numCompleto[*indiceNumCompleto]);
        numDecimal[*indiceNum]=numCompleto[*indiceNumCompleto];
        *indiceNum=*indiceNum+1;
        *indiceNumCompleto=*indiceNumCompleto+1;
    }
    numDecimal[*indiceNum]='\0';

    free(indiceNum);
    free(indiceNumCompleto);
 }
