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

/*Parte 6*/

Pagina *CriaPagina()
{
    Pagina *p = (Pagina *) malloc(sizeof(Pagina));
    p-> nroChavesno = 0;
    p-> alturaN = 0;
    p-> RRNdoNo = -1;

    for (int i = 0; i < 4; ++i)
    {
        p->ponteiros[i] = -1;
        p->camposReferencia[i] = -1;
        for (int j = 0; j < 3; ++j)
        {
            p->chaves[j][0] = '\0';
        }
    }
    return p;
}

void lerCabecalho(Cabecalho_arvore *cabecalhoArvore, FILE *indice)
{
  //ler todos os dados do cabecalho
    fread(&cabecalhoArvore->status, sizeof(char), 1, indice);
    fread(&cabecalhoArvore->noRaiz, sizeof(int), 1, indice);
    fread(&cabecalhoArvore->RRNproxNo, sizeof(int), 1, indice);
    fread(&cabecalhoArvore->lixo, sizeof(char), 196, indice);
}

void leitura_no (Pagina *pagina, FILE *indice)
{
    fread(&pagina->nroChavesno, sizeof(int), 1, indice);
    fread(&pagina->alturaN, sizeof(int), 1, indice);
    fread(&pagina->RRNdoNo, sizeof(int), 1, indice);

    for (int i = 0; i < 4; ++i)
    {
        fread(&pagina->ponteiros[i], sizeof(int), 1, indice);
        if (i < 3)
        {
            fread(&(pagina->chaves[i]), sizeof(char), 55, indice);
            fread(&(pagina->camposReferencia[i]), sizeof(int), 1, indice);
        }
    }
    for (int j = 0; j < 3; ++j)
    {
        for (int i = 0; i < 55; ++i)
        {
            if (pagina->chaves[j][i] == '$')
            {
                pagina->chaves[j][i] = '\0';
            }
        }
    }
}

//int recupera_rrn (char *busca, int rrnDaRaiz, FILE *indice)
//{
//    Pagina *pagina;
//    pagina = CriaPagina();
//    leitura_no(pagina, indice);
//    if (pagina->nroChavesno == 0)
//    {
//        return -1;
//    }
//    else
//    {
//        for (int i = 0; i < pagina->nroChavesno; ++i)
//        {
//            if (strcmp(busca, pagina->chaves[i]) == 0)
//            {
//                return pagina->camposReferencia[i];
//            }
//        }
//        for (int i = 0; i < pagina->nroChavesno; ++i)
//        {
//            if (strcmp(busca, pagina->chaves[i]) < 0)
//            {
//                return recupera_rrn(busca, pagina->ponteiros[i], indice);
//            }
//        }
//        return recupera_rrn(busca, pagina->ponteiros[pagina->nroChavesno], indice);
//    }
//}

int recuperando(char *busca, int rrnAtual, FILE *indice) //EncontraRRNrec
{
    fseek(indice, (rrnAtual + 1) * 205, SEEK_SET);
    Pagina pagina;
    leitura_no(&pagina, indice);

    for (int i = 0; i <= 3; ++i)
    {
        int resultado = strcmp(busca, pagina.chaves[i]);
        if (i == 3)
        {
            if (pagina.ponteiros[i] != -1)
            {
                return recuperando(busca, pagina.ponteiros[i], indice);
            }
            else
            {
                return -1;
            }
        }
        if (resultado < 0 || pagina.chaves[i][0] == '\0')
        {
            if (pagina.ponteiros[i] != -1)
            {
                return recuperando(busca, pagina.ponteiros[i], indice);
            }
            else
            {
                return -1;
            }
        }
        else if (resultado == 0)
        {
            return pagina.camposReferencia[i];
        }
    }
    if (pagina.ponteiros[pagina.nroChavesno] != -1)
    {
        return recuperando(busca, pagina.ponteiros[pagina.nroChavesno], indice);
    }
    else
    {
        return -1;
    }
}

int recupera(char *busca, int rrnDaRaiz,FILE *indice)
{
    return recuperando(busca, rrnDaRaiz, indice);
}

/*Fim da parte 6*/


/*PARTE 5*/

/*---------------------------------------------------------------------------------------------*/

//int insereNoIndice(Pagina *no, char* newKey, int PR, int P){
//    int pos = 0;
//    while (pos < 3) {
//        if (strlen(no->C[pos]) == 0){
//            strcpy(no->C[pos], newKey);
//            no->PR[pos] = PR;
//            break;
//        } else if (strcmp(newKey, no->C[pos]) < 0){
//            no->P[3] = no->P[2];
//            strcpy(no->C[2], no->C[1]);
//            no->PR[2] = no->PR[1];
//            if (pos == 0){
//                no->P[2] = no->P[1];
//                no->P[1] = no->P[0];
//                strcpy(no->C[1], no->C[0]);
//                no->PR[1] = no->PR[0];
//                strcpy(no->C[0], newKey);
//                no->PR[0] = PR;
//            } else {
//                strcpy(no->C[1], newKey);
//                no->PR[1] = PR;
//            }
//            break;
//        }
//        pos++;
//    }
//    no->nroChavesno++;
//    return pos;
//}
//
//int BuscaPai(FILE* indice, int RRN, char* chave, int aux){
//    Pagina no;
//    read_node(indice, &no, RRN); // Implemente a função de leitura do nó do disco
//    int i = 0;
//    while (i < no.nroChavesno && strcmp(chave, no.chaves[i]) > 0) {
//        i++;
//    }
//
//    if (i < no.nroChavesno && strcmp(chave, no.chaves[i]) == 0) {
//        return aux;
//    }
//    int cmp = strcmp(chave, no.C[i]);
//    if (strlen(no.C[i]) == 0){
//        cmp = -1;
//    }
//    if (no.P[i] != -1 && cmp < 0) {
//        BuscaPai(indice, no.P[i], chave, no.RRNdoNO);
//    } else if (no.P[i + 1] != -1) {
//        BuscaPai(indice, no.P[i+1], chave,  no.RRNdoNO);
//    }
//}
//
//btree_header InsereOverflow(FILE* indice, btree_header bHeader, Pagina* no, char* newKey, int PR, int P) {
//    // Verifica se ta no nó raiz, se estiver, splita e cria outro nó
//    int RRN_pai = BuscaPai(indice, bHeader.noRaiz, no->C[0], -1);
//    Pagina pai;
//    if (RRN_pai != -1){
//        read_node(indice, &pai, RRN_pai);
//    }
//
//    // Com o nó pai, ordenar o no a ser splitado e alocar a chave na posição [1] no pai
//    Pagina auxiliar = criaNode();
//    int pos = 0;
//    while (pos < no->nroChavesNo && strcmp(newKey, no->C[pos]) > 0) {
//        pos++;
//    }
//    /*char temp[256];
//    int PRaux;
//    int Paux;
//    for (int i = no->nroChavesNo; i > pos; i--) {
//        if (i != 3){
//            strcpy(no->C[i], no->C[i - 1]);
//            no->PR[i] = no->PR[i - 1];
//            no->P[i] = no->P[i - 1];
//        } else {
//            strcpy(temp, no->C[i - 1]);
//            PRaux = no->PR[i - 1];
//            Paux = no->P[i];
//        }
//    }
//    if (pos == 3){
//        strcpy(temp, newKey);
//        PRaux = PR;
//        Paux = P;
//    } else {
//        // Insere a nova chave na posição correta
//        strcpy(no->C[pos], newKey);
//        no->PR[pos] = PR;
//        no->P[pos + 1] = P;
//
//    }*/
//
//
//    char temp[4][256];
//    int PRtemp[4];
//    int Ptemp[5];
//
//
//    // Preenche os vetores temp com as chaves e seus respectivos PR e P
//    for (int i = 0; i < 4; i++) {
//        if (i != 3) {
//            strcpy(temp[i], no->C[i]);
//            PRtemp[i] = no->PR[i];
//            Ptemp[i] = no->P[i];
//        } else if (i == 3) {
//            strcpy(temp[i], newKey);
//            PRtemp[i] = PR;
//            Ptemp[i] = no->P[i];  // Defina o valor apropriado para o ponteiro
//            Ptemp[i + 1] = P;
//        }
//    }
//
//
//    for (int i = 3; i >= pos; i--) {
//        if (i != pos){
//            strcpy(temp[i], temp[i - 1]);
//            PRtemp[i] = PRtemp[i - 1];
//            Ptemp[i + 1] = Ptemp[i];
//        } else {
//            strcpy(temp[i], newKey);
//            PRtemp[i] =  PR;
//            Ptemp[i + 1] = P;
//        }
//    }
//    // Cria novo nó
//    auxiliar.P[0] = Ptemp[2];
//    auxiliar.PR[0] = PRtemp[2];
//    strcpy(auxiliar.C[0], temp[2]);
//    auxiliar.P[1] =  Ptemp[3];
//    auxiliar.PR[1] = PRtemp[3];
//    strcpy(auxiliar.C[1], temp[3]);
//    auxiliar.P[2] = Ptemp[4];
//    auxiliar.alturaNo = no->alturaNo;
//    auxiliar.nroChavesNo = 2;
//    auxiliar.RRNdoNO = bHeader.RRNproxNo;
//    bHeader.RRNproxNo++;
//    int ptr = no->PR[1];
//    for (int i = 0; i < 3; i++) {
//        no->P[i] = -1;
//        no->P[i + 1] = -1;
//        no->C[i][0] = '\0';
//        no->PR[i] = -1;
//    }
//
//    no->P[0] = Ptemp[0];
//    strcpy(no->C[0], temp[0]);
//    no->PR[0] = PRtemp[0];
//    no->P[1] = Ptemp[1];
//    no->nroChavesNo = 1;
//    if (no->alturaNo == 1){
//        for (int j = 0; j < 4; j++){
//            no->P[j] = -1;
//        }
//    }
//    // Fazer isso recursivamente até o nó tiver espaço ou for o nó raiz
//
//    if (pai.nroChavesNo == 3 || RRN_pai == -1){
//        if (RRN_pai != -1){
//            pai.alturaNo = no->alturaNo + 1;
//            bHeader = InsereOverflow(indice, bHeader, &pai, temp[1], PRtemp[1], auxiliar.RRNdoNO);
//        } else {
//            Pagina raiz = criaNode();
//            raiz.alturaNo = (no->alturaNo + 1);
//            raiz.nroChavesNo = 1;
//            raiz.RRNdoNO = bHeader.RRNproxNo;
//            bHeader.RRNproxNo++;
//            bHeader.noRaiz = raiz.RRNdoNO;
//            strcpy(raiz.C[0], temp[1]);
//            raiz.PR[0] = PRtemp[1];
//            raiz.P[0] = no->RRNdoNO;
//            raiz.P[1] = auxiliar.RRNdoNO;
//            escreve_node(indice, &raiz);
//        }
//
//    } else {
//        int ptr = insereNoIndice(&pai, temp[1], PRtemp[1], auxiliar.RRNdoNO);
//        pai.P[ptr + 1] = auxiliar.RRNdoNO;
//        escreve_node(indice, &pai);
//    }
//
//    // Apaga os registros do no, com excecao do na primeira posicao
//
//    escreve_node(indice, no);
//    escreve_node(indice, &auxiliar);
//
//    return bHeader;
//}



/*---------------------------------------------------------------------------------------------*/

/*Fim da parte 5*/




//LIVRO

//void InserePagina(Ponteiro P, Registro R, Ponteiro Pd)
//{
//    short nao_achou;
//    int k;
//    k = P -> n;
//    nao_achou = (k>0);
//    while (nao_achou)
//    {
//        if(R.Chave >= P -> r[k-1].Chave)
//            {
//                nao_achou = false;
//                break;
//            }
//        P -> r[k] = P -> r [k-1];
//        P -> p[k+1] = P -> p [k];
//        k--;
//        if(k < 1)
//        {
//            nao_achou = false;
//        }
//    }
//    P -> r[k] = R;
//    P -> p[k+1] = Pd;
//    P -> n++;
//}
//
//void Ins(Registro R, Ponteiro P, short *Cresceu, Registro *RegRetorno, Ponteiro *P_retorno)
//{
//    long i = 1;
//    long j;
//
//    Ponteiro P_temp;
//
//    if (P == NULL) {
//        *Cresceu = true;
//        (*RegRetorno) = R;
//        (*P_retorno) = NULL;
//        return;
//    }
//
//    while (i < P->n && Reg.Chave > P->r[i - 1].Chave) i++;
//    if (Reg.Chave == P->r[i - 1].Chave) {
//        printf("Erro: registro já presente");
//        *Cresceu = false;
//        return;
//    }
//
//
//    if (Reg.Chave < P->r[i - 1].Chave) i--;
//    Ins(Reg, P->p[i], Cresceu, RegRetorno, P_retorno)
//    if (!*Cresceu) return;
//    if (P->n<[mm]) //Pagina tem espaco
//    {
//        InsereNaPagina(P, *RegRetorno, *P_retorno);
//        *Cresceu = FALSE;
//        return;
//    }
////Overflow: Pagina tem que ser dividida
//
//    P_temp = (Ponteiro) malloc(sizeof(Pagina));
//    P_temp->n = 0;
//    P_temp->p[0] = null;
//    if (i < m + 1) {
//        InserePagina(P_temp, P->r[mm - 1], P->p[mm]);
//        P->n--;
//        InserePagina(P, *RegRetorno, *P_retorno);
//    } else InserePagina(P_temp, *RegRetorno, *P_retorno);
//    for (j = m + 2; j <= mm; j++) {
//        InserePagina(P_temp, P->r[j - 1], P->p[j]);
//        P->n = m;
//        P_temp->p[0] = P->P[m + 1];
//        *RegRetorno = P->r[m];
//        *P_retorno = P_temp;
//    }
//}
//
//void Insere (Registro Reg, Ponteiro *P)
//{
//    short Cresceu;
//    Registro RegRetorno;
//    Pagina *P_retorno, *P_temp;
//    Ins(Reg, *P,  &Cresceu, &RegRetorno, &P_retorno);
//    if (Cresceu) /*Arvore cresce na altura pela raiz*/
//    {
//        P_temp = (Pagina *) malloc (sizeof (Pagina));
//        P_temp -> n =1;
//        P_temp -> r[0] = RegRetorno;
//        P_temp -> p[1] = P_retorno;
//        P_temp -> p[0] = *P;
//        *P = P_temp;
//    }
//
//
//}
//



