#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aux_geral.h"
#include "aux_funcoes.h"
#include "aux_arquivos.h"

/*
Daniel Dias Silva Filho- 13677114
Henrique Parro - 11917987


*/
int main(int argv, char *argc[])
{
    //basico da escolha
    int escolha;
    char filename[32];
    scanf("%d", &escolha);
    int repete = 0;
    Registro registro;
    Cabecalho cabecalho;


    //variaveis para a funcionalidade 6
    char nome_dados[20];
    char indice[20];
    char especifica[55];
    char info_busca[55];

    //variaveis para função 7
    char nome_dados2[20];
    char indice2[20];
    int n = 0;


    switch (escolha) {

        case 1:
            scanf("%s", filename);
            parte_1(filename);
            break;
        case 2:
            scanf("%s", filename);
            parte_2(filename);
            break;
        case 3:
            scanf("%s", filename);
            parte_3(filename, especifica, info_busca, &registro);
            break;
        case 4:
            scanf("%s", filename);
            //parte_4(filename, int RRN_P);
            break;
        case 5:
            printf("Funcionalidade 5");
            break;
        case 6:
        {
            scanf("%s%s%d", nome_dados, indice, &repete);

            FILE *info_dados = abre_arquivo(nome_dados, "rb");
            FILE *info_indice = abre_arquivo(indice, "rb");

            if (info_dados == NULL || info_indice == NULL || cabecalho.status == '0')
            {
                printf("Falha no processamento do arquivo.");
                break;
            }

            fseek(info_dados, 13, SEEK_SET);

            for (int i = 0; i < repete; i++)
            {
                scanf("%s", especifica);

                //se o valor for igual, pega o que esta ali
                if (strcmp(especifica, "nomeTecnologiaOrigem") == 0 || strcmp(especifica, "nomeTecnologiaDestino") == 0)
                {
                    scan_quote_string(info_busca);
                    fseek(info_dados, 13, SEEK_SET);
                    parte_3(nome_dados, especifica, info_busca, &registro); //arrumar
                } else if (strcmp(especifica, "grupo") == 0 || strcmp(especifica, "popularidade") == 0 ||
                           strcmp(especifica, "peso") == 0) {
                    scanf("%s", info_busca);
                    fseek(info_dados, 13, SEEK_SET);
                    parte_3(nome_dados, especifica, info_busca, &registro);

                } else if (strcmp(especifica, "nomeTecnologiaOrigemDestino") == 0)
                {
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
            break;
        }
        case 7 :
        {
            scanf("%s%s%d", nome_dados2, indice2, &n);

            FILE *info_dados2 = fopen(nome_dados2, "rb");
            FILE *info_indice2 = fopen(indice2, "rb");

            if (info_dados2 == NULL || info_indice2 == NULL)
            {
                printf("Falha no processamento do arquivo.");
                break;
            }

            fseek(info_dados2, 13, SEEK_SET);

            for (int i = 0; i < n; i++)
            {
                scanf("%s", especifica);

                //se o valor for igual, pega o que esta ali
                if (strcmp(especifica, "nomeTecnologiaOrigem") == 0 || strcmp(especifica, "nomeTecnologiaDestino") == 0)
                {
                    scan_quote_string(info_busca);
                    fseek(info_dados2, 13, SEEK_SET);
                    parte_3(nome_dados2, especifica, info_busca, &registro); //arrumar
                } else if (strcmp(especifica, "grupo") == 0 || strcmp(especifica, "popularidade") == 0 ||
                           strcmp(especifica, "peso") == 0) {
                    scanf("%s", info_busca);
                    fseek(info_dados2, 13, SEEK_SET);
                    parte_3(nome_dados2, especifica, info_busca, &registro);

                } else if (strcmp(especifica, "nomeTecnologiaOrigemDestino") == 0)
                {
                    scan_quote_string(info_busca);
                    fseek(info_dados2, 13, SEEK_SET);
                    fseek(info_indice2, 0, SEEK_SET);
                    //verifica se o arquivo é consistente
                    if (parte_7(info_dados2, info_indice2, info_busca) == -1)
                    {
                        break;
                    }
                }
            }
            fclose(info_dados2);
            fclose(info_indice2);
            break;
        }
    }


}

