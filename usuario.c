#include <stdio.h>
#include "sgc.h"

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
