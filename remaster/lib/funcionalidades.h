#ifndef FUNCS_H
#define FUNCS_H

#include "middleware.h"
#include "defines.h"

void func_criar_binario();
void func_ler_registros();
void func_ler_registro_filtrado();
void func_ler_registro_id();
void func_criar_indexador();
int func_busca(FILE *indice , char *busca);
#endif