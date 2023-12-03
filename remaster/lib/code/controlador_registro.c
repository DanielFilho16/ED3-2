#include "../controlador_registro.h"

void reg_seta_status(FILE * arquivo, char status){
    /** desc: A função atualiza o status do arquivo, alternando-o entre 1 e 0.
    */

    if(status  == '0' || status == '1'){
        fseek(arquivo,0,SEEK_SET);
        fwrite(&status,1,sizeof(char),arquivo);
    }

    return;
}

void reg_ler_lixo(FILE *arquivo){
    char lixo = CHAR_TRASH;
    
    while (!feof(arquivo) && lixo == CHAR_TRASH){
    fread(&lixo, sizeof(char), 1, arquivo);
}

    if (!feof(arquivo)){
        fseek(arquivo, -1, SEEK_CUR);
    }
}

void reg_preencher_lixo(FILE *arquivo,int total){
    char lixo = CHAR_TRASH;

    for(int i=0;i<total;i++){
        fwrite(&lixo, 1, sizeof(char), arquivo);
    }
}

regs_cabecalho_type regs_ler_cabecalho(FILE * arquivo){
    /** desc:
     * 
    */
    
    regs_cabecalho_type cabecalho;

    fseek(arquivo, 0, 0);

    fread(&cabecalho.status, sizeof(char),1, arquivo);

    if (cabecalho.status == '0'){
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    fread(&cabecalho.proxRRN,sizeof(int),1, arquivo);
    fread(&cabecalho.nroTecnologias, sizeof(int), 1, arquivo);
    fread(&cabecalho.nroParesTecnologias, sizeof(int), 1, arquivo);
    
    return cabecalho;

};

regs_tecnologia_type regs_ler_registro(FILE * arquivo){

    regs_tecnologia_type registro;

    fread(&registro.removido, sizeof(char), 1, arquivo);
    fread(&registro.grupo, sizeof(int), 1, arquivo);
    fread(&registro.popularidade, sizeof(int), 1, arquivo);
    fread(&registro.peso, sizeof(int), 1, arquivo);

    //string variavel
    fread(&registro.tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
    fread(registro.tecnologiaOrigem.string, sizeof(char)*registro.tecnologiaOrigem.tamanho,1 , arquivo);
    registro.tecnologiaOrigem.string[registro.tecnologiaOrigem.tamanho] = '\0';

    fread(&registro.tecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
    fread(registro.tecnologiaDestino.string, sizeof(char)*registro.tecnologiaDestino.tamanho,1 , arquivo);
    registro.tecnologiaDestino.string[registro.tecnologiaDestino.tamanho] = '\0';

    reg_ler_lixo(arquivo);

    return registro;
}

void regs_atualizar_cabecalho(FILE * arquivo, regs_cabecalho_type cabecalho){
    fseek(arquivo,0,SEEK_SET);
    fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho.proxRRN, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroTecnologias, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroParesTecnologias, sizeof(int), 1, arquivo);

    return;
}

void regs_escrever_registro(FILE * arquivo, regs_tecnologia_type registro, regs_cabecalho_type * cabecalho){
        fwrite(&registro.removido, sizeof(char), 1, arquivo);
        fwrite(&registro.grupo, sizeof(int), 1, arquivo);
        fwrite(&registro.popularidade, sizeof(int), 1, arquivo);
        fwrite(&registro.peso, sizeof(int), 1, arquivo);
        fwrite(&registro.tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
        fwrite(&registro.tecnologiaOrigem.string, sizeof(char)*(registro.tecnologiaOrigem.tamanho), 1, arquivo);
        fwrite(&registro.tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
        fwrite(&registro.tecnologiaDestino.string, sizeof(char)*(registro.tecnologiaDestino.tamanho), 1, arquivo);

        int bytes = 76 - 21 - registro.tecnologiaOrigem.tamanho - registro.tecnologiaDestino.tamanho;

        reg_preencher_lixo(arquivo,bytes);

        cabecalho->proxRRN++;
        return;
}



