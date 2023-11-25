#include <stdio.h>
#include "aux_geral.h"
#include "aux_funcoes.h"

/*
Daniel Dias Silva Filho- 13677114
Henrique Parro - 11917987


*/
int main(int argv, char *argc[]){
    int escolha;
    char filename[32];
    scanf("%d", &escolha);

    switch (escolha){

        case 1:
            scanf("%s", filename);
            parte_1(filename);
        case 2:
            scanf("%s", filename);
            parte_2(filename);
        case 3:
            scanf("%s", filename);
            parte_3(filename);
        case 4:
            scanf("%s", filename);
            parte_4(filename);
        default:
            printf("Entrada indisponível.");
            break;
    }


}

