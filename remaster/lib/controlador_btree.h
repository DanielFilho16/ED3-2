#ifndef CTRL_BTREE_H
#define CTRL_BTREE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "defines.h"
// Representação do Cabeçalho do arquivo da árvore
typedef struct{
    char status;            // 1 byte
    int noRaiz;             // 4 bytes
    int RRNproxNo;          // 4 bytes
    char lixo[196];         // 196 bytes
}btree_cabecalho_type;      // 205 bytes


// Representação do Nó do arquivo da árvore
typedef struct{
    int nroChavesNo;          // 4 bytes
    int alturaNo;             // 4 bytes
    int RRNdoNo;              // 4 bytes

    int p1;                 // 4 bytes
    char c1[55];            // 55 bytes
    int pr1;                // 4 bytes

    int p2;                 // 4 bytes
    char c2[55];            // 55 bytes
    int pr2;                // 4 bytes

    int p3;                 // 4 bytes
    char c3[55];            // 55 bytes
    int pr3;                // 4 bytes
     
    int p4;   // 4 bytes
}btree_node_reg_type;           // total: 205 bytes
#endif

btree_cabecalho_type btree_criar_cabecalho_btree();
btree_node_reg_type btree_criar_node_btree();

void btree_seta_status(FILE * arquivo, char status);
btree_cabecalho_type btree_ler_cabecalho(FILE * arquivo);
void btree_atualizar_cabecalho(FILE * arquivo, btree_cabecalho_type btree_cab);
btree_node_reg_type btree_ler_node(FILE * arquivo, int rnn_node);
int btree_inserir_node(FILE * arquivo, btree_node_reg_type btree_node, btree_cabecalho_type * btree_cab);
void btree_inserir_chave(FILE * idx,btree_cabecalho_type * cab,char * nv_chave, int reg_rnn);
int btree_inserir_chave_node(btree_node_reg_type * node, char * chave, int reg_tnn);
void btree_printar_node(btree_node_reg_type node);
void btree_key_cpy(char * str_1, char * str_2);