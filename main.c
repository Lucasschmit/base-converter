#include <stdio.h>
#include <stdlib.h>
#define precision 16
#define precisionEntera 10
#define precisionDecimal 5

/*PROYECTO OdC "convert"*/

void divideNumero(char *n, char *nE, char *nD);

int main() {
    char *numero[precision];
    numero=malloc(precision * sizeof(char));

    char *numEntero[precisionEntera];
    numEntero=malloc(precisionEntera * sizeof(char));

    char *numDecimal[precisionDecimal];
    numDecimal=malloc(precisionDecimal * sizeof(char));

    int *baseOrigen;
    baseOrigen=malloc(sizeof(int));

    int *baseDestino;
    baseDestino=malloc(sizeof(int));

    int *cont;
    cont=malloc(sizeof(int));

    char *resultado[precision];
    resultado=malloc(precision * sizeof(char));

    int*numConvertido;
    numConvertido=malloc(sizeof(int));


    printf("Ingresar numero a ser cambiado de base\n");
    scanf("%s", *numero);
    printf("Ingresar base origen\n");
    scanf("%d", *baseOrigen);
    printf("Ingresar base destino\n");
    scanf("%d", *baseDestino);

    control();

    divideNumero(&numero,&numEntero,&numDecimal);

    switch(*baseDestino,*baseOrigen){
        case *baseDestino==10:
            deNa10Entero(&baseOrigen,&numEntero,&numConvertido);
            deNa10Decimal(&baseOrigen,&numDecimal,&numConvertido);
            break;
        case *baseOrigen==10:
            break;
        case(*baseDestino!=10 && *baseOrigen!=10):
            break;
    }

    free(numero);
    free(numEntero);
    free(numDecimal);
    free(baseOrigen);
    free(baseDestino);
    free(cont);
    free(resultado);
    free(numConvertido);
}
}
    return 0;
}

void control(char *num, int *baseO){
    if((*num - '0'< *baseO) || () )
}

void divideNumero(char *n, char *nE, char *nD){
    int *contador;
    contador=malloc(sizeof(int));
    do{
        *nE=*n;
        n++;
        nE++;
    }while(*n!=".")

    n++;

    for(*contador=0;*contador<precisionDecimal;*contador++){
        *n=*nD;
        n++;
        nD++;
    }
    free(contador);
}
