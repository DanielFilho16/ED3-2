#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <ctype.h>
#include "controlador_csv.h"
#include "controlador_registro.h"
#include "defines.h"

FILE * middle_abrir_arquivo(char * path, char  * modo);
void middle_fechar_arquivo(FILE *arquivo);

regs_cabecalho_type middle_criar_cabecalho();

lista_tecnos middle_criar_lista_tecnos();
void middle_inserir_lista(lista_tecnos * lista, char * tecno1, char * tecno2);

int middle_buscar_tecno(lista_tecnos *lista, char * tecno);
int middle_buscar_tecno_par(lista_tecnos *lista, char * tecno1, char * tecno2);

int middle_is_numeric(char * campo);
int middle_verifica_busca(regs_tecnologia_type registro, search_item_type busca);

void middle_libera_lista(lista_tecnos *lista);

void middle_binarioNaTela(char *nomeArquivoBinario);
void middle_scan_quote_string(char *str);


void middle_print_cabecalho(regs_cabecalho_type cab);
void middle_print_registro(regs_tecnologia_type registro);

#endif