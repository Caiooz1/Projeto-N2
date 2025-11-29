/*--------------------------------------------------------*
*     Disciplina: Programaçao Estruturada e Modular       *
*     Prof. Carlos Verissimo                              *
*---------------------------------------------------------*
*     Objetivo do Programa: Projeto da P2                 *
*     Tema: Estoque de Loja (Grupo 7)                     *  
*     Data - 18/11/2025                                   * 
*     Autores - Rafael Kenzo e Caio Zatti                 *
*---------------------------------------------------------*/


#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100   // define o limite máximo de produtos permitidos no vetor
#define TAM_NOME 50        // define o tamanho máximo da string do nome
#define TAM_CATEG 30       // define o tamanho máximo da string da categoria

/* ---------- STRUCT DO PRODUTO ---------- */
typedef struct {
    int codigo;                         // armazena o código numérico do produto
    char nome[TAM_NOME];                // armazena o nome do produto como vetor de chars
    char categoria[TAM_CATEG];          // armazena a categoria do produto
    float preco;                        // guarda o preço unitário
    int quantidade;                     // quantidade atual em estoque
    int quantidadeInicial;              // guarda o valor inicial do estoque para cálculos posteriores
} Produto;

/* ---------- PROTÓTIPOS DAS FUNÇÕES ---------- */
void cadastrarProduto(Produto produtos[], int *n);   // função para adicionar novo produto no vetor
void listarProdutos(Produto produtos[], int n);      // função que exibe todos os produtos cadastrados
void entrada(Produto produtos[], int n);             // registra entrada de estoque
void saida(Produto produtos[], int n);               // registra saída de estoque
void buscar(Produto produtos[], int n);              // busca produto pelo código
void relatorio(Produto produtos[], int n);           // relatório dos produtos com estoque abaixo de 30%

/* ---------- FUNÇÃO PRINCIPAL ---------- */
int main() {
    Produto produtos[MAX_PRODUTOS];   // cria o vetor que armazenará até 100 produtos
    int n = 0;                        // controla quantos produtos foram cadastrados
    int opcao;                        // armazena a opção digitada no menu

    do {                               // inicia o loop do menu que se repete até o usuário sair
        printf("\n=== MENU ===\n");     // exibe o menu na tela
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Registrar entrada\n");
        printf("4 - Registrar saída\n");
        printf("5 - Buscar produto\n");
        printf("6 - Relatório: estoque abaixo de 30%%\n");
        printf("0 - Sair\n");
        printf("Opção: ");

        scanf("%d", &opcao);        // lê a opção que o usuário escolheu
        getchar();                   // consome o ENTER deixado no buffer

        switch (opcao) {             // verifica qual opção foi escolhida
            case 1: cadastrarProduto(produtos, &n); break;   // chama função para cadastrar produto
            case 2: listarProdutos(produtos, n); break;      // chama função para listar produtos
            case 3: entrada(produtos, n); break;             // chama função de entrada de estoque
            case 4: saida(produtos, n); break;               // chama função de saída de estoque
            case 5: buscar(produtos, n); break;              // chama função de busca
            case 6: relatorio(produtos, n); break;           // chama relatório
            case 0: printf("Saindo...\n"); break;           // finaliza o programa
            default: printf("Opção inválida!\n");          // trata opção inexistente
        }

    } while (opcao != 0);            // repete o menu enquanto o usuário não escolher sair

    return 0;                        // fim do programa principal
}

/* ---------- CADASTRAR PRODUTO ---------- */
void cadastrarProduto(Produto produtos[], int *n) {
    Produto p;                         // cria variável temporária para receber os dados

    printf("\nCódigo: ");
    scanf("%d", &p.codigo);           // lê o código digitado
    getchar();                         // limpa o ENTER

    printf("Nome: ");
    fgets(p.nome, TAM_NOME, stdin);    // lê o nome do produto
    p.nome[strcspn(p.nome, "\n")] = 0;   // remove o ENTER final

    printf("Categoria: ");
    fgets(p.categoria, TAM_CATEG, stdin);   // lê a categoria
    p.categoria[strcspn(p.categoria, "\n")] = 0;   // remove ENTER

    printf("Preço: ");
    scanf("%f", &p.preco);            // lê o preço unitário

    printf("Quantidade inicial: ");
    scanf("%d", &p.quantidade);       // lê o estoque inicial

    p.quantidadeInicial = p.quantidade;   // salva o estoque inicial

    produtos[*n] = p;                  // insere o produto no vetor
    (*n)++;                             // incrementa a quantidade total

    printf("Produto cadastrado!\n");
}

/* ---------- LISTAR PRODUTOS ---------- */
void listarProdutos(Produto produtos[], int n) {
    printf("\n=== LISTA DE PRODUTOS ===\n");

    for (int i = 0; i < n; i++) {     // percorre cada produto cadastrado
        printf("\nCódigo: %d\nNome: %s\nCategoria: %s\nPreço: R$%.2f\nQtd Atual: %d\nQtd Inicial: %d\n",
            produtos[i].codigo,      // exibe o código do produto
            produtos[i].nome,        // exibe o nome
            produtos[i].categoria,   // exibe a categoria
            produtos[i].preco,       // exibe o preço
            produtos[i].quantidade,  // exibe a quantidade atual
            produtos[i].quantidadeInicial);   // exibe o estoque inicial
    }
}

/* ---------- REGISTRAR ENTRADA ---------- */
void entrada(Produto produtos[], int n) {
    int codigo, qtd;

    printf("Código do produto: ");
    scanf("%d", &codigo);           // lê o código digitado para localizar produto

    for (int i = 0; i < n; i++) {    // percorre o vetor em busca do código
        if (produtos[i].codigo == codigo) {   // verifica se o produto existe

            printf("Quantidade a adicionar: ");
            scanf("%d", &qtd);              // lê a quantidade adicionada

            produtos[i].quantidade += qtd;   // soma no estoque atual

            printf("Entrada registrada!\n");
            return;                          // encerra a função
        }
    }

    printf("Produto não encontrado!\n");    // caso o código não exista
}

/* ---------- REGISTRAR SAÍDA ---------- */
void saida(Produto produtos[], int n) {
    int codigo, qtd;

    printf("Código do produto: ");
    scanf("%d", &codigo);           // lê o código do produto

    for (int i = 0; i < n; i++) {    // procura no vetor
        if (produtos[i].codigo == codigo) {   // encontrou produto

            printf("Quantidade a remover: ");
            scanf("%d", &qtd);              // lê a quantidade que deseja retirar

            if (produtos[i].quantidade < qtd) {   // verifica se tem estoque suficiente
                printf("Estoque insuficiente!\n");
                return;
            }

            produtos[i].quantidade -= qtd;   // atualiza o estoque após retirada

            printf("Saída registrada!\n");
            return;                          // encerra
        }
    }

    printf("Produto não encontrado!\n");
}

/* ---------- BUSCAR PRODUTO ---------- */
void buscar(Produto produtos[], int n) {
    int codigo;

    printf("Digite o código: ");
    scanf("%d", &codigo);           // lê código informado

    for (int i = 0; i < n; i++) {    // procura produto no vetor
        if (produtos[i].codigo == codigo) {   // encontrou produto
            printf("\nCódigo: %d\nNome: %s\nCategoria: %s\nPreço: %.2f\nQtd Atual: %d\nQtd Inicial: %d\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].categoria,
                produtos[i].preco,
                produtos[i].quantidade,
                produtos[i].quantidadeInicial);
            return;                  // encerra após exibir
        }
    }

    printf("Produto não encontrado!\n");     // caso não exista
}

/* ---------- RELATÓRIO ABAIXO DE 30% ---------- */
void relatorio(Produto produtos[], int n) {
    printf("\n=== PRODUTOS ABAIXO DE 30%% DO ESTOQUE INICIAL ===\n");

    for (int i = 0; i < n; i++) {        // percorre todos os produtos

        float limite = produtos[i].quantidadeInicial * 0.30;   // calcula 30% do estoque inicial

        if (produtos[i].quantidade <= limite) {   // verifica se está no limite crítico

            printf("\nCódigo: %d\nNome: %s\nQtd Atual: %d\nLimite 30%%: %.0f\n",
                produtos[i].codigo,               // exibe o código
                produtos[i].nome,                 // exibe o nome
                produtos[i].quantidade,           // exibe quantidade atual
                limite);                           // exibe o limite calculado
        }
    }
}