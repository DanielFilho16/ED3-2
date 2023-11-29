#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aux_geral.h"
#include "aux_funcoes.h"

/*
Daniel Dias Silva Filho- 13677114
Henrique Parro - 11917987


*/
int main(int argv, char *argc[])
{
    int escolha;
    char filename[32];
    scanf("%d", &escolha);


    switch (escolha) {

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
            //parte_4(filename, int RRN_P);
        case 5:
            printf("Funcionalidade 5");
        case 6:
        {
            char nome_dados[20];
            char indice[20];
            char especifica[55];
            char info_busca[55];
            Registro registro;
            int repete = 0;

            scanf("%s%s%d", nome_dados, indice, &repete);

            FILE *info_dados = fopen(nome_dados, "rb");
            FILE *info_indice = fopen(indice, "rb");

            fseek(info_dados, 13, SEEK_SET);

            for (int i = 0; i < repete; i++)
            {
                scanf("%s", especifica);

                //se o valor for igual, pega o que esta ali
                if (strcmp(especifica, "nomeTecnologiaOrigem") == 0 || strcmp(especifica, "nomeTecnologiaDestino") == 0)
                {
                    scan_quote_string(info_busca);
                    fseek(info_dados, 13, SEEK_SET);
                    parte_3(info_dados, especifica, info_busca, &registro); //arrumar
                } else if (strcmp(especifica, "grupo") == 0 || strcmp(especifica, "popularidade") == 0 ||
                           strcmp(especifica, "peso") == 0) {
                    scanf("%s", info_busca);
                    fseek(info_dados, 13, SEEK_SET);
                    parte_3(info_dados, especifica, info_busca, &registro);

                } else if (strcmp(especifica, "nomeTecnologiaOrigemDestino") == 0) {
                    scan_quote_string(info_busca);
                    fseek(info_dados, 13, SEEK_SET);
                    fseek(info_indice, 0, SEEK_SET);
                    //verifica se o arquivo é consistente
                    if (parte_6(info_dados, info_indice, info_busca) == -1)
                    {
                        break;
                    }
                }
            }
            fclose(info_dados);
            fclose(info_indice);
        }
    }


}

