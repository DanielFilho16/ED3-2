#include "../middleware.h"

FILE * middle_abrir_arquivo(char * path, char * modo){
    FILE *fp;
    fp = fopen(path, modo);

    if (fp == NULL){
        printf("Falha no processamento do arquivo");
        exit(ERROR_FILE_OPEN);
    }

    return fp;
}

void middle_fechar_arquivo(FILE *arquivo){
   
   if(arquivo == NULL){
        printf(">[WARN] File pointer nulo.\n");
   }
    fclose(arquivo);
}

regs_cabecalho_type middle_criar_cabecalho(){
    regs_cabecalho_type cab;

    cab.status = '0';
    cab.proxRRN = 0;
    cab.nroTecnologias = 0;
    cab.nroParesTecnologias = 0;
    
    return cab;
}

lista_tecnos middle_criar_lista_tecnos(){
    lista_tecnos lista;
    lista.qnt = 0;
    lista.inicio = NULL;

    return lista;
}

void middle_inserir_lista(lista_tecnos * lista, char * tecno1, char * tecno2){

    item_lista_type * node = (item_lista_type * )malloc(sizeof(item_lista_type));

    strcpy(node->tecno1,tecno1);
    strcpy(node->tecno2,tecno2);
    node->prox = NULL;

    if(lista->inicio == NULL){
        lista->inicio = node;
        return;
    }
    
    item_lista_type *n = lista->inicio;

    while(n->prox != NULL){
        n = n->prox;
    }

    n->prox = node;
    return;
}

int middle_buscar_tecno(lista_tecnos *lista, char * tecno){
    
    item_lista_type * node = lista->inicio;

    while (node != NULL){
        if (!strcmp(node->tecno1, tecno)){
            return TRUE;
        }
        

        if (!strcmp(node->tecno2, tecno)){
             return TRUE;
        }
        

        node = node->prox;
    }
    return FALSE;
}

int middle_buscar_tecno_par(lista_tecnos *lista, char * tecno1, char * tecno2){
    item_lista_type * node = lista->inicio;

    while (node != NULL){
        if(!strcmp(node->tecno1,tecno1) && !strcmp(node->tecno2,tecno2)){
            return TRUE;
        }

        node = node->prox;
    }

    return FALSE;
}

int middle_is_numeric(char * campo){
    if(!strcmp(campo,"nomeTecnologiaOrigem") || !strcmp(campo,"nomeTecnologiaDestino")){
        return FALSE;
    }

    return TRUE;
}

int middle_verifica_busca(regs_tecnologia_type registro, search_item_type busca){
    if(!strcmp(busca.campo,"peso")){
        if(busca.valord == registro.peso){
            return TRUE;
        }
    }else if(!strcmp(busca.campo,"popularidade")){
        if(busca.valord == registro.popularidade){
            return TRUE;
        }
    }else if(!strcmp(busca.campo,"grupo")){
        if(busca.valord == registro.grupo){
            return TRUE;
        }
    }else if(!strcmp(busca.campo,"nomeTecnologiaOrigem")){

        if(!strcmp(busca.valorc,registro.tecnologiaOrigem.string)){
            return TRUE;
        }
        
    }else if(!strcmp(busca.campo,"nomeTecnologiaDestino")){
        if(!strcmp(busca.valorc,registro.tecnologiaDestino.string)){
            return TRUE;
        }
    }

    return FALSE;
}

void middle_binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
    *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *) malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for(i = 0; i < fl; i++) {
        cs += (unsigned long) mb[i];
    }
    printf("%lf\n", (cs / (double) 100));
    free(mb);
    fclose(fs);
}

void middle_libera_lista(lista_tecnos *lista){
    if(lista->inicio != NULL){
        item_lista_type * no;
        while(lista->inicio != NULL){
            no = lista->inicio;
            lista->inicio = no->prox;
            free(no);
        }
        free(lista);
    }
}

char * middle_gerar_chave(regs_tecnologia_type registro){
    char * chave = (char *) malloc(sizeof(char)*55);

    for(int i=0;i<registro.tecnologiaOrigem.tamanho;i++){
        chave[i] = registro.tecnologiaOrigem.string[i];
    }

    for(int i=registro.tecnologiaOrigem.tamanho;i < (registro.tecnologiaOrigem.tamanho + registro.tecnologiaDestino.tamanho);i++){
        chave[i] = registro.tecnologiaDestino.string[i-registro.tecnologiaOrigem.tamanho];
    }

    
    for(int i=(registro.tecnologiaOrigem.tamanho + registro.tecnologiaDestino.tamanho);i<55;i++){
        chave[i] = CHAR_TRASH;
    }
    return chave;
}

void middle_print_cabecalho(regs_cabecalho_type cab){
    printf(">status:%c\n",cab.status);
    printf(">proxRRN:%d\n",cab.proxRRN);
    printf(">tecnos:%d\n",cab.nroTecnologias);
    printf(">pares:%d\n",cab.nroParesTecnologias);
}

void middle_print_registro(regs_tecnologia_type registro){
    if(registro.removido == '0'){
        printf("%s, ",registro.tecnologiaOrigem.string);

        if(registro.grupo == -1){
            printf("NULO, ");
        }
        else printf("%d, ",registro.grupo);

        if(registro.popularidade == -1){
            printf("NULO, ");
        }
        else printf("%d, ",registro.popularidade);

        if(registro.tecnologiaDestino.tamanho == 0){
            printf("NULO, ");
        }else{
            printf("%s, ", registro.tecnologiaDestino.string);
        }

        if(registro.peso == -1){
            printf("NULO\n");
        }
        else printf("%d\n",registro.peso);
    }
}

void middle_scan_quote_string(char *str) {

    /*
    *	Use essa função para ler um campo string delimitado entre aspas (").
    *	Chame ela na hora que for ler tal campo. Por exemplo:
    *
    *	A entrada está da seguinte forma:
    *		nomeDoCampo "MARIA DA SILVA"
    *
    *	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
    *		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
    *		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
    *
    */

    char R;

    while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

    if(R == 'N' || R == 'n') { // campo NULO
        getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    } else if(R == '\"') {
        if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    } else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
        str[0] = R;
        scanf("%s", &str[1]);
    } else { // EOF
        strcpy(str, "");
    }
}


int recuperando(char *busca, int rrnAtual, FILE *indice) //EncontraRRNrec
{
    

//     typedef struct{
//     int nroChavesNo;          // 4 bytes
//     int alturaNo;             // 4 bytes
//     int RRNdoNo;              // 4 bytes

//     int p1;                 // 4 bytes
//     char c1[55];            // 55 bytes
//     int pr1;                // 4 bytes

//     int p2;                 // 4 bytes
//     char c2[55];            // 55 bytes
//     int pr2;                // 4 bytes

//     int p3;                 // 4 bytes
//     char c3[55];            // 55 bytes
//     int pr3;                // 4 bytes
     
//     int p4;   // 4 bytes
// }btree_node_reg_type; 


    fseek(indice, (rrnAtual + 1) * 205, SEEK_SET);
    btree_node_reg_type pagina;
    leitura_no(&pagina, indice);

    for (int i = 0; i <= 3; ++i)
    {
        int resultadoc1 = strcmp(busca, pagina.c1);
        if (pagina.c1)
        {
            if (pagina.p1 != -1)
            {
                return recuperando(busca, pagina.p1, indice);
            }
            else
            {
                return -1;
            }
        }
        if (resultadoc1 < 0 || pagina.c1[0] == '\0')
        {
            if (pagina.p1 != -1)
            {
                return recuperando(busca, pagina.p1, indice);
            }
            else
            {
                return -1;
            }
        }
        else if (resultadoc1 == 0)
        {
            return pagina.c1;
        }


        int resultadoc2 = strcmp(busca, pagina.c2);
        if (pagina.c2)
        {
            if (pagina.p2 != -1)
            {
                return recuperando(busca, pagina.p2, indice);
            }
            else
            {
                return -1;
            }
        }
        if (resultadoc2 < 0 || pagina.c2[0] == '\0')
        {
            if (pagina.p2 != -1)
            {
                return recuperando(busca, pagina.p2, indice);
            }
            else
            {
                return -1;
            }
        }
        else if (resultadoc2 == 0)
        {
            return pagina.c2;
        }




        int resultadoc3 = strcmp(busca, pagina.c3);
        if (pagina.c3)
        {
            if (pagina.p3 != -1)
            {
                return recuperando(busca, pagina.p3, indice);
            }
            else
            {
                return -1;
            }
        }
        if (resultadoc3 < 0 || pagina.c3[0] == '\0')
        {
            if (pagina.p1 != -1)
            {
                return recuperando(busca, pagina.p3, indice);
            }
            else
            {
                return -1;
            }
        }
        else if (resultadoc3 == 0)
        {
            return pagina.c3;
        }


    }

    if ( pagina.nroChavesNo != -1)
    {
        return recuperando(busca, pagina.nroChavesNo, indice);
    }
    else
    {
        return -1;
    }
}

int recupera(char *busca, int rrnDaRaiz,FILE *indice)
{
    return recuperando(busca, rrnDaRaiz, indice);
}

