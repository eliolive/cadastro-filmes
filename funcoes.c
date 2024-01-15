#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

Filme *criar_filme()
{
    Filme *f = (Filme *)malloc(sizeof(Filme));
    if (f != NULL)
    {
        f->informacoes = (Info *)malloc(sizeof(Info));
        if (f->informacoes == NULL)
        {
            free(f);
            return NULL;
        }
    }
    return f;
}
void free_filme(Filme *f)
{
    if (f != NULL)
    {
        free(f->informacoes);
        free(f);
    }
}
void imprimir_filme(Filme *f)
{
    if (f != NULL)
    {
        printf("%.2f R$ || %s (%s, %d) || %s %d", f->preco, f->nome, f->informacoes->genero, f->informacoes->faixaEtaria, f->informacoes->diretor, f->informacoes->ano);
    }
}
void set_nome(Filme *f, char *novo)
{
    if (f != NULL && novo != NULL)
    {
        strncpy(f->nome, novo, 100);
        f->nome[100] = '\0';
    }
}
void set_preco(Filme *f, float novo)
{
    if (f != NULL)
    {
        f->preco = novo;
    }
}
void set_diretor(Filme *f, char *novo)
{
    if (f != NULL && novo != NULL)
    {
        strncpy(f->informacoes->diretor, novo, 100);
        f->informacoes->diretor[100] = '\0';
    }
}
void set_genero(Filme *f, char *novo)
{
    if (f != NULL && novo != NULL)
    {
        strncpy(f->informacoes->genero, novo, 50);
        f->informacoes->genero[50] = '\0';
    }
}
void set_ano(Filme *f, int novo)
{
    if (f != NULL)
    {
        f->informacoes->ano = novo;
    }
}
void set_faixaetaria(Filme *f, int novo)
{
    if (f != NULL)
    {
        if (strstr(f->informacoes->genero, "Terror") != NULL && novo < 18)
        {
            printf("\nFaixa etaria deve ser maior que 18 para filmes do genero Terror.\n");
            printf("Insira uma nova faixa etaria:\n");
            scanf("%d", &novo);
            set_faixaetaria(f, novo);
        }
        else
        {
            f->informacoes->faixaEtaria = novo;
        }
    }
}

void cadastrar_titulo(Filme ***f, int *n)
{
    (*n)++;
    Filme **nova_tabela = (Filme **)realloc(*f, (*n) * sizeof(Filme *));
    if (nova_tabela == NULL)
    {
        printf("Memoria Insuficiente\n");
        exit(1);
    }
    *f = nova_tabela;

    Filme *novo_filme = criar_filme();
    if (novo_filme == NULL)
    {
        printf("Memoria Insuficiente\n");
        exit(1);
    }

    (*f)[(*n) - 1] = novo_filme;

    if (*n > 1)
    {
        Filme *ultimo_filme = (*f)[(*n) - 2];
        memcpy((*f)[(*n) - 1], ultimo_filme, sizeof(Filme));
    }
    printf("Nome: ");
    scanf(" %[^\n]", (*f)[(*n) - 1]->nome);
    printf("Preco: ");
    scanf("%f", &(*f)[(*n) - 1]->preco);

    (*f)[(*n) - 1]->informacoes = (Info *)malloc(sizeof(Info));
    if ((*f)[(*n) - 1]->informacoes == NULL)
    {
        free((*f)[(*n) - 1]);
        printf("Memoria Insuficiente\n");
        exit(1);
    }
    printf("Diretor: ");
    scanf(" %[^\n]", (*f)[(*n) - 1]->informacoes->diretor);
    printf("Genero: ");
    scanf(" %[^\n]", (*f)[(*n) - 1]->informacoes->genero);
    printf("Ano: ");
    scanf("%d", &(*f)[(*n) - 1]->informacoes->ano);
    printf("Faixa etaria: ");
    scanf("%d", &(*f)[(*n) - 1]->informacoes->faixaEtaria);
    set_faixaetaria((*f)[(*n) - 1], (*f)[(*n) - 1]->informacoes->faixaEtaria);
    printf("\n");
}
void atualizar_info_titulo(Filme **f, int n)
{
    printf("Escolha o indice do titulo a ser atualizado: ");
    int indice;
    scanf("%d", &indice);

    if (indice < 1 || indice > n)
    {
        printf("Indice invalido.\n");
        return;
    }

    Filme *filme_atualizar = f[indice - 1];

    printf("1 - RENOMEAR TITULO\n");
    printf("2 - ATUALIZAR PRECO\n");
    printf("3 - ATUALIZAR GENERO\n");

    int opcao_submenu;
    scanf("%d", &opcao_submenu);

    switch (opcao_submenu)
    {
    case 1:
        printf("Novo nome: ");
        scanf(" %[^\n]", filme_atualizar->nome);
        printf("Novo diretor: ");
        scanf(" %[^\n]", filme_atualizar->informacoes->diretor);
        break;
    case 2:
        printf("Novo preco: ");
        scanf("%f", &filme_atualizar->preco);
        break;
    case 3:
        printf("Novo genero: ");
        scanf(" %[^\n]", filme_atualizar->informacoes->genero);
        break;
    default:
        printf("Opcao invalida.\n");
        break;
    }
    imprimir_tabela(f, n);
}
void excluir_titulo(Filme ***f, int *n)
{
    printf("Escolha o indice do titulo a ser excluido: ");
    int indice_excluir;
    scanf("%d", &indice_excluir);

    if (indice_excluir < 1 || indice_excluir > *n)
    {
        printf("Indice invalido.\n");
        return;
    }
    // Libera a Memoria alocada para o título a ser excluído
    free((*f)[indice_excluir - 1]);
    // Move os títulos restantes para preencher o espaço vazio
    for (int i = indice_excluir - 1; i < *n - 1; i++)
    {
        (*f)[i] = (*f)[i + 1];
        (*f)[i]->informacoes = (*f)[i + 1]->informacoes; // Atualiza o ponteiro informacoes
    }
    // Reduz o tamanho da tabela
    (*n)--;
    // Realoca a tabela de filmes
    Filme **nova_tabela = (Filme **)realloc(*f, (*n) * sizeof(Filme *));
    if (nova_tabela == NULL)
    {
        printf("Memoria Insuficiente\n");
        exit(1);
    }
    *f = nova_tabela;

    printf("Titulo excluido com sucesso.\n");
    printf("\n");
}
void imprimir_tabela(Filme **f, int n)
{
    if (n > 0)
    {
        printf("-------------TABELA DE FILMES-------------\n\n");
        for (int i = 0; i < n; i++)
        {
            printf("%.4d -- ", i + 1);
            imprimir_filme(f[i]);
            printf("\n");
        }
    }
    else
    {
        printf("Nenhum filme cadastrado.\n");
    }
}
void menu_de_opcoes()
{
    printf("\nMENU DE OPCOES\n");
    printf("1 - CADASTRAR UM NOVO TITULO\n");
    printf("2 - ATUALIZAR INFO DE UM TITULO\n");
    printf("3 - EXCLUIR UM TITULO\n");
    printf("4 - FINALIZAR OPERACAO\n");
}