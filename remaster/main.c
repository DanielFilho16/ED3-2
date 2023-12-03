#include<stdio.h>
#include "lib/funcionalidades.h"

int main(int argc, char * argv[]){
    int func_code;
    scanf("%d",&func_code);

    switch(func_code){
        case 1:
            func_criar_binario();
            break;
        case 2:
            func_ler_registros();
            break;
        case 3:
            func_ler_registro_filtrado();
            break;
        case 4:
            func_ler_registro_id();
            break;
        case 5:
            func_criar_indexador();
        default:
            printf("Funcionalidade invalida.\n");
            exit(0);
    }
}