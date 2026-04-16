#ifndef PEDIDOS_h
#define PEDIDOS_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "ESTOQUE.h"
#include "FILA.h"  
#include "CARDAPIO.h"    



// a funcao randomiza os pedidos que serao gerados no dia, entre 1 e 10 (ids dos hamburgueres)
// crie uma fila para organizar a dos pedidos

// rand randomiza o id dos hamburgueres pedidos em um dia
// a qtd de pedidos randomizei na main; de 4 a 10 pedidos em um unico dia

void gerarPedidos(tp_fila *filaPedidos, int qtdPedidos) {
    for (int i = 0; i < qtdPedidos; i++) {
        int idHamburguer = (rand() % hamburguerMAX) + 1;
        insereFila(filaPedidos, idHamburguer);
    }
}

// imprime os pedidos de um dia no formato --> xxx - [i] nome do hamburguer <--
// apos a fila dos pedidos gerada no codigo acima, imprimePedidos remove o id do hamburguer da fila e printa na main

void imprimePedidos(tp_fila f, hamburguer cardapio[]) {
    tp_item e;
    int contador = 1; // 1 porque os pedidos partem do pedido 001
    
    printf(MAGENTA "\n--- PEDIDOS DO DIA ---\n" RESET);
    while (!filaVazia(&f)) {
        removeFila(&f, &e);
        printf("%03d - [%d] %s\n", contador, e, cardapio[e - 1].nome); // O formato %03d garante que o número do pedido tenha sempre 3 dígitos, preenchendo com zeros se preciso
        contador++;
    }
}

#endif