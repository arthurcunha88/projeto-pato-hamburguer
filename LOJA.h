#ifndef LOJA_H
#define LOJA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "LISTADE.h"
#include "ESTOQUE.h"

void clearScreen();
void pauseGame();
void limparBufferEntrada();

// Estrutura da loja, que usa listade para armazenar dinamicamente os itens disponiveis
typedef struct {
    char nome[50];
    float precoCompra;
    float precoVenda;
} tp_itemLoja;

typedef struct {
    tp_listade *itens;
} tp_loja;

// Inicializa a loja
tp_loja *inicializarLoja(ingrediente estoque[], int totalIngredientes) {
    tp_loja *loja = (tp_loja*) malloc(sizeof(tp_loja));
    loja->itens = inicializaListade();

    for (int i = 0; i < totalIngredientes; i++) {
        tp_itemLoja *novo = (tp_itemLoja*) malloc(sizeof(tp_itemLoja));
        strcpy(novo->nome, estoque[i].nome);
        novo->precoCompra = estoque[i].precoCompra;      // preco que o jogador paga para comprar
        novo->precoVenda = estoque[i].precoVenda; // preco que o jogador recebe ao vender
        insereListadeNoFim(loja->itens, novo);
    }

    return loja;
}


// Exibe os produtos disponiveis
void exibirItensLoja(tp_loja *loja) {
    
    clearScreen();
    
    if (listadeVazia(loja->itens)) {
        printf(RED "\nNenhum produto disponivel na loja.\n" RESET);
        pauseGame();
        return;
    }

    printf(BRIGHT_CYAN "\n============== ITENS DA LOJA PATONICA ==============\n" RESET);
    printf(BRIGHT_WHITE "Nome                 | Preco Compra | Preco Venda\n" RESET);
    printf(BRIGHT_MAGENTA "----------------------------------------------------\n" RESET);

    tp_no *atu = loja->itens->ini;
    while (atu != NULL) {
        tp_itemLoja *item = (tp_itemLoja*)(intptr_t) atu->info;
        printf(
            CYAN "%-20s" RESET " | "
            GREEN "%12.2f" RESET " | "
            YELLOW "%11.2f\n" RESET,
            item->nome,
            item->precoCompra,
            item->precoVenda
        );

        atu = atu->prox;
    }
    printf(BRIGHT_MAGENTA "----------------------------------------------------\n" RESET);
}

// Busca produto na loja
tp_itemLoja *buscarItemLoja(tp_loja *loja, char nome[]) {
    tp_no *atu = loja->itens->ini;
    while (atu != NULL) {
        tp_itemLoja *item = (tp_itemLoja*)(intptr_t) atu->info;
        if (strcmp(item->nome, nome) == 0) return item;
        atu = atu->prox;
    }
    return NULL;
}

// Compra ingrediente: adiciona ao estoque e desconta saldo
void comprarIngrediente(tp_loja *loja, ingrediente estoque[], float *saldo) {
    
    char nome[50];
    int qtd = 0;
    
    while(1){
        
    exibirItensLoja(loja);
    
    printf(YELLOW "\nDigite -1 para voltar ao menu da loja" RESET);
    printf(BRIGHT_WHITE"\nDigite o nome do ingrediente que deseja comprar (ex: Pao; Carne; Alface; ...): "RESET);
    
    scanf(" %[^\n]", nome);
    limparBufferEntrada();
    
    if (strcmp(nome, "-1") == 0) {
        printf(GREEN "\n\nSaindo da compra...\n"RESET);
        pauseGame();
        break; // sai do loop
    }
    
    tp_itemLoja *item = buscarItemLoja(loja, nome);
    if (!item) {
        printf(RED"\n\nIngrediente nao encontrado na loja.\n"RESET);
        
        pauseGame();
        continue;
    }
    
    while(qtd <= 0) {
        printf("\nQuantidade a comprar: ");
        scanf("%d", &qtd);
        limparBufferEntrada();
        
        if (qtd <= 0) {
            printf(RED "\nQuantidade selecionada invalida. Pressione ENTER para selecionar novamente."RESET); 
            limparBufferEntrada();
        }
    }

    float custo = item->precoCompra * qtd;
    if (*saldo < custo) {
        printf(RED"\nSaldo insuficiente para efetuar a compra.\n"RESET);
        pauseGame();
        clearScreen();
        qtd = 0;
        continue;
    }

    adicionarEstoque(estoque, nome, qtd);
    *saldo -= custo;
    printf(GREEN"\n\nCompra realizada! Novo saldo: R$%.2f\n"RESET, *saldo);
    pauseGame();
    clearScreen();
    qtd = 0;
    }
}

// Vende ingrediente: remove do estoque e soma saldo
void venderIngrediente(tp_loja *loja, ingrediente estoque[], float *saldo) {
    
    char nome[50];
    int qtd;
    
    clearScreen();
    
    while(1){
        
    exibirEstoque(estoque);

    
    printf(YELLOW"\nDigite -1 para voltar ao menu da loja"RESET);
    printf(BRIGHT_WHITE"\nDigite o nome do ingrediente que deseja vender(ex: Pao; Carne; Alface; ...):  "RESET);
    
    scanf(" %[^\n]", nome);
    limparBufferEntrada();
    
    if (strcmp(nome, "-1") == 0) {
        printf(GREEN "\n\nSaindo da venda...\n"RESET);
        pauseGame();
        break; // break para sair do loop
    }
    
    tp_itemLoja *item = buscarItemLoja(loja, nome);
    if (!item) {
        printf(RED "\nA loja nao compra este ingrediente.\n"RESET);
        pauseGame();
        clearScreen();
        continue;
    }

    printf("\nQuantidade a vender: ");
    scanf("%d", &qtd);
    limparBufferEntrada();

    if (!retirarDoEstoque(estoque, nome, qtd)) {
        pauseGame();
        clearScreen();
        continue;
    }

    float ganho = item->precoVenda * qtd;
    *saldo += ganho;
    printf(GREEN "\nVenda realizada! Novo saldo: R$%.2f\n"RESET, *saldo);
    pauseGame();
    clearScreen();
    }
}

// Menu da loja
void abrirLoja(tp_loja *loja, ingrediente estoque[], float *saldo) {
    int opcao;
    do {
        clearScreen();
        printf(BRIGHT_CYAN "\n=============== LOJA PATONICA ===============\n" RESET);
        printf(BRIGHT_GREEN "Saldo atual: R$%.2f\n" RESET, *saldo);

        printf(
            BRIGHT_WHITE
            "1 - Exibir itens\n"
            "2 - Comprar ingredientes\n"
            "3 - Vender ingredientes\n"
            "0 - Voltar ao menu do jogo\n"
            RESET
        );

        printf(BRIGHT_CYAN "=============================================\n" RESET);
        printf(BRIGHT_YELLOW "Escolha uma opcao: " RESET);
        int resultadoScan = scanf("%d", &opcao); //resultadoscan eh pra tratar como opcao invalida no switch case
        
        limparBufferEntrada();

        if (resultadoScan == 0) opcao = -1;

        switch (opcao) {
            case 1: exibirItensLoja(loja); pauseGame(); break;
            case 2: comprarIngrediente(loja, estoque, saldo); break;
            case 3: venderIngrediente(loja, estoque, saldo); break;
            case 0: printf(GREEN "\n\nVoltando ao menu...\n"RESET);
                break;
            default: 
                printf(RED "\nOpcao invalida.\n"RESET);
                pauseGame();
        }
    } while (opcao != 0);
}


#endif