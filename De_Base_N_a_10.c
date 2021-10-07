#include <stdio.h>
void potencia(int *b, int *p, int cant);

void deNa10Entero(int *pBase,char *pN, int *pResultadoNa10 ){

    char *pDigito;
    pDigito=malloc(sizeof(char));

    int *pPot;
    pPot=malloc(sizeof(int));

    int *pCont;
    pCont=malloc(sizeof(int));

    char *pDigitoLetra;
    pDigitoLetra=malloc(sizeof(char));

    int *pDigigitoNum;
    pDigigitoNum=malloc(sizeof(int));

    while(*pN+precisionDecimal==nullptr){
            pN--;
    }

    do{
        *pDigito=*pN;
        pN--;
        if(*pDigito==('A') || *pDigito==('B') || *pDigito==('C') || *pDigito==('D') || *pDigito==('E') || *pDigito==('F')){
            *pDigigitoNum-= 'A' +10;
        }else{
            if(*pDigito==('a') || *pDigito==('b') || *pDigito==('c') || *pDigito==('d') || *pDigito==('e') || *pDigito==('e')){
               *pDigigitoNum-= 'a' +10;
               }else{
            *pDigigitoNum=*pDigito - '0';
               }
        }

        potencia(&base,&pot, &cont);

        *pResultadoNa10+=*pDigito * *pPot;
        cont++;
    }while(pN>pN+precisionEntera+1)

    free(pPot);
    free(pDigito);
    free(pDigitoLetra);
    free(pDigigitoNum);
    free(pCont);
}

void deNa10Decimal(int *pBase,char *pN, int *pResultadoNa10){

    char *pDigito;
    pDigito=malloc(sizeof(char));

    int *pPot;
    pPot=malloc(sizeof(int));

    int *pCont;
    pCont=malloc(sizeof(int));

    char *pDigitoLetra;
    pDigitoLetra=malloc(sizeof(char));

    int *pDigigitoNum;
    pDigigitoNum=malloc(sizeof(int));

    while(*pN+precisionDecimal==nullptr){
            pN--;
        }

    do{
        *pDigito=*pN;
        pN++;

        if(*pDigito==('A') || *pDigito==('B') || *pDigito==('C') || *pDigito==('D') || *pDigito==('E') || *pDigito==('F')){
            *pDigigitoNum-= 'A' +10;
        }else{
            if(*pDigito==('a') || *pDigito==('b') || *pDigito==('c') || *pDigito==('d') || *pDigito==('e') || *pDigito==('e')){
               *pDigigitoNum-= 'a' +10;
               }else{
            *pDigigitoNum=*pDigito - '0';
               }
        }

        potencia(&base,&pot, &cont);

        *pResultadoNa10+=*pDigito / *pPot;
        cont++;
    }while(pN<pN+precisionDecimal+1)

    free(pPot);
    free(pDigito);
    free(pDigitoLetra);
    free(pDigigitoNum);
    free(pCont);
}
void potencia(int *b, int *p, int cant){
    *p=1;
    for(int j=0;j< cant;j++)
        *p*=*b;
}
