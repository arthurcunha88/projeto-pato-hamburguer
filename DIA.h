#ifndef DIA_H
#define DIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PEDIDOS.h"
#include "CARDAPIO.h"
#include "ESTOQUE.h"
#include "PILHA.h"
#include "FILA.h"

//funcoes que coordenam um dia de atendimento


void clearScreen();
void pauseGame();
void limparBufferEntrada();

typedef struct {
    int dia;
    int pedidosAtendidos;
    float faturamento;
    float lucroTotal;
    float custo;
    char estado[20]; // condição, status
} tp_dia;

// Usa os ingredientes da receita e calcula o custo total (ingredientes do estoque)
float usarIngredientes(tp_pilha *burgerJogador, ingrediente estoque[], ArvAVL* relatorioDia) {
    float custo = 0;
    tp_item idIng;

    tp_pilha aux; 
    inicializaPilha(&aux);

    while(pop(burgerJogador, &idIng)) {
        push(&aux, idIng);
    }

    while (pop(&aux, &idIng)) { 
        
        if (registrarSaidaDeItem(estoque, relatorioDia, idIng, 1)) {
            custo += estoque[idIng].precoCompra;
        } else {
            printf(YELLOW "AVISO: Ingrediente '%s' acabou durante o preparo!\n" RESET, estoque[idIng].nome);
        }
    }
    
    return custo;
}

// Usuário monta o hambúrguer manualmente 
void montarHamburguerManual(tp_pilha *burger, ingrediente estoque[]) {
    inicializaPilha(burger);
    int idEscolhido; //id do ingrediente do estoque sendo utilizado

    printf(CYAN "\n MONTE SEU HAMBURGUER \n" RESET);
    printf("Digite os ingredientes na ordem desejada (use o ID do estoque)\n");
    printf(YELLOW "Digite -1 para finalizar a montagem.\n\n" RESET);

    // Exibe ingredientes disponíveis no estoque (sempre atualizados a partir da monatgem dos hamburgueres)
    printf(MAGENTA "=========== ESTOQUE DISPONIVEL ===========\n" RESET);
    for (int i = 0; i < ingredienteMAX; i++) {
        printf("[%d] %-20s | Quantidade: %d\n", i, estoque[i].nome, estoque[i].quantidade); //%-20s para alinhar os ingredientes bonitinho
    }
    printf(MAGENTA "==========================================\n" RESET);

    while (1) {
        printf("\nEscolha o ID do ingrediente (ou -1 para finalizar): ");
        if (scanf("%d", &idEscolhido) != 1) {
            limparBufferEntrada(); // Limpa o buffer em caso de entrada inválida
            printf(RED "Entrada invalida. Tente novamente.\n" RESET);
            continue;
        }
        
        limparBufferEntrada();

        if (idEscolhido == -1)
            break;

        if (idEscolhido < 0 || idEscolhido >= ingredienteMAX) {
            printf(RED "ID invalido! Tente novamente.\n" RESET);
            continue;
        }

        if (estoque[idEscolhido].quantidade <= 0) {
            printf(YELLOW"O ingrediente '%s' está esgotado!\n" RESET, estoque[idEscolhido].nome);
            continue;
        }

        push(burger, idEscolhido);
        printf(GREEN "'%s' adicionado à montagem!\n" RESET, estoque[idEscolhido].nome);
    }

    if (pilhaVazia(burger)) {
        printf(RED "\n Nenhum ingrediente foi adicionado!\n" RESET);
        return;
    }

    printf(CYAN "\n SUA MONTAGEM FINAL \n" RESET); //de cima pra baixo
    tp_pilha aux;
    inicializaPilha(&aux);
    int idTemp;

    // Mostra de cima pra baixo sem destruir a pilha original
    while (!pilhaVazia(burger)) {
        pop(burger, &idTemp);
        printf("- %s\n", estoque[idTemp].nome);
        push(&aux, idTemp);
    }

    // Restaura pilha original
    while (!pilhaVazia(&aux)) {
        pop(&aux, &idTemp);
        push(burger, idTemp);
    }

    printf( CYAN "=============================\n" RESET);
}

// Compara hambúrguer montado com receita do pedido
float compararHamburguer(tp_pilha jogador, tp_pilha receita, float precoHamburguer) {
    tp_item ingJogador, ingReceita;
    int acertos = 0;
    int total = alturaPilha(&receita);

    if (total == 0) {
        return 0.0f;
    }
    
    tp_pilha auxJogador, auxReceita;
    inicializaPilha(&auxJogador);
    inicializaPilha(&auxReceita);
    
    // Esvazia 'jogador' para 'auxJogador' (inverte a ordem)
    while (pop(&jogador, &ingJogador)) {
        push(&auxJogador, ingJogador);
    }
    // Esvazia 'receita' para 'auxReceita' (inverte a ordem)
    while (pop(&receita, &ingReceita)) {
        push(&auxReceita, ingReceita);
    }
    
    //inverte a ordem para comparar as receitas debaixo para cima

    while (!pilhaVazia(&auxJogador) && !pilhaVazia(&auxReceita)) {
        pop(&auxJogador, &ingJogador);
        pop(&auxReceita, &ingReceita);

        if (ingJogador == ingReceita) {
            acertos++;
        }
    }

    float pontuacao = (float)acertos / total;
    float valorRecebido = pontuacao * precoHamburguer;

    printf(CYAN "\n====== RESULTADO DA MONTAGEM ======\n" RESET); //panorama da montagem em relação a receita original
    printf("Ingredientes corretos: %d de %d (%.1f%%)\n", acertos, total, pontuacao * 100);
    printf("Pagamento recebido: " GREEN "R$%.2f " RESET "de R$%.2f\n", valorRecebido, precoHamburguer);

    return valorRecebido;
}

void exibirReceitaEAguardar(hamburguer *h, ingrediente estoque[], int numPedido) {
    clearScreen();
    
    printf(MAGENTA "-> HAMBURGUER: %s\n" RESET, h->nome);
    printf(CYAN "   RECEITA DO PEDIDO %03d\n" RESET, numPedido);
    printf("   (de cima para baixo)\n\n");
    
    for (int j = 0; j < h->numItens; j++) {
        int idIngrediente = h->receita[j];
        printf("   %s\n", estoque[idIngrediente].nome);
    }
    
    printf(YELLOW "\naperte ENTER para começar a montagem\n" RESET);
    
    limparBufferEntrada();
}

// Função principal do dia — organiza a execução e os resultados
tp_dia atenderDia(int dia, hamburguer cardapio[], ingrediente estoque[], ArvAVL* relatorioGlobal) {
    tp_fila filaPedidos;
    inicializaFila(&filaPedidos);
    
    ArvAVL* relatorioDia = criarAVL();

    int qtdPedidos = (rand() % 5) + 2; // 4 a 10 pedidos por dia
    gerarPedidos(&filaPedidos, qtdPedidos);

    printf(CYAN "\n======================\n" RESET);
    printf(MAGENTA "        DIA %d\n" RESET, dia);
    printf(CYAN "======================\n" RESET);
    imprimePedidos(filaPedidos, cardapio);

    pauseGame();
    
    int atendidos = 0;
    float receita = 0.0f;
    float lucro = 0.0f;
    float custoTotal = 0.0f;
    tp_item id;
    int pedidoCont = 1;

    while (!filaVazia(&filaPedidos)) {
        removeFila(&filaPedidos, &id);
        hamburguer *h = &cardapio[id - 1];
        
        exibirReceitaEAguardar(h, estoque, pedidoCont);
        clearScreen();
        
        printf(CYAN "\n Atendendo pedido %03d -> [%d] %s\n" RESET, pedidoCont, id, h->nome);

        // user monta manualment o hambúrguer
        tp_pilha burgerJogador;
        montarHamburguerManual(&burgerJogador, estoque);

        // Cria pilha da receita para comparação
        tp_pilha receitaPilha;
        tp_pilha pilhaAux;
        tp_item e;
        inicializaPilha(&receitaPilha);
        inicializaPilha(&pilhaAux);
        
        for (int i = 0; i < h->numItens; i++) {
            push(&pilhaAux, h->receita[i]);
        }
        
        while(!pilhaVazia(&pilhaAux)) {
            pop(&pilhaAux, &e);
            push(&receitaPilha, e);
        }

        // Compara montagem com receita
        float valorRecebido = compararHamburguer(burgerJogador, receitaPilha, h->preco);

        // Aplica custo real (desconta ingredientes e calcula custo)
        float custoHamburguer = usarIngredientes(&burgerJogador, estoque, relatorioDia);

        if (custoHamburguer < 0) {
            printf(RED "Pedido cancelado por falta de ingredientes.\n" RESET);
        } else {
            receita += valorRecebido;
            custoTotal += custoHamburguer;
            lucro += (valorRecebido - custoHamburguer);
            atendidos++;
        }

        pedidoCont++;
        
        pauseGame();
    }
    
    clearScreen();
    printf(MAGENTA "========== RESUMO GERAL DO DIA %d ==========\n" RESET, dia);
    printf("Pedidos atendidos: " GREEN "%d\n" RESET, atendidos);
    printf("Receita total: " GREEN "R$%.2f\n" RESET, receita);
    printf("Lucro líquido: " GREEN "R$%.2f\n\n" RESET, lucro);

    printf(CYAN "--- Consumo de Ingredientes (Hoje) ---\n" RESET);
    imprimirRelatorioFinal(relatorioDia, estoque);

    atualizarRelatorioGlobal(relatorioDia, relatorioGlobal);
    liberaABB(relatorioDia);

    tp_dia resultado;
    resultado.dia = dia;
    resultado.pedidosAtendidos = atendidos;
    resultado.faturamento = receita;
    resultado.lucroTotal = lucro;
    resultado.custo = custoTotal;
    strcpy(resultado.estado, "Finalizado");
    return resultado;
}

#endif