#ifndef UNTITLED_AUX_GERAL_H
#define UNTITLED_AUX_GERAL_H
#define TAM_REGISTRO 76
#define TAM_TECNOLOGIA 20
#define TAM_CABECALHO 13
#define TAM_PAG 512
#define TAM_ITEM 64
#include <stdio.h>

typedef struct Cabecalho{
    char status; //indica se o arquivo de dados esta consistente 0(setar 0 ao abrir para escrita) 1(apos escrever)
    int proxRRN; //iniciado com 0
    int nroTecnologias; //quantidade, inicial eh 0, apenas diferentes
    int nroParesTecnologias; //quantidade, inicial eh 0, apenas diferentes
} Cabecalho;
typedef struct {
    int tamanho;
    char string[TAM_TECNOLOGIA];
} StringVariavel;
typedef struct Registro{
    char removido;
    int grupo;
    int popularidade;
    int peso;
    StringVariavel tecnologiaOrigem;
    StringVariavel tecnologiaDestino;
    TipoChave Chave; // Livro
} Registro;

//Código Livro
typedef struct EnderecoTipo{
    long p;
    char b;
}EnderecoTipo;

typedef ItemTipo {
    Registro Reg;
    EnderecoTipo Esq, Dir;
}ItemTipo;

typedef ItemTipo PaginaTipo[TAM_ITEM]

typedef struct PaginaTipo{
    char tipo;
    union {
        PaginaTipoA Pa;
        PaginaTipoB Pb;
        PaginaTipoC Pc;
    }P;
}PaginaTipo;

typedef long TipoChave;
typedef struct Registro{
    TipoChave Chave;
}Registro;
typedef struct Pagina* Ponteiro;
typedef struct Pagina{
    char n;
    int nroChavesno;
    int RRNdoNo;
    int alturaN;
    int chaves[3];
    int ponteiros[4];
    int camposReferencia[2];
    Registro r[mm];
    Ponteiro p[mm+1];
}Pagina;

//Fim código livro


typedef struct No{
    Registro * reg;
    struct No * prox;
}No;
typedef struct Lista{
    No * inicio;
    int qnt;
}Lista;

struct Registro *novoRegistro();
struct Cabecalho *novoCabecalho();
struct Lista *novaLista();
void deletaRegistro(Registro *registro);
void deletaCabecalho(Cabecalho *cabecalho);
void liberaLista(Lista *lista);
int lerLinhaCSV(FILE *arquivoCSV, Registro *registro);
void escreverCabecalho(FILE *arquivoBinario,Cabecalho *cabecalho);
void registroNaLista(Registro *registro,Lista *lista);
int procura_tecnologia(Lista *lista,Registro *registro);
int procura_par(Lista *lista,Registro *registro);
void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
int n_de_registro(FILE *arquivoCSV); //Define o número do RRN
void leitura_tabela(FILE *arquivoCSV, Registro *Registro); //Faz a leitura de dados da struct
void exibe(Registro *Registro); //Exibe os dados organizadamente na tela
void printaRegistro(Registro *registro);



#endif
