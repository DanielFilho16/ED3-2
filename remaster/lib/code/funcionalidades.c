#include "../funcionalidades.h"


void func_criar_binario(){

    // Leitura e abertura dos arquivos;
    char path_csv[STR_DEFAULT_SIZE], path_bin[STR_DEFAULT_SIZE];

    scanf("%s %s",path_csv,path_bin);

    FILE* csv = middle_abrir_arquivo(path_csv,"r");
    FILE* bin = middle_abrir_arquivo(path_bin,"wb");
    
    

    regs_cabecalho_type cab = middle_criar_cabecalho();
    regs_atualizar_cabecalho(bin,cab);

    lista_tecnos lista = middle_criar_lista_tecnos();
    
    regs_tecnologia_type regs_temp;
    csv_pular_cabecalho(csv);

    while(!feof(csv)){
        regs_temp = csv_ler_registro(csv);

        middle_print_registro(regs_temp);

        regs_escrever_registro(bin,regs_temp,&cab);

        if(!middle_buscar_tecno(&lista,regs_temp.tecnologiaOrigem.string)){
            cab.nroTecnologias++;
        }

        if(regs_temp.tecnologiaDestino.tamanho > 0){
            if(!middle_buscar_tecno(&lista,regs_temp.tecnologiaDestino.string)){
                cab.nroTecnologias++;
            }

            if(!middle_buscar_tecno_par(&lista, regs_temp.tecnologiaOrigem.string, regs_temp.tecnologiaDestino.string)){
                cab.nroParesTecnologias++;
                middle_inserir_lista(&lista,regs_temp.tecnologiaOrigem.string, regs_temp.tecnologiaDestino.string);
            }
        }
    }

    // middle_print_cabecalho(cab);
    regs_atualizar_cabecalho(bin,cab);
    reg_seta_status(bin,'1');

    middle_fechar_arquivo(csv);
    middle_fechar_arquivo(bin);

    middle_binarioNaTela(path_bin);
};

void func_ler_registros(){
    char path_bin[STR_DEFAULT_SIZE];

    scanf("%s",path_bin);

    FILE* bin = middle_abrir_arquivo(path_bin,"rb");

    regs_cabecalho_type cab = regs_ler_cabecalho(bin);

    regs_tecnologia_type regs_temp;
    while(!feof(bin)){
        regs_temp = regs_ler_registro(bin);
        middle_print_registro(regs_temp);
        
    }

    middle_fechar_arquivo(bin);
}

void func_ler_registro_filtrado(){
    char path_bin[STR_DEFAULT_SIZE];
    scanf("%s",path_bin);

    FILE* bin = middle_abrir_arquivo(path_bin,"rb");
    
    int n;
    scanf("%d",&n);

    search_item_type busca;

    regs_cabecalho_type cab = regs_ler_cabecalho(bin);

    for(int i=0;i<n;i++){

        scanf("%s",busca.campo);
        if(middle_is_numeric(busca.campo)){
            scanf("%d",&busca.valord);
        }else{
            middle_scan_quote_string(busca.valorc);
        }
        
        regs_tecnologia_type regs_temp;
        while(!feof(bin)){
            regs_temp = regs_ler_registro(bin);
            
            if(middle_verifica_busca(regs_temp,busca)){
                middle_print_registro(regs_temp);
            }
            
        }

        fseek(bin,13,SEEK_SET);
    }
    
    

    middle_fechar_arquivo(bin);
}

void func_ler_registro_id(){

    char path_bin[STR_DEFAULT_SIZE];
    scanf("%s",path_bin);
    
    int rrn;
    scanf("%d",&rrn);

    FILE* bin = middle_abrir_arquivo(path_bin,"rb");
    regs_cabecalho_type cab = regs_ler_cabecalho(bin);

    regs_tecnologia_type regs_temp;
    fseek(bin,76*rrn,SEEK_CUR);

    regs_temp = regs_ler_registro(bin);
    middle_print_registro(regs_temp);
    
    middle_fechar_arquivo(bin);
}



