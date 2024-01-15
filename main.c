#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(void){
    int n;
    printf("Entre com o tamanho da sua tabela: ");
    scanf("%d", &n);

    Filme** f = (Filme**)malloc(n * sizeof(Filme*));
    if(f == NULL){
        printf("Memoria Insuficiente\n");
        return 1;
    }
    for(int i = 0; i < n; i++){
        f[i] = criar_filme();
        if(f[i] == NULL){
            printf("Memoria Insuficiente\n");
            return 1;
        }
        printf("Nome: ");
        scanf(" %[^\n]", f[i]->nome);
        printf("Preco: ");
        scanf("%f", &f[i]->preco);
        printf("Diretor: ");
        scanf(" %[^\n]", f[i]->informacoes->diretor);
        printf("Genero: ");
        scanf(" %[^\n]", f[i]->informacoes->genero);
        printf("Ano: ");
        scanf("%d", &f[i]->informacoes->ano);
        printf("Faixa etaria: ");
        scanf("%d", &f[i]->informacoes->faixaEtaria);
        set_faixaetaria(f[i], f[i]->informacoes->faixaEtaria);
        printf("\n");
    }

    imprimir_tabela(f,n);

    int opcao = 0;

    while(opcao != 4){
        menu_de_opcoes();
        printf("\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastrar_titulo(&f, &n);
                break;
            case 2:
               atualizar_info_titulo(f, n);
                break;
            case 3:
                excluir_titulo(&f, &n);
                break;
            case 4:
                printf("Operacao finalizada.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
        imprimir_tabela(f,n);
    }
    for(int i = 0; i < n; i++){
        free_filme(f[i]);
    }
    free(f);

    return 0;
}