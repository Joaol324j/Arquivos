#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgc.h"

#define MAX_PRODUTOS 100

int main() {
    Produto estoque[MAX_PRODUTOS];
    int quantidadeProdutos = carregarEstoque(estoque);

    int opcao;
    char senha[50];

    printf("Digite a senha de administrador: ");
    fgets(senha, 50, stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remover a quebra de linha do final

    // Autenticação do administrador
    if (strcmp(senha, "1234") == 0) {
        // Menu para o administrador
        do {
            printf("\n### Menu Administrador ###\n");
            printf("1. Adicionar Produto\n");
            printf("2. Listar Produtos\n");
            printf("3. Adicionar Usuário\n");
            printf("4. Excluir Usuário\n");
            printf("5. Cancelar Pedido\n");
            printf("6. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            getchar(); // Limpar o buffer do teclado

            switch (opcao) {
                case 1:
                    adicionarProduto(estoque, &quantidadeProdutos);
                    break;
                case 2:
                    listarProdutos(estoque, quantidadeProdutos);
                    break;
                case 3:
                    adicionarUsuario();
                    break;
                case 4:
                    excluirUsuario();
                    break;
                case 5:
                    cancelarPedido(estoque, quantidadeProdutos);
                    break;
                case 6:
                    printf("Saindo\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        } while (opcao != 6);
    } else {
        printf("Senha de administrador incorreta. Acesso negado.\n");
    }

    return 0;
}
