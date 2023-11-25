//
// Created by Henrique on 25/09/2023.
//
#include "aux_geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
    *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *) malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for(i = 0; i < fl; i++) {
        cs += (unsigned long) mb[i];
    }
    printf("%lf\n", (cs / (double) 100));
    free(mb);
    fclose(fs);
}

void scan_quote_string(char *str) {

    /*
    *	Use essa função para ler um campo string delimitado entre aspas (").
    *	Chame ela na hora que for ler tal campo. Por exemplo:
    *
    *	A entrada está da seguinte forma:
    *		nomeDoCampo "MARIA DA SILVA"
    *
    *	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
    *		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
    *		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
    *
    */

    char R;

    while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

    if(R == 'N' || R == 'n') { // campo NULO
        getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    } else if(R == '\"') {
        if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    } else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
        str[0] = R;
        scanf("%s", &str[1]);
    } else { // EOF
        strcpy(str, "");
    }
}

void printaRegistro(Registro *registro){
    if(registro->tecnologiaOrigem.string[0] == '$'){
        printf(" ,");
    }else printf("%s,", registro->tecnologiaOrigem.string);

    if(registro->grupo == -1){
        printf(" ,");
    }else printf("%d,", registro->grupo);

    if(registro->popularidade == -1){
        printf(" ,");
    }else printf("%d,", registro->popularidade);

    if(registro->tecnologiaDestino.string[0] == '$'){
        printf(" ,");
    }else printf("%s,", registro->tecnologiaDestino.string);

    if(registro->peso == -1){
        printf(" \n");
    }else printf("%d \n", registro->peso);
}

struct Registro *novoRegistro(){
    Registro *registro = (Registro *)malloc(sizeof(TAM_REGISTRO));
    if(registro == NULL){
        printf("Erro ao alocar memoria do registro");
    };

    //Malocando e inicializando TecnologaOrigem
    registro->tecnologiaOrigem.tamanho = 0;//Colocar dps que ler

    //Malocando e inicializando TecnologiasDestino
    registro->tecnologiaDestino.tamanho = 0;// Colocar dps que ler

    //Inicializando as partes estaticas do registro como valores padroes para caso faltar dados
    registro->removido = '0';
    registro->grupo = 0;
    registro->popularidade = 0;
    registro->peso = 0;

    return registro;

}
void deletaRegistro(Registro *registro){
    free(registro);
}

struct Cabecalho *novoCabecalho(){
    Cabecalho *cabecalho = (Cabecalho *)malloc(sizeof(TAM_CABECALHO));
    if(cabecalho == NULL){
        printf("Erro ao alocar memoria do cabecalho");
    }

    //Inicializando struct de cabecalho
    cabecalho->status = 1; //indica se o arquivo de dados esta consistente 0(setar 0 ao abrir para escrita) 1(apos escrever)
    cabecalho->proxRRN =0; //iniciado com 0
    cabecalho->nroTecnologias = 0; //quantidade, inciail eh 0, apenas diferentes
    cabecalho->nroParesTecnologias =0;

    return cabecalho;
}
void deletaCabecalho(Cabecalho *cabecalho){
    free(cabecalho);

}

struct Lista *novaLista(){
    Lista *l = (Lista *) malloc(sizeof (Lista));

    if(l == NULL){
        printf(" Erro de alocação de memoria");
        return 0;
    }

    l->inicio = NULL;
    l->qnt = 0;

}
void liberaLista(Lista *lista){
    if(lista->inicio != NULL){
        No* no;
        while(lista->inicio != NULL){
            no = lista->inicio;
            lista->inicio = no->prox;
            free(no);
        }
        free(lista);
    }
}

int lerLinhaCSV(FILE *arquivoCSV, Registro *registro) {
    char linha[1024]; // Assumindo que cada linha do CSV tem menos de 1024 caracteres
    if (fgets(linha, sizeof(linha), arquivoCSV) == NULL) {
        return 0; // Fim do arquivo
    }

    // Inicializa campos opcionais com valores padrão
    strcpy(registro->tecnologiaOrigem.string,"NULL");
    strcpy(registro->tecnologiaDestino.string,"NULL");


    // Analisa os campos da linha
    char *token = strtok(linha, ",");
    registro->removido = '0';
    if (token) {
        registro->tecnologiaOrigem.tamanho = strlen(token);
        strcpy(registro->tecnologiaOrigem.string,token);

    }
    token = strtok(NULL, ",");
    registro->grupo = atoi(token);


    token = strtok(NULL, ",");
    registro->popularidade = atoi(token);
    token = strtok(NULL, ",");
    if (token) {
        registro->tecnologiaDestino.tamanho = strlen(token);
        strcpy(registro->tecnologiaDestino.string,token);
    }
    token = strtok(NULL, ",");
    registro->peso = atoi(token);



    return 1;
}

void registroNaLista(Registro *registro,Lista *lista){

    if(lista == NULL || registro == NULL){
        return;
    }

    No *novo = (No *) malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro de alocação de memoria");
        return;
    }

    novo->reg = registro;
    novo->prox = NULL;

    lista->qnt++;

    if(lista->inicio == NULL){
            lista->inicio = novo;
    }

    else{
        No *aux = lista->inicio;

        while(aux->prox != NULL){

            aux = aux->prox;

        }

        aux->prox = novo;

    }
}
int procura_tecnologia(Lista *lista,Registro *registro){

    No *n = lista->inicio;

    while (n != NULL){

        if (strcmp(n->reg->tecnologiaOrigem.string, registro->tecnologiaOrigem.string) == 0){
            return 1;
        }

        n = n->prox;
    }
    return 0;
}
int procura_par(Lista *lista,Registro *registro){

    No *n = lista->inicio;

    while (n != NULL){

        if (strcmp(n->reg->tecnologiaOrigem.string, registro->tecnologiaOrigem.string) == 0){
            if(((n->reg->tecnologiaDestino.string == NULL) || strcmp(n->reg->tecnologiaDestino.string,"\n") == 0) ) {
                return 1;
            }
            else if(strcmp(n->reg->tecnologiaDestino.string, registro->tecnologiaDestino.string) == 0){
                return 1;
            } else return 0;
                       return 1;
        }else return 0;

        n = n->prox;
    }

    return 0;
}

void escreverCabecalho(FILE *arquivoBinario, Cabecalho *cabecalho) {
    fwrite(cabecalho, sizeof(Cabecalho), 1, arquivoBinario);
}


void exibe(Registro *Registro){
    printf("nomeTecnologiaOrigem: %s\n", Registro->tecnologiaOrigem.string);
    printf("grupo: %d\n", Registro->grupo);
    printf("popularidade: %d\n", Registro->popularidade);
    printf("nomeTecnologiaDestino: %s\n", Registro->tecnologiaDestino.string);
    printf("peso: %d\n\n", Registro->peso);
}

//void parte_3(FILE *arquivo,Registro *registro,Cabecalho *cabecalho) {
//
//    int n; // Número de vezes que a busca deve ser executada
//    int totalRegistros = 0;
//    int encontrados = 0;
//    // Lê os registros do arquivo
//    fseek(arquivo, 0, 0);
//
//    fread(&(cabecalho->status), sizeof(char),1, arquivo);
//    fread(&(cabecalho->proxRRN),sizeof(int),1, arquivo);
//    fread(&(cabecalho->nroTecnologias), sizeof(int), 1, arquivo);
//    fread(&(cabecalho->nroParesTecnologias), sizeof(int), 1, arquivo);
//
//
//    while(!feof(arquivo)) {
//
//
////----------------------------------LEIUTRA DOS DADOS DO ARQUIVO BINARIO--------------------------------------//
//        if (fread(&(registro->removido), sizeof(char), 1, arquivo)) {
//
//            fread(&(registro->grupo), sizeof(int), 1, arquivo);
//            fread(&(registro->popularidade), sizeof(int), 1, arquivo);
//            fread(&(registro->peso), sizeof(int), 1, arquivo);
//
//            //string variavel
//            fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
//            fread(registro->tecnologiaOrigem.string, sizeof(char) * registro->tecnologiaOrigem.tamanho, 1, arquivo);
//            // if(registro->tecnologiaOrigem.string[0] == '$') registro->tecnologiaOrigem.string[0] = ' ';
//            registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';
//
//
//            fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
//            fread(registro->tecnologiaDestino.string, sizeof(char) * registro->tecnologiaDestino.tamanho, 1,
//                  arquivo);
//            // if(registro->tecnologiaDestino.string[0] == '$') registro->tecnologiaDestino.string[0] = ' ';
//            registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';
//
//            char lixo = '$';
//            while (!feof(arquivo) && lixo == '$') {
//                fread(&lixo, sizeof(char), 1, arquivo);
//            }
//
//            if (!feof(arquivo)) {
//                fseek(arquivo, -1, 1);
//            }
//            totalRegistros++;
//        }
//    }
//        fclose(arquivo);
//
//            scanf("%d", &n);
//
//            while (n > 0) {
//                char campoBusca[TAM_REGISTRO]; //Declara e pega o que vai ser pesquisado
//                scanf("%s", campoBusca);
//
//                for (int i = 0; i < totalRegistros; i++) {
//                    if (registro->removido == 0) { // Verifica se o registro não está logicamente removido
//                        if (strcmp(campoBusca, "nome") == 0) {
//                            char buscaNome[TAM_REGISTRO];
//                            printf("Digite o nome a ser buscado: ");
//                            scan_quote_string(buscaNome);
//                            if (strcmp(buscaNome, registros[i].nome) == 0) {
//                                encontrados++;
//                                printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id,
//                                       registros[i].nome, registros[i].peso);
//                            }
//                        } else if (strcmp(campoBusca, "peso") == 0) {
//                            double buscaPeso;
//                            printf("Digite o peso a ser buscado: ");
//                            scanf("%lf", &buscaPeso);
//                            if (buscaPeso == registros[i].peso) {
//                                encontrados++;
//                                printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id,
//                                       registros[i].nome, registros[i].peso);
//                            }
//                        }else if (strcmp(campoBusca, "peso") == 0) {
//                            double buscaPeso;
//                            printf("Digite o peso a ser buscado: ");
//                            scanf("%lf", &buscaPeso);
//                            if (buscaPeso == registros[i].peso) {
//                                encontrados++;
//                                printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id,
//                                       registros[i].nome, registros[i].peso);
//                            }
//                        }else if (strcmp(campoBusca, "peso") == 0) {
//                            double buscaPeso;
//                            printf("Digite o peso a ser buscado: ");
//                            scanf("%lf", &buscaPeso);
//                            if (buscaPeso == registros[i].peso) {
//                                encontrados++;
//                                printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id,
//                                       registros[i].nome, registros[i].peso);
//                            }
//                        }else if (strcmp(campoBusca, "peso") == 0) {
//                            double buscaPeso;
//                            printf("Digite o peso a ser buscado: ");
//                            scanf("%lf", &buscaPeso);
//                            if (buscaPeso == registros[i].peso) {
//                                encontrados++;
//                                printf("Registro encontrado: ID %d, Nome: %s, Peso: %lf\n", registros[i].id,
//                                       registros[i].nome, registros[i].peso);
//                            }
//                        }
//                    }
//                }
//
//            }
//
//
//            if (encontrados == 0) {
//                printf("Nenhum registro encontrado.\n");
//            }
//
//            n--;
//        }

void

void InserePagina(Ponteiro P, Registro R, Ponteiro Pd)
{
    short nao_achou;
    int k;
    k = P -> n;
    nao_achou = (k>0);
    while (nao_achou)
    {
        if(R.Chave >= P -> r[k-1].Chave)
            {
                nao_achou = false;
                break;
            }
        P -> r[k] = P -> r [k-1];
        P -> p[k+1] = P -> p [k];
        k--;
        if(k < 1)
        {
            nao_achou = false;
        }
    }
    P -> r[k] = R;
    P -> p[k+1] = Pd;
    P -> n++;
}

void Ins(Registro R, Ponteiro P, short *Cresceu, Registro *RegRetorno, Ponteiro *P_retorno) {
    long i = 1;
    long j;

    Ponteiro P_temp;

    if (P == NULL) {
        *Cresceu = true;
        (*RegRetorno) = R;
        (*P_retorno) = NULL;
        return;
    }

    while (i < P->n && Reg.Chave > P->r[i - 1].Chave) i++;
    if (Reg.Chave == P->r[i - 1].Chave) {
        printf("Erro: registro já presente");
        *Cresceu = false;
        return;
    }


    if (Reg.Chave < P->r[i - 1].Chave) i--;
    Ins(Reg, P->p[i], Cresceu, RegRetorno, P_retorno)
    if (!*Cresceu) return;
    if (P->n<[mm]) //Pagina tem espaco
    {
        InsereNaPagina(P, *RegRetorno, *P_retorno);
        *Cresceu = FALSE;
        return;
    }
//Overflow: Pagina tem que ser dividida

    P_temp = (Ponteiro) malloc(sizeof(Pagina));
    P_temp->n = 0;
    P_temp->p[0] = null;
    if (i < m + 1) {
        InserePagina(P_temp, P->r[mm - 1], P->p[mm]);
        P->n--;
        InserePagina(P, *RegRetorno, *P_retorno);
    } else InserePagina(P_temp, *RegRetorno, *P_retorno);
    for (j = m + 2; j <= mm; j++) {
        InserePagina(P_temp, P->r[j - 1], P->p[j]);
        P->n = m;
        P_temp->p[0] = P->P[m + 1];
        *RegRetorno = P->r[m];
        *P_retorno = P_temp;
    }
}

void Insere (Registro Reg, Ponteiro *P)
{
    short Cresceu;
    Registro RegRetorno;
    Pagina *P_retorno, *P_temp;
    Ins(Reg, *P,  &Cresceu, &RegRetorno, &P_retorno);
    if (Cresceu) /*Arvore cresce na altura pela raiz*/
    {
        P_temp = (Pagina *) malloc (sizeof (Pagina));
        P_temp -> n =1;
        P_temp -> r[0] = RegRetorno;
        P_temp -> p[1] = P_retorno;
        P_temp -> p[0] = *P;
        *P = P_temp;
    }


}




