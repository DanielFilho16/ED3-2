#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TRUE 1
#define FALSE 0

#define TAM_TECNO 20
#define STR_DEFAULT_SIZE 255 
#define BTREE_REG_SIZE 205
#define MAX_KEYS 3

#define CHAR_TRASH '$'
#define EMPTY_KEY "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"

#define ERROR_FILE_OPEN 100

// Estrutura de Dados para os Registros de Dados Binário
typedef struct regs_cabecalho_type{
    char status;                // 1 byte
    int proxRRN;                // 4 bytes
    int nroTecnologias;         // 4 bytes
    int nroParesTecnologias;    // 4 bytes
} regs_cabecalho_type;          // total: 13 bytes

typedef struct regs_var_string{
    int tamanho;
    char string[TAM_TECNO];
} regs_var_string;

typedef struct{
    char removido;                      // 1 byte  
    int grupo;                          // 4 bytes
    int popularidade;                   // 4 bytes
    int peso;                           // 4 bytes
    regs_var_string tecnologiaOrigem;   // 4 + x bytes
    regs_var_string tecnologiaDestino;  // 4 + y bytes
} regs_tecnologia_type;                 // total: 21 + x + y bytes


// Estruturas Auxiliares para busca
typedef struct item_lista{
    char tecno1[STR_DEFAULT_SIZE];
    char tecno2[STR_DEFAULT_SIZE];
    struct item_lista * prox;
}item_lista_type;

typedef struct{
    item_lista_type * inicio;
    int qnt;
}lista_tecnos;

// Estrutura para busca
typedef struct{
    char campo[STR_DEFAULT_SIZE];
    char valorc[STR_DEFAULT_SIZE];
    int valord;
}search_item_type;

#endif