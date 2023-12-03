/* Defines necessários para o funcionamento da strsep */
#define _BSD_SOURCE
#define _DEFAULT_SOURCE
#define _GNU_SOURCE

#include "../controlador_csv.h"

void csv_pular_cabecalho(FILE * csv){
    char tmp[STR_DEFAULT_SIZE];

    fscanf(csv,"%s\n",tmp);

    return;
}

regs_tecnologia_type csv_ler_registro(FILE * csv){
    regs_tecnologia_type registro;

    registro.removido = '0';

    char * linha;
    linha = (char *) malloc(STR_DEFAULT_SIZE * sizeof(char));
    
    fscanf(csv,"%[^\n]s",linha);

    char *token;
    registro.removido = '0';

    token = strsep(&linha,",\n");
    if(token){
        registro.tecnologiaOrigem.tamanho = strlen(token);
        strcpy(registro.tecnologiaOrigem.string,token);
        registro.tecnologiaDestino.string[strlen(token)] = '\0';
    }

    token = strsep(&linha,",\n");
    registro.grupo = atoi(token);

    token = strsep(&linha,",\n");
    registro.popularidade = atoi(token);

    token = strsep(&linha,",\n");
    if(token){
        registro.tecnologiaDestino.tamanho = strlen(token);
        strcpy(registro.tecnologiaDestino.string,token);
        registro.tecnologiaDestino.string[strlen(token)] = '\0';
    }

    token = strsep(&linha,",\n");
    registro.peso = atoi(token);

    fgetc(csv); 

    return registro;
}

