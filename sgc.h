#ifndef SGC_H
#define SGC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

// Definição da estrutura de Produto
typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Produto;


// Função para carregar o estoque de produtos a partir de um arquivo
int carregarEstoque(Produto *estoque) {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        return 0;
    }

    int quantidadeProdutos = 0;
    while (fscanf(arquivo, "%s %f %d", estoque[quantidadeProdutos].nome, &estoque[quantidadeProdutos].preco, &estoque[quantidadeProdutos].quantidade) == 3) {
        quantidadeProdutos++;
    }

    fclose(arquivo);
    return quantidadeProdutos;
}


// Função para adicionar um novo produto ao estoque
void adicionarProduto(Produto *estoque, int *quantidadeProdutos) {
    char nome[50];
    float preco;
    int quantidade;

    printf("Digite o nome do produto: ");
    scanf("%s", nome);
    printf("Digite o preco do produto: ");
    scanf("%f", &preco);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &quantidade);

    strcpy(estoque[*quantidadeProdutos].nome, nome);
    estoque[*quantidadeProdutos].preco = preco;
    estoque[*quantidadeProdutos].quantidade = quantidade;

    (*quantidadeProdutos)++;

    printf("Produto adicionado com sucesso!\n");
}


// Função para listar os produtos do estoque
void listarProdutos(Produto *estoque, int quantidadeProdutos) {
    printf("### Lista de Produtos ###\n");
    printf("Nome\t\tPreco\tQuantidade\n");
    for (int i = 0; i < quantidadeProdutos; i++) {
        printf("%s\t\t%.2f\t%d\n", estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
    }
}

// Função para adicionar um novo usuário ao sistema
void adicionarUsuario() {
    char nome[50];
    char senha[50];
    char nivel[50];

    printf("Digite o nome do usuário: ");
    scanf("%s", nome);
    printf("Digite a senha do usuário: ");
    scanf("%s", senha);
    printf("Digite o nível do usuário (admin/convencional): ");
    scanf("%s", nivel);

    FILE *arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fprintf(arquivo, "%s %s %s\n", nome, senha, nivel);
    fclose(arquivo);

    printf("Usuário adicionado com sucesso!\n");
}

// Função para excluir um usuário do sistema
void excluirUsuario() {
    char nome[50];
    printf("Digite o nome do usuário que deseja excluir: ");
    scanf("%s", nome);

    FILE *arquivoLeitura = fopen("usuarios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoLeitura == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    char linha[150];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivoLeitura)) {
        char nomeUsuario[50];
        char senha[50];
        char nivel[50];
        sscanf(linha, "%s %s %s", nomeUsuario, senha, nivel);
        if (strcmp(nomeUsuario, nome) != 0) {
            fprintf(arquivoTemp, "%s", linha);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivoLeitura);
    fclose(arquivoTemp);

    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");

    if (encontrado) {
        printf("Usuário excluído com sucesso!\n");
    } else {
        printf("Usuário não encontrado.\n");
    }
}

// Função para cancelar um pedido feito por um usuário
void cancelarPedido(Produto *estoque, int quantidadeProdutos) {
    char nomeProduto[50];
    int quantidade;

    printf("Digite o nome do produto do pedido que deseja cancelar: ");
    scanf("%s", nomeProduto);
    printf("Digite a quantidade do produto do pedido que deseja cancelar: ");
    scanf("%d", &quantidade);

    FILE *arquivoLeitura = fopen("pedidos.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoLeitura == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    char linha[150];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivoLeitura)) {
        char nomeProdutoPedido[50];
        int quantidadePedido;
        sscanf(linha, "%s %d", nomeProdutoPedido, &quantidadePedido);
        if (strcmp(nomeProdutoPedido, nomeProduto) != 0 || quantidadePedido != quantidade) {
            fprintf(arquivoTemp, "%s", linha);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivoLeitura);
    fclose(arquivoTemp);

    remove("pedidos.txt");
    rename("temp.txt", "pedidos.txt");

    if (encontrado) {
        printf("Pedido cancelado com sucesso!\n");
    } else {
        printf("Pedido não encontrado.\n");
    }
}

// Função para fazer um pedido de produto por um usuário convencional
void fazerPedido(Produto *estoque, int quantidadeProdutos) {
    char nomeProduto[50];
    int quantidadeDesejada;

    printf("Digite o nome do produto desejado: ");
    scanf("%s", nomeProduto);

    int indiceProduto = -1;
    for (int i = 0; i < quantidadeProdutos; i++) {
        if (strcmp(estoque[i].nome, nomeProduto) == 0) {
            indiceProduto = i;
            break;
        }
    }

    if (indiceProduto == -1) {
        printf("Produto não encontrado no estoque.\n");
        return;
    }

    printf("Digite a quantidade desejada: ");
    scanf("%d", &quantidadeDesejada);

    if (quantidadeDesejada > estoque[indiceProduto].quantidade) {
        printf("Quantidade solicitada excede a quantidade disponível em estoque.\n");
        return;
    }

    printf("Pedido realizado com sucesso: %s - %.2f (x%d)\n", estoque[indiceProduto].nome, estoque[indiceProduto].preco, quantidadeDesejada);
}


// Função para listar os pedidos feitos pelos usuários convencionais
void listarPedidos() {
    FILE *arquivo = fopen("pedidos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pedidos.\n");
        return;
    }

    printf("### Pedidos feitos pelos usuários convencionais ###\n");
    char nomeProduto[50];
    int quantidade;

    while (fscanf(arquivo, "%s %d", nomeProduto, &quantidade) == 2) {
        printf("%s - x%d\n", nomeProduto, quantidade);
    }

    fclose(arquivo);
}


#endif
