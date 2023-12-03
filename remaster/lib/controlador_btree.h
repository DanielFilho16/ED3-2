#ifndef CTRL_BTREE_H
#define CTRL_BTREE_H


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
}btree_node_type;           // total: 205 bytes

#endif