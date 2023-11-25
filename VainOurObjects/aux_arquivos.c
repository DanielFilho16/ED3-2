//
// Created by Henrique on 25/09/2023.
//
#include <stdio.h>

FILE* abre_arquivo(char* filename, char *modo){

    FILE *fp;
    fp = fopen(filename, modo);

    if (fp == NULL){
        printf("Falha no processamento do arquivo");

        return 0;
    }
}

void fecha_arquivo(FILE *arquivo){
    fclose(arquivo);
}