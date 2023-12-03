#ifndef CTRL_CSV_H
#define CTRL_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"

void csv_pular_cabecalho(FILE * csv);
regs_tecnologia_type csv_ler_registro(FILE * csv);
#endif