//Arquivo de cabeçalho.h para o módulo de funções Videoteca
//Todas as funções devem ser implementadas independente se vão ser utilizadas ou não
//estrutura para um Filme
#ifndef FUNCOES_H
#define FUNCOES_H

// Abstração da estrutura Info
typedef struct info {
    char diretor[101]; // 101 caracteres + 1 para fim de string
    char genero[51];  // 50 caracteres + 1 para fim de string
    int ano;
    int faixaEtaria;  // Use 0 para classificação livre
} Info;

// Estrutura para um Filme
typedef struct filme {
    char nome[101]; // 100 caracteres + 1 para fim de string
    float preco;    // Até duas casas decimais
    Info* informacoes;
} Filme;

// Função que cria e retorna um ponteiro simples para o tipo Filme
Filme* criar_filme();

// Função que exclui um filme e libera memória
void free_filme(Filme* f);

// Função que imprime informações de um filme
void imprimir_filme(Filme* f);

// Função que imprime a tabela atualizada dos filmes cadastrados
// código -- preço R$ ## nome (gênero, faixa etária) ## diretor ano
// 0001 -- 25.50 R$ ## The Godfather Part II (Crime/Drama, 16) ## Francis Ford Coppola 1974
void imprimir_tabela(Filme** f, int n);

// Função que da início ao fluxo
void menu_de_opcoes();

// Funções de manipulação
// Função que acessa e modifica o nome de um filme
void set_nome(Filme* f, char* novo);

// Função que acessa e modifica o preço de um filme
void set_preco(Filme* f, float novo);

// Função que acessa e renomeia um diretor de um filme
void set_diretor(Filme* f, char* novo);

// Função que acessa e renomeia os gêneros de um filme
void set_genero(Filme* f, char* novo);

// Função que acessa e modifica o ano de um filme
void set_ano(Filme* f, int novo);

// Função que acessa e modifica a faixa etária de um filme
void set_faixaetaria(Filme* f, int novo );

// Função que cadastra um novo título
void cadastrar_titulo(Filme*** f, int* n);

// Função que atualiza informações de um título
void atualizar_info_titulo(Filme** f, int n);

// Função que exclui um título
void excluir_titulo(Filme*** f, int* n);

#endif  // CABECALHO_H