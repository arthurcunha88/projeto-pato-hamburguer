#ifndef CARDAPIO_h
#define CARDAPIO_h

#include <string.h>
#include "ESTOQUE.h"
#include "PILHA.h"
#include "COLORS.H"

#define hamburguerMAX 10


typedef struct {
    tp_pilha burger;
    char nome[30];
    float preco;
    int id;
    int receita[20];
    int numItens;
} hamburguer;

// funcao guarda as informacoes do cardapio da hamburgueria
// como parametros sao passados uma struct com as informações de cada hamburguer e uma struct para declarar os ingredientes, em ordem, de cada hamburguer

void inicializarCardapio(hamburguer cardapio[], ingrediente estoque[]) {
    int k;

    // 1. Bit and Bacon
    strcpy(cardapio[0].nome, "Bit and Bacon");
    cardapio[0].preco = 22.00; cardapio[0].id = 1;
    int receita0[] = {0, 2, 3, 1, 0, -1}; 
    k = 0; while (receita0[k] != -1) { cardapio[0].receita[k] = receita0[k]; k++; } //limite -1 para parar a ordem da receita
    cardapio[0].numItens = k; //k é declarado para numerar a quantidade de ingredientes de cada hamburguer (numItens)

    // 2. Duck Cheese
    strcpy(cardapio[1].nome, "Duck Cheese");
    cardapio[1].preco = 25.00; cardapio[1].id = 2;
    int receita1[] = {0, 4, 5, 1, 3, 0, -1}; 
    k = 0; while (receita1[k] != -1) { cardapio[1].receita[k] = receita1[k]; k++; }
    cardapio[1].numItens = k; //k segue a mesma logica em todos os hamburgueres

    // 3. Quackteirao
    strcpy(cardapio[2].nome, "Quackteirao");
    cardapio[2].preco = 26.00; cardapio[2].id = 3;
    int receita2[] = {0, 4, 3, 1, 3, 0, -1}; 
    k = 0; while (receita2[k] != -1) { cardapio[2].receita[k] = receita2[k]; k++; }
    cardapio[2].numItens = k;

    // 4. Big Pato
    strcpy(cardapio[3].nome, "Big Pato");
    cardapio[3].preco = 30.00; cardapio[3].id = 4;
    int receita3[] = {0, 3, 1, 4, 0, 1, 3, 4, 0, -1}; 
    k = 0; while (receita3[k] != -1) { cardapio[3].receita[k] = receita3[k]; k++; }
    cardapio[3].numItens = k;

    // 5. Donald 
    strcpy(cardapio[4].nome, "Donald");
    cardapio[4].preco = 32.00; cardapio[4].id = 5;
    int receita4[] = {0, 8, 7, 5, 4, 13, 3, 10, 0, -1}; 
    k = 0; while (receita4[k] != -1) { cardapio[4].receita[k] = receita4[k]; k++; }
    cardapio[4].numItens = k;

    // 6. Patolino
    strcpy(cardapio[5].nome, "Patolino");
    cardapio[5].preco = 32.00; cardapio[5].id = 6;
    int receita5[] = {0, 2, 12, 1, 7, 3, 9, 0, -1}; 
    k = 0; while (receita5[k] != -1) { cardapio[5].receita[k] = receita5[k]; k++; }
    cardapio[5].numItens = k;

    // 7. Duckling
    strcpy(cardapio[6].nome, "Duckling");
    cardapio[6].preco = 22.50; cardapio[6].id = 7;
    int receita6[] = {0, 10, 1, 3, 0, -1}; 
    k = 0; while (receita6[k] != -1) { cardapio[6].receita[k] = receita6[k]; k++; }
    cardapio[6].numItens = k;

    // 8. PatOnion
    strcpy(cardapio[7].nome, "PatOnion");
    cardapio[7].preco = 33.00; cardapio[7].id = 8;
    int receita7[] = {0, 7, 12, 6, 1, 6, 3, 0, -1}; 
    k = 0; while (receita7[k] != -1) { cardapio[7].receita[k] = receita7[k]; k++; }
    cardapio[7].numItens = k;

    // 9. Tio Patinhas
    strcpy(cardapio[8].nome, "Tio Patinhas");
    cardapio[8].preco = 44.00; cardapio[8].id = 9;
    int receita8[] = {0, 11, 4, 7, 1, 3, 2, 1, 0, -1}; 
    k = 0; while (receita8[k] != -1) { cardapio[8].receita[k] = receita8[k]; k++; }
    cardapio[8].numItens = k;

    // 10.DuX-Tudo
    strcpy(cardapio[9].nome, "DuX-Tudo");
    cardapio[9].preco = 55.00; cardapio[9].id = 10;
    int receita9[] = {0, 11, 7, 8, 5, 4, 2, 12, 3, 1, 10, 0, 6, 2, 12, 3, 1, 0, -1}; 
    k = 0; while (receita9[k] != -1) { cardapio[9].receita[k] = receita9[k]; k++; }
    cardapio[9].numItens = k;
}

// função para printar o cardapio na main
// tem como parametros as mesmas coisas do inicilizar cardapio (struct com as informações de cada hamburguer e struct para printar ingredientes do estoque)

void exibirCardapio(hamburguer cardapio[], ingrediente estoque[]) { 
    printf(BRIGHT_CYAN "\n ---- CARDAPIO PATO BURGER ----\n" RESET);
    for (int i = 0; i < hamburguerMAX; i++) {
        printf(BRIGHT_YELLOW"\n[%d]" RESET BRIGHT_WHITE "%s" RESET "-" GREEN "R$ %.2f\n" RESET, cardapio[i].id, cardapio[i].nome, cardapio[i].preco); // printa id, nome e preco
        printf(BRIGHT_MAGENTA "    Ordem de preparo:\n" RESET); // espaços para ficar organizado
        for (int j = 0; j < cardapio[i].numItens; j++) {
            printf(CYAN "     %d)" RESET BRIGHT_WHITE "%s\n" RESET, j + 1, estoque[cardapio[i].receita[j]].nome); // espaços para alinhar com "ordem de preparo:"
        }
    }
}

#endif