//
// Created by Henrique on 25/09/2023.
//

#include "aux_funcoes.h"
#include "aux_geral.h"
#include "aux_arquivos.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int parte_1(char *filename){


    FILE* csv = abre_arquivo(filename,"r");

    Registro *registro = novoRegistro();
    Cabecalho *cabecalho = novoCabecalho();
    Lista *lista = novaLista();

    //Le e descarta a primeira linha do arquivo
    char primeiraLinha[1024];
    if (fgets(primeiraLinha, sizeof(primeiraLinha), csv) == NULL) {
        perror("Erro ao ler os cabeçalhos");
        fecha_arquivo(csv);
        return 1;
    }

    // Abre o arquivo binário para escrita
    FILE* binario = abre_arquivo("tabela.bin","wb");

    if (binario == NULL) {
        perror("Erro ao criar o arquivo binário");
        fecha_arquivo(csv);
        return 1;
    }

    // Escreve o cabeçalho no arquivo binário
    escreverCabecalho(binario, cabecalho);

    // Lê e escreve cada linha do CSV no arquivo binário
    Registro* temp = malloc(sizeof(Registro));
    while(lerLinhaCSV(csv, temp)) {
        fwrite(&registro->tecnologiaOrigem.string, sizeof(char)*registro->tecnologiaOrigem.tamanho, 1, binario);
        fwrite(&registro->grupo, sizeof(int), 1, binario);
        fwrite(&registro->popularidade, sizeof(int), 1, binario);
        fwrite(&registro->tecnologiaDestino.string, sizeof(char)*registro->tecnologiaDestino.tamanho, 1, binario);
        fwrite(&registro->peso, sizeof(int), 1, binario);
        cabecalho->proxRRN++;

        int Nome = procura_tecnologia(lista,temp);
        int Par = procura_par(lista, temp);

        if (!Nome){

            registroNaLista(temp,lista);

            if (!Nome){
                cabecalho->nroTecnologias = cabecalho->nroTecnologias + 1;
            }

        }

        if (!Par){
                cabecalho->nroParesTecnologias = cabecalho->nroParesTecnologias + 1;
            }


        temp = malloc(sizeof(Registro));


    }
    free(temp);



    rewind(binario);
    cabecalho->status = '1'; // Arquivo consistente agora
    escreverCabecalho(binario, cabecalho);

    //printf("a");


    binarioNaTela("tabela.bin");

    fecha_arquivo(csv);
    fecha_arquivo(binario);
    deletaRegistro(registro);
    deletaCabecalho(cabecalho);
    liberaLista(lista);

}
int parte_2(char *filename){


    FILE* binario = abre_arquivo(filename,"rb");

    Cabecalho *cabecalho = novoCabecalho();
    Registro *registro = novoRegistro();

    //Lendo cabecalho
    fseek(binario, 0, 0);

    fread(&(cabecalho->status), sizeof(char),1, binario);
    fread(&(cabecalho->proxRRN),sizeof(int),1, binario);
    fread(&(cabecalho->nroTecnologias), sizeof(int), 1, binario);
    fread(&(cabecalho->nroParesTecnologias), sizeof(int), 1, binario);


    while(!feof(binario))
    {


//----------------------------------LEIUTRA DOS DADOS DO ARQUIVO BINARIO--------------------------------------//
        if(fread(&(registro->removido),sizeof(char),1,binario))
        {


            if(registro->removido == '0') {

                fread(&(registro->grupo), sizeof(int), 1, binario);
                fread(&(registro->popularidade), sizeof(int), 1, binario);
                fread(&(registro->peso), sizeof(int), 1, binario);

                //string variavel
                fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, binario);
                fread(registro->tecnologiaOrigem.string, sizeof(char)*registro->tecnologiaOrigem.tamanho,1 , binario);
                registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';


                fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, binario);
                fread(registro->tecnologiaDestino.string, sizeof(char)*registro->tecnologiaDestino.tamanho,1 , binario);
                registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';

                char lixo = '$';
                while (!feof(binario) && lixo == '$') {
                    fread(&lixo, sizeof(char), 1, binario);
                }

                if (!feof(binario)) {
                    fseek(binario, -1, 1);
                }

                printaRegistro(registro);

            }


            if(registro->removido == '1')
            {
                    fread(&(registro->grupo), sizeof(int), 1, binario);
                    fread(&(registro->popularidade), sizeof(int), 1, binario);
                    fread(&(registro->peso), sizeof(int), 1, binario);


                    //string variavel
                    fread(&registro->tecnologiaOrigem.tamanho,sizeof(int),1,binario);
                    fread(registro->tecnologiaOrigem.string,sizeof(char),registro->tecnologiaOrigem.tamanho,binario);

                    fread(&registro->tecnologiaDestino.tamanho,sizeof(int),1,binario);
                    fread(registro->tecnologiaDestino.string,sizeof(char),registro->tecnologiaDestino.tamanho,binario);

                    if (feof(binario)){
                    return 0;
                    }

                    char lixo = '$';
                    while (!feof(binario) && lixo == '$'){
                    fread(&lixo, 1, sizeof(char), binario);
                     }

                    if (!feof(binario)){
                    fseek(binario, -1, 1);
                    }


            }


        }
    }
    free(registro);
    free(cabecalho);
    fclose(binario);
}
int parte_3(char *filename, char* especifica,char* info_busca, Registro *registro){

    FILE* binario = abre_arquivo(filename,"rb");

    if (binario == NULL){

        printf("Falha no processamento do arquivo.\n");
        return 0;
    }

    Registro *registro = novoRegistro();
    Cabecalho *cabecalho = novoCabecalho();
    Lista *lista = novaLista();

    fseek(binario, 0, 0);

    fread(&(cabecalho->status), sizeof(char),1, binario);

    if (cabecalho->status == '0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    fread(&(cabecalho->proxRRN),sizeof(int),1, binario);
    fread(&(cabecalho->nroTecnologias), sizeof(int), 1, binario);
    fread(&(cabecalho->nroParesTecnologias), sizeof(int), 1, binario);

    Registro* temp = malloc(sizeof(Registro));

    int flag_encontrou = 0;
    int busca_int = 0;

    while(fread(&(registro->removido),sizeof(char), 1, binario)){

        if(registro->removido == '0'){

            fread(&(registro->grupo), sizeof(int), 1, binario);
            fread(&(registro->popularidade), sizeof(int), 1, binario);
            fread(&(registro->peso), sizeof(int), 1, binario);

            //string variavel
            fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, binario);
            fread(registro->tecnologiaOrigem.string, sizeof(char)*registro->tecnologiaOrigem.tamanho,1 , binario);
            registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';


            fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, binario);
            fread(registro->tecnologiaDestino.string, sizeof(char)*registro->tecnologiaDestino.tamanho,1 , binario);
            registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';


            if (strcmp(especifica, "nomeTecnologiaOrigem") == 0){
                if (registro->tecnologiaOrigem.tamanho == strlen(busca) && strncmp(busca, registro->tecnologiaOrigem.string, registro->tecnologiaOrigem.tamanho) == 0){
                    imprimirRegistrosNaTela(&registro);
                    flag_encontrou = 1;
                }
            }
            if (strcmp(especifica, "grupo") == 0){


                if (sscanf(info_busca, "%d", &busca_int) == 1 && busca_int == registro->grupo){

                    imprimirRegistrosNaTela(&registro);
                    flag_encontrou = 1;
                }
            }
            if (strcmp(especifica, "popularidade") == 0){


                if (sscanf(info_busca, "%d", &busca_int) == 1 && busca_int == registro->popularidade)
                {
                    imprimirRegistrosNaTela(&registro);
                    flag_encontrou = 1;
                }
            }
            if (strcmp(especifica, "nomeTecnologiaDestino") == 0){

                if (registro->tecnologiaDestino.tamanho == strlen(busca) && strncmp(busca, registro->tecnologiaDestino.string, registro->tecnologiaDestino.tamanho) == 0)
                {
                    imprimirRegistrosNaTela(&out);
                    flag_encontrou = 1;
                }
            }
            if (strcmp(especifica, "peso") == 0)
            {

                if (sscanf(info_busca, "%d", &busca_int) == 1 && busca_int == registro->peso)
                {
                    imprimirRegistrosNaTela(registro);
                    flag_encontrou = 1;
                }
            }

            if(!flag_encontrou) printf("Registro inexistente.\n");

            char lixo = '$';
            while (!feof(binario) && lixo == '$') {
                fread(&lixo, sizeof(char), 1, binario);
            }

            if (!feof(binario)) {
                fseek(binario, -1, 1);
            }

        }

        if(registro->removido == '1'){

            fread(&(registro->grupo), sizeof(int), 1, binario);
            fread(&(registro->popularidade), sizeof(int), 1, binario);
            fread(&(registro->peso), sizeof(int), 1, binario);

            //string variavel
            fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, binario);
            fread(registro->tecnologiaOrigem.string, sizeof(char)*registro->tecnologiaOrigem.tamanho,1 , binario);
            registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';


            fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, binario);
            fread(registro->tecnologiaDestino.string, sizeof(char)*registro->tecnologiaDestino.tamanho,1 , binario);
            registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';


            char lixo = '$';
            while (!feof(binario) && lixo == '$') {
                fread(&lixo, sizeof(char), 1, binario);
            }

            if (!feof(binario)) {
                fseek(binario, -1, 1);
            }

        }

    }

}

    fecha_arquivo(binario);
    liberaLista(lista);
    deletaCabecalho(cabecalho);
    deletaRegistro(registro);

}
int parte_4(char *filename, int RRN_P) {

    FILE* binario = abre_arquivo(filename,"rb");

    if (binario == NULL){

        printf("Falha no processamento do arquivo.\n");
        return 0;
    }

    Registro *registro = novoRegistro();
    Cabecalho *cabecalho = novoCabecalho();

    fseek(binario, 0, 0);

    fread(&(cabecalho->status), sizeof(char),1, binario);
    fread(&(cabecalho->proxRRN),sizeof(int),1, binario);
    fread(&(cabecalho->nroTecnologias), sizeof(int), 1, binario);
    fread(&(cabecalho->nroParesTecnologias), sizeof(int), 1, binario);

    int RRN = RRN_P;
    if (cabecalho->proxRRN <= RRN) {
        printf("Registro inexistente.");
        return 0;
    }
    fseek(binario, RRN * TAM_REGISTRO, 1);  // coloca o ponteiro no inicio do registro (byte offset)

    char lixo = '$';
    while (!feof(binario) && lixo == '$') {
        fread(&lixo, sizeof(char), 1, binario);
    }

    if (!feof(binario)) {
        fseek(binario, -1, 1);
    }

    //leitura_tabela(binario, registro);
    fread(&(registro->removido),sizeof(char), 1, binario);
    fread(&(registro->grupo), sizeof(int), 1, binario);
    fread(&(registro->popularidade), sizeof(int), 1, binario);
    fread(&(registro->peso), sizeof(int), 1, binario);

    //string variavel
    fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, binario);
    fread(registro->tecnologiaOrigem.string, sizeof(char)*registro->tecnologiaOrigem.tamanho,1 , binario);
    registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';


    fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, binario);
    fread(registro->tecnologiaDestino.string, sizeof(char)*registro->tecnologiaDestino.tamanho,1 , binario);
    registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';

    printaRegistro(registro);

    fclose(binario);
    deletaRegistro(registro);
    deletaCabecalho(cabecalho);

    return 0;

}

//Função para pesquisar na árvore B
//void parte_5(Registro *x, Ponteiro P)
//{
//    long i =1;
//    if(P == NULL)
//    {
//        printf("Registro não esta presente na arvore");
//        return;
//    }
//    while (i<P ->n && x-> Chave > P -> r [i-1].Chave) i++;
//    if(x -> Chave == P -> r[i - 1].Chave)
//    {
//        *x = P ->r[i-1];
//        return;
//    }
//    if(x -> Chave < P -> r[i-1].Chave)
//    {
//        Pesquisa(x, P -> p[i-1]);
//    }
//    else Pesquisa (x, P -> p[i]);
//}

int parte_6(FILE *dados, FILE *indice , char *busca )
{
    Cabecalho_arvore cabecalho;
    lerCabecalho(&cabecalho, indice);
    if (cabecalho.status == '0')
    {
        printf("Falha no processamento do arquivo.");
        return -1;
    }

    if (recupera(busca, cabecalho.noRaiz, indice) == -1)
    {
        printf("Registro inexistente.\n");
    }
    else
    {
        parte_4((char *) dados, recupera(busca, cabecalho.noRaiz, indice));
    }
    return 0;

} //ok






