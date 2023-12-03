#ifndef CTRL_REGS_H
#define CTRL_REGS_H

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

void reg_seta_status(FILE * arquivo, char status);
void reg_ler_lixo(FILE *arquivo);
void reg_preencher_lixo(FILE *arquivo,int total);

regs_cabecalho_type regs_ler_cabecalho(FILE * arquivo);
regs_tecnologia_type regs_ler_registro(FILE * arquivo);

void regs_atualizar_cabecalho(FILE * arquivo, regs_cabecalho_type cabecalho);
void regs_escrever_registro(FILE * arquivo, regs_tecnologia_type registro, regs_cabecalho_type * cabecalho);

#endif