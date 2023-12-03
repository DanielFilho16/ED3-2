#include "../controlador_btree.h"


btree_cabecalho_type btree_criar_cabecalho_btree(){
    btree_cabecalho_type cab;

    cab.status = '0';
    cab.noRaiz = -1;
    cab.RRNproxNo = 0;
    for(int i=0;i<196;i++){
        cab.lixo[i] = CHAR_TRASH; 
    }

    return cab;    
}

btree_node_reg_type btree_criar_node_btree(){
    btree_node_reg_type node;
    node.nroChavesNo = 0;
    node.alturaNo = 0;
    node.RRNdoNo = 0;
    node.p1 = -1;
    node.p2 = -1;
    node.p3 = -1;
    node.p4 = -1;

    return node;
}

void btree_printar_node(btree_node_reg_type node){
    printf(">NroChaves: %d\n",node.nroChavesNo);
    printf(">Altura: %d\n",node.alturaNo);
    printf(">RRN: %d\n",node.RRNdoNo);
    printf(">C1: %s\n",node.c1);
    printf(">C2: %s\n",node.c2);
    printf(">C3: %s\n",node.c3);

    return;
}

void btree_printar_cab(btree_cabecalho_type cab){
    printf(">status: %c\n",cab.status);
    printf(">Raiz: %d\n",cab.noRaiz);
    printf(">RRN: %d\n",cab.RRNproxNo);
    printf(">lixo: %s\n",cab.lixo);
    return;
}

void btree_seta_status(FILE * arquivo, char status){
    /** desc: A função atualiza o status do arquivo, alternando-o entre 1 e 0.
    */

    if(status  == '0' || status == '1'){
        fseek(arquivo,0,SEEK_SET);
        fwrite(&status,1,sizeof(char),arquivo);
    }

    return;
}

btree_cabecalho_type btree_ler_cabecalho(FILE * arquivo){
    btree_cabecalho_type btree_cab;

    fseek(arquivo,0,SEEK_SET);
    fread(&btree_cab.status, sizeof(char), 1, arquivo);
    fread(&btree_cab.noRaiz, sizeof(int), 1, arquivo);
    fread(&btree_cab.RRNproxNo, sizeof(int), 1, arquivo);
    fread(&btree_cab.lixo, sizeof(char)*196, 1, arquivo);

    return  btree_cab;

}

void btree_atualizar_cabecalho(FILE * arquivo, btree_cabecalho_type btree_cab){

    fseek(arquivo,0,SEEK_SET);
    fwrite(&btree_cab.status, sizeof(char), 1, arquivo);
    fwrite(&btree_cab.noRaiz, sizeof(int), 1, arquivo);
    fwrite(&btree_cab.RRNproxNo, sizeof(int), 1, arquivo);
    fwrite(&btree_cab.lixo, sizeof(char)*196, 1, arquivo);

    return;

}

btree_node_reg_type btree_ler_node(FILE * arquivo, int rnn_node){

    btree_node_reg_type btree_node;

    fseek(arquivo,sizeof(char)*BTREE_REG_SIZE*(rnn_node+1),SEEK_SET);

    fread(&btree_node.nroChavesNo, sizeof(int), 1, arquivo);
    fread(&btree_node.alturaNo, sizeof(int), 1, arquivo);
    fread(&btree_node.RRNdoNo, sizeof(int), 1, arquivo);

    fread(&btree_node.p1, sizeof(int), 1, arquivo);
    fread(&btree_node.c1, sizeof(char)*55, 1, arquivo);
    fread(&btree_node.pr1, sizeof(int), 1, arquivo);

    fread(&btree_node.p2, sizeof(int), 1, arquivo);
    fread(&btree_node.c2, sizeof(char)*55, 1, arquivo);
    fread(&btree_node.pr2, sizeof(int), 1, arquivo);

    fread(&btree_node.p3, sizeof(int), 1, arquivo);
    fread(&btree_node.c3, sizeof(char)*55, 1, arquivo);
    fread(&btree_node.pr3, sizeof(int), 1, arquivo);

    fread(&btree_node.p4, sizeof(int), 1, arquivo);

    return btree_node;
}

void btree_atualizar_node(FILE * arquivo, btree_node_reg_type btree_node){
    long int curr_pos = ftell(arquivo);

    fseek(arquivo,BTREE_REG_SIZE*(btree_node.RRNdoNo+1),SEEK_SET);

    fwrite(&btree_node.nroChavesNo, sizeof(int), 1, arquivo);
    fwrite(&btree_node.alturaNo, sizeof(int), 1, arquivo);
    fwrite(&btree_node.RRNdoNo, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p1, sizeof(int), 1, arquivo);
    fwrite(&btree_node.c1, sizeof(char)*55, 1, arquivo);
    fwrite(&btree_node.pr1, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p2, sizeof(int), 1, arquivo);
    fwrite(&btree_node.c2, sizeof(char)*55, 1, arquivo);
    fwrite(&btree_node.pr2, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p3, sizeof(int), 1, arquivo);
    fwrite(&btree_node.c3, sizeof(char)*55, 1, arquivo);
    fwrite(&btree_node.pr3, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p4, sizeof(int), 1, arquivo);

    fseek(arquivo,curr_pos,SEEK_SET);

    return;
}

int btree_inserir_node(FILE * arquivo, btree_node_reg_type btree_node, btree_cabecalho_type * btree_cab){
    long int curr_pos = ftell(arquivo);
    int insertion_rnn = btree_cab->RRNproxNo;

    fseek(arquivo,BTREE_REG_SIZE*(insertion_rnn+1),SEEK_SET);
    fwrite(&btree_node.nroChavesNo, sizeof(int), 1, arquivo);
    fwrite(&btree_node.alturaNo, sizeof(int), 1, arquivo);
    fwrite(&insertion_rnn, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p1, sizeof(int), 1, arquivo);
    fwrite(&btree_node.c1, sizeof(char)*55, 1, arquivo);
    fwrite(&btree_node.pr1, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p2, sizeof(int), 1, arquivo);
    fwrite(&btree_node.c2, sizeof(char)*55, 1, arquivo);
    fwrite(&btree_node.pr2, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p3, sizeof(int), 1, arquivo);
    fwrite(&btree_node.c3, sizeof(char)*55, 1, arquivo);
    fwrite(&btree_node.pr3, sizeof(int), 1, arquivo);

    fwrite(&btree_node.p4, sizeof(int), 1, arquivo);

    btree_cab->RRNproxNo++;
    fseek(arquivo,curr_pos,SEEK_SET);
    btree_printar_cab(*btree_cab);

    return insertion_rnn;
}

void btree_inserir_chave(FILE * idx,btree_cabecalho_type * cab,char * nv_chave, int reg_rnn){
    // btree_printar_cab(*cab);
    if(cab->noRaiz == -1){
        btree_node_reg_type node = btree_criar_node_btree();

        node.nroChavesNo = 1;
        strcpy(node.c1,nv_chave);
        node.pr1 = reg_rnn;

        cab->noRaiz=0;
        btree_inserir_node(idx,node,cab);
        btree_atualizar_cabecalho(idx,*cab);
        // btree_printar_node(node);
        return;
    }

    // Carrega a raiz
    int node_id = btree_buscar_node(idx,cab->noRaiz,nv_chave);
    btree_node_reg_type curr_node = btree_ler_node(idx,node_id);

    if(curr_node.nroChavesNo < MAX_KEYS){
        btree_inserir_chave_node(&curr_node,nv_chave,reg_rnn);
        btree_atualizar_node(idx, curr_node);
        btree_split(idx,cab->noRaiz,cab);
        btree_atualizar_cabecalho(idx,*cab);
    }

    return;
}

btree_split(FILE * idx, int root_id, btree_cabecalho_type * cab){

    btree_node_reg_type root = btree_ler_node(idx,root_id);

    btree_split_rec(idx, root_id, root.p2,cab);
    btree_split_rec(idx, root_id, root.p1,cab);
    btree_split_rec(idx, root_id, root.p3,cab);
    btree_split_rec(idx, root_id, root.p4,cab);

    root = btree_ler_node(idx,root_id);

    if(root.nroChavesNo == 3){
        btree_node_reg_type new_root = btree_criar_node_btree();
        btree_node_reg_type new_child = btree_criar_node_btree();

        new_root.nroChavesNo = 1;
        new_child.nroChavesNo = 1;

        btree_key_cpy(new_root.c1,root.c2);
        new_root.pr1 = root.pr2;

        btree_key_cpy(new_child.c1,root.c3);
        new_child.pr1 = root.pr3;

        root.pr2 = -1;
        btree_key_cpy(root.c2,EMPTY_KEY);
        root.pr3 = -1;
        btree_key_cpy(root.c3,EMPTY_KEY);

        root.nroChavesNo = 1;

        int new_child_id = btree_inserir_node(idx,new_child,cab);

        new_root.p1 = root_id;
        new_root.p2 = new_child_id;

        int new_root_id = btree_inserir_node(idx,new_root,cab);

        btree_atualizar_node(idx,root);

        cab->noRaiz = new_root_id;
        btree_atualizar_altura_rec(idx,new_root.p1,1);
        btree_atualizar_altura_rec(idx,new_root.p2,1);
    }

}

void btree_split_rec(FILE * idx, int parent_id, int current_id, btree_cabecalho_type * cab){
    if(current_id == -1){
        return;
    }

    btree_node_reg_type current = btree_ler_node(idx,current_id);

    btree_split_rec(idx, current_id, current.p2,cab);
    btree_split_rec(idx, current_id, current.p1,cab);
    btree_split_rec(idx, current_id, current.p3,cab);
    btree_split_rec(idx, current_id, current.p4,cab);

    current = btree_ler_node(idx,current_id);

    if(current.nroChavesNo == 3){
        btree_node_reg_type new_child = btree_criar_node_btree();

        btree_key_cpy(new_child.c1,current.c3);
        new_child.pr1 = current.pr3;

        current.pr3 = -1;
        btree_key_cpy(current.c3,EMPTY_KEY);

        btree_node_reg_type parent =btree_ler_node(idx,parent_id);
        int pos_insert = btree_inserir_chave_node(&parent,current.c2,current.p2);

        current.pr2 = -1;
        btree_key_cpy(current.c2,EMPTY_KEY);

        current.nroChavesNo = 1;
        new_child.nroChavesNo = 1;

        int child_id = btree_inserir_node(idx,new_child,cab);
        
        if(pos_insert == 1){
            parent.p1 = current_id;
            parent.p2 = child_id;
        }else if(pos_insert == 2){
            parent.p2 = current_id;
            parent.p3 = child_id;
        }else{
            parent.p3 = current_id;
            parent.p4 = child_id;
        }

        btree_atualizar_node(idx,parent);
        btree_atualizar_node(idx,current);

    }
}

void btree_atualizar_altura_rec(FILE *idx, int pointer,int height){
    if(pointer == -1){
        return;
    }

    btree_node_reg_type node = btree_ler_node(idx,pointer);
    node.alturaNo = height;
    btree_atualizar_node(idx,node);
    btree_atualizar_altura_rec(idx,node.p1,height+1);
    btree_atualizar_altura_rec(idx,node.p2,height+1);
    btree_atualizar_altura_rec(idx,node.p3,height+1);
    btree_atualizar_altura_rec(idx,node.p4,height+1);
}

int btree_buscar_node(FILE * idx, int pnt_node,char * chave){
    btree_node_reg_type node = btree_ler_node(idx,pnt_node); 

    if(strcmp(chave,node.c1) < 0){
        if(node.p1 != -1){
            return btree_buscar_node(idx,node.p1,chave);
        }
    }else if(strcmp(chave,node.c2) < 0){
        if(node.p2 != -1){
            return btree_buscar_node(idx,node.p2,chave);
        }
    }else if(strcmp(chave,node.c3) < 0){
        if(node.p3 != -1){
            return btree_buscar_node(idx,node.p3,chave);
        }
    }
    if(node.p4 != -1){
        return btree_buscar_node(idx,node.p4,chave);
    }
    return pnt_node;
    
}

void btree_key_cpy(char * str_1, char * str_2){
    for(int i=0;i<55;i++){
         str_1[i] = str_2[i];  
    }
}

int btree_inserir_chave_node(btree_node_reg_type * node, char * chave,int reg_rnn){
    char aux_c1[55],aux_c2[55];
    int aux_n1,aux_n2;

    if(strcmp(chave,node->c1) < 0){
        btree_key_cpy(aux_c1,node->c1);
        aux_n1 = node->pr1;

        node->pr1 = reg_rnn;
        btree_key_cpy(node->c1,chave);

        btree_key_cpy(aux_c2,node->c2);
        aux_n2 = node->pr2;
        
        node->pr2 = aux_n1;
        btree_key_cpy(node->c2,aux_c1);
        

        node->pr3 = aux_n2;
        btree_key_cpy(node->c3,aux_c2);
        node->nroChavesNo++;
        return 1;
    }else{  
        if(node->nroChavesNo == 1){
            node->pr2 = reg_rnn;
            btree_key_cpy(node->c2,chave);
            node->nroChavesNo++;
            return 2;
        }else if(strcmp(chave,node->c2) < 0){
            btree_key_cpy(aux_c2,node->c2);
            aux_n2 = node->pr2;

            node->pr2 = reg_rnn;
            btree_key_cpy(node->c2,chave);

            node->pr3 = aux_n2;
            btree_key_cpy(node->c3,aux_c2);
            node->nroChavesNo++;
            return 2;
        }

        node->pr3 = reg_rnn;
        btree_key_cpy(node->c3,chave);
        return 3;
        
    }

    
    return;
}