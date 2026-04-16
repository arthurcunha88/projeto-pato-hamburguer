#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PEDIDOS.h"
#include "CARDAPIO.h"
#include "ESTOQUE.h"
#include "PILHA.h"
#include "FILA.h"
#include "DIA.h"
#include "LISTADE.h"
#include "COLORS.H" 

//aloca o registro de um dia no final da listade
void registrarDia(tp_listade *historico, tp_dia *novoDia) {

    insereListadeNoFim(historico, (tp_item_de)novoDia);
}

//exibe o historico com formato de "tabela"
void exibirHistorico(tp_listade *historico) {
    if (listadeVazia(historico)) {
        printf(YELLOW "\n Nenhum dia registrado ainda.\n" RESET); 
        return;
    }

    printf(CYAN "\n============================ HISTORICO DE ATENDIMENTOS ===========================\n" RESET); 
    printf(MAGENTA " Dia  | Pedidos | Faturamento (R$)  | Lucro (R$)  | Custo Prod. (R$) | Status\n" RESET); 
    printf(CYAN "----------------------------------------------------------------------------------\n" RESET);

    tp_no *atu = historico->ini;
    while (atu != NULL) {
        tp_dia *d = (tp_dia*)atu->info;

        const char *corLucro = (d->lucroTotal >= 0) ? GREEN : RED;
        const char *corCusto = (d->custo > 0) ? YELLOW : RESET; // Se houver custo, destaca em amarelo

        printf(" %-3d  | " YELLOW "%-7d" RESET " | " GREEN "R$%-15.2f" RESET " | %s" "R$%-9.2f" RESET " | %s" "R$%-14.2f" RESET " | %s\n",
                d->dia,
                d->pedidosAtendidos,
                d->faturamento,
                corLucro, d->lucroTotal,
                corCusto, d->custo,
                d->estado);

        atu = atu->prox;
    }

    printf(CYAN "==================================================================================\n" RESET); 
}

void exibirResumoGeral(tp_listade *historico) {
    if (listadeVazia(historico)) {
        printf(YELLOW "\n Nenhum historico disponível para resumo.\n" RESET); 
        return;
    }

    int totalPedidos = 0;
    float receitaGeral = 0, lucroGeral = 0, somaCustos = 0;

    tp_no *atu = historico->ini;
    while (atu != NULL) {
        tp_dia *d = (tp_dia*)atu->info;
        totalPedidos += d->pedidosAtendidos;
        receitaGeral += d->faturamento;
        lucroGeral += d->lucroTotal;
        somaCustos += d->custo;
        atu = atu->prox;
    }

    // Lógica de cores para Lucro Geral no resumo
    const char *corLucroGeral = (lucroGeral >= 0) ? GREEN : RED;

    printf(MAGENTA "\n========= RESUMO GERAL DA PATO BURGER =========\n" RESET); 
    printf("Total de pedidos: " CYAN "%d\n" RESET, totalPedidos);
    printf("Faturamento total: " GREEN "R$%.2f\n" RESET, receitaGeral);
    printf("Lucro acumulado: " "%s R$%.2f\n" RESET, corLucroGeral, lucroGeral);
    printf("Custo total de produção: " YELLOW "R$%.2f\n" RESET, somaCustos);
    printf(MAGENTA "===============================================\n" RESET); 

}

//funcao armazena informacoes de um dia no historico.txt
void salvarHistoricoEmDisco(tp_listade *historico, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (f == NULL) {
        printf(RED "\nERRO: Não foi possível abrir o arquivo %s para salvar.\n" RESET, nomeArquivo); 
        return;
    }

    tp_no *atu = historico->ini;
    while (atu != NULL) {
        tp_dia *d = (tp_dia*)atu->info;

        fprintf(f, "%d,%d,%.2f,%.2f,%.2f,%s\n",
                d->dia,
                d->pedidosAtendidos,
                d->faturamento,
                d->lucroTotal,
                d->custo,
                d->estado);

        atu = atu->prox;
    }

    fclose(f);
    printf(GREEN "\nHistórico salvo com sucesso.\n" RESET); 
}


void carregarHistoricoDeDisco(tp_listade *historico, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf(YELLOW "-> Arquivo de histórico não encontrado. Um novo sera criado ao salvar.\n" RESET); 
        return;
    }

    char linha[300];
    while (fgets(linha, sizeof(linha), f)) {

        tp_dia *d = (tp_dia*) malloc(sizeof(tp_dia));
        if (!d) {
            printf(RED "Falha ao alocar memória para carregar histórico.\n" RESET); 
            break;
        }

        int result = sscanf(linha, "%d,%d,%f,%f,%f,%19[^\n]", //informacoes armazenadas de um dia de atendimento da pato burger
                             &d->dia,
                             &d->pedidosAtendidos,
                             &d->faturamento,
                             &d->lucroTotal,
                             &d->custo,
                             d->estado);

        if (result == 6) {
            registrarDia(historico, d);
        } else {
            printf(YELLOW "Aviso: Linha mal formatada no histórico: %s" RESET, linha); 
            free(d);
        }
    }

    fclose(f);
    printf(BRIGHT_WHITE "-> Histórico carregado.\n" RESET); 
}


int obterProximoDia(tp_listade *historico) { //mecanica para adicionar + 1 dia no historico
    if (listadeVazia(historico)) {
        return 1;
    }

    tp_dia *ultimoDia = (tp_dia*)historico->fim->info;
    return ultimoDia->dia + 1;
}


tp_listade * DestroiHistorico (tp_listade *lista){  //apagar listade do historico ao final de um dia
  tp_no *atu, *prox;
  atu = lista->ini;
  while (atu != NULL)  {
        prox = atu->prox;

        if (atu->info != NULL) {
              free((tp_dia*)atu->info);
        }

        free(atu);
        atu = prox;
        }
  free(lista);
  return NULL;
}

#endif