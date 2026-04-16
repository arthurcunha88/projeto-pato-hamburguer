#ifndef ESTOQUE_h
#define ESTOQUE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "ARVOREAVL.h"
#include "COLORS.H"

#define ingredienteMAX 14

typedef struct{
	char nome[30];
	int quantidade;
	float precoCompra;
	float precoVenda;
	int id;
} ingrediente;

// funcao para armazenar cada ingrediente e definir o nome de cada um, por meio do strcpy
// com a implementacao da loja, foram adicionadas funcoes para adicionar e retirar os itens do estoque
// o id facilita a manipulação dos ingredientes, para definir, por exemplo, a ordem de preparo de cada hamburguer

// na main, uma struct de nome estoque armazena um ingrediente em cada estoque[i], em que i é organiza cada um dos 14 ingredientes (0-13)

void inicializarEstoque(ingrediente estoque[]) {
    
    const float FATOR_VENDA = 0.8; //venda do ingrediente sera 0.8 do valor da compra

    // Ingrediente: Pao
    strcpy(estoque[0].nome, "Pao");
    estoque[0].quantidade = 67;
    estoque[0].precoCompra = 0.40;
    estoque[0].precoVenda = estoque[0].precoCompra * FATOR_VENDA;
    estoque[0].id = 0;

    // Ingrediente: Carne
    strcpy(estoque[1].nome, "Carne");
    estoque[1].quantidade = 20;
    estoque[1].precoCompra = 4.50;
    estoque[1].precoVenda = estoque[1].precoCompra * FATOR_VENDA;
    estoque[1].id = 1;

    // Ingrediente: Bacon
    strcpy(estoque[2].nome, "Bacon");
    estoque[2].quantidade = 10;
    estoque[2].precoCompra = 2.50;
    estoque[2].precoVenda = estoque[2].precoCompra * FATOR_VENDA;
    estoque[2].id = 2;

    // Ingrediente: Queijo
    strcpy(estoque[3].nome, "Queijo");
    estoque[3].quantidade = 25;
    estoque[3].precoCompra = 2.00;
    estoque[3].precoVenda = estoque[3].precoCompra * FATOR_VENDA;
    estoque[3].id = 3;

    // Ingrediente: Alface
    strcpy(estoque[4].nome, "Alface");
    estoque[4].quantidade = 20;
    estoque[4].precoCompra = 1.50;
    estoque[4].precoVenda = estoque[4].precoCompra * FATOR_VENDA;
    estoque[4].id = 4;

    // Ingrediente: Tomate
    strcpy(estoque[5].nome, "Tomate");
    estoque[5].quantidade = 20;
    estoque[5].precoCompra = 1.50;
    estoque[5].precoVenda = estoque[5].precoCompra * FATOR_VENDA;
    estoque[5].id = 5;

    // Ingrediente: Onion Rings
    strcpy(estoque[6].nome, "Onion Rings");
    estoque[6].quantidade = 8;
    estoque[6].precoCompra = 3.00;
    estoque[6].precoVenda = estoque[6].precoCompra * FATOR_VENDA;
    estoque[6].id = 6;

    // Ingrediente: Cebola Caramelizada
    strcpy(estoque[7].nome, "Cebola Caramelizada");
    estoque[7].quantidade = 12;
    estoque[7].precoCompra = 2.00;
    estoque[7].precoVenda = estoque[7].precoCompra * FATOR_VENDA;
    estoque[7].id = 7;

    // Ingrediente: Picles
    strcpy(estoque[8].nome, "Picles");
    estoque[8].quantidade = 12;
    estoque[8].precoCompra = 1.00;
    estoque[8].precoVenda = estoque[8].precoCompra * FATOR_VENDA;
    estoque[8].id = 8;

    // Ingrediente: Ketchup
    strcpy(estoque[9].nome, "Ketchup");
    estoque[9].quantidade = 32;
    estoque[9].precoCompra = 1.00;
    estoque[9].precoVenda = estoque[9].precoCompra * FATOR_VENDA;
    estoque[9].id = 9;

    // Ingrediente: Maionese Verde
    strcpy(estoque[10].nome, "Maionese Verde");
    estoque[10].quantidade = 8;
    estoque[10].precoCompra = 1.80;
    estoque[10].precoVenda = estoque[10].precoCompra * FATOR_VENDA;
    estoque[10].id = 10;

    // Ingrediente: Geleia de Pimenta
    strcpy(estoque[11].nome, "Geleia de Pimenta");
    estoque[11].quantidade = 5;
    estoque[11].precoCompra = 4.00;
    estoque[11].precoVenda = estoque[11].precoCompra * FATOR_VENDA;
    estoque[11].id = 11;

    // Ingrediente: Molho Cheddar
    strcpy(estoque[12].nome, "Molho Cheddar");
    estoque[12].quantidade = 10;
    estoque[12].precoCompra = 4.00;
    estoque[12].precoVenda = estoque[12].precoCompra * FATOR_VENDA;
    estoque[12].id = 12;

    // Ingrediente: Frango
    strcpy(estoque[13].nome, "Frango");
    estoque[13].quantidade = 20;
    estoque[13].precoCompra = 3.00;
    estoque[13].precoVenda = estoque[13].precoCompra * FATOR_VENDA;
    estoque[13].id = 13;
}

// Exibe todos os ingredientes no estoque em forma de tabela
void exibirEstoque(ingrediente estoque[]) {
    printf(BRIGHT_CYAN "\n================== ESTOQUE ATUAL ==================\n" RESET);
    printf(BRIGHT_WHITE "%-20s | %-10s | %-10s\n" RESET, "Ingrediente", "Qtd.", "Preco Compra");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < ingredienteMAX; i++) {
        if (estoque[i].quantidade > 0) {
            printf(GREEN "%-20s" RESET " |" YELLOW "%-10d" RESET "  |" CYAN "R$%-9.2f\n" RESET,
                   estoque[i].nome,
                   estoque[i].quantidade,
                   estoque[i].precoCompra);
        }
    }

    printf("---------------------------------------------------\n");
}

// Adiciona quantidade ao ingrediente existente (nao cria novos)
int adicionarEstoque(ingrediente estoque[], char nome[], int qtd) {
    for (int i = 0; i < ingredienteMAX; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            estoque[i].quantidade += qtd;
            return 1; // sucesso
        }
    }
    printf( RED"Ingrediente '%s' nao encontrado no estoque.\n"RESET, nome);
    return 0; // falhou, ingrediente inexistente
}

// Retira quantidade do estoque (sem remover o item)
int retirarDoEstoque(ingrediente estoque[], char nome[], int qtd) {
    for (int i = 0; i < ingredienteMAX; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            if (estoque[i].quantidade >= qtd) {
                estoque[i].quantidade -= qtd;
                return 1; // sucesso
            } else {
                printf(RED "Quantidade insuficiente de '%s' no estoque.\n"RESET, nome);
                return 0; // nao ha o suficiente
            }
        }
    }
    printf(RED"Ingrediente '%s' nao encontrado no estoque.\n"RESET, nome);
    return 0; // nao existe
} //essas opcoes de ingrediente nao existe nunca devem ser acessadas, mas estao por garantia de algum bug ou etc

int estoqueVazio(ingrediente estoque[]) {
    for (int i = 0; i < ingredienteMAX; i++) {
        if (estoque[i].quantidade > 0) {
            return 0; // Encontrou pelo menos um item
        }
    }
    return 1; // Estoque totalmente vazio
}
int registrarSaidaDeItem(ingrediente estoque[], ArvAVL* relatorio, int id, int qtd){

    if (retirarDoEstoque(estoque, estoque[id].nome, qtd)) {   

        inserir(relatorio, id, qtd);
        printf(GREEN ">> Item consumido: %d x %s\n" RESET, qtd, estoque[id].nome);
        return 1;
    }
    return 0;
}
 
void imprimirRelatorioFinal(ArvAVL* raiz, ingrediente estoque[]){
    if (raiz == NULL) return;

    if (*raiz != NULL) {

        imprimirRelatorioFinal(&((*raiz)->esq), estoque);

        int id = (*raiz)->info;

        printf(BRIGHT_CYAN "Ingrediente: " RESET BRIGHT_WHITE "%-20s" RESET BRIGHT_YELLOW "| Total consumido: " RESET GREEN "%d\n" RESET, estoque[id].nome, (*raiz)->qntConsumida);

        imprimirRelatorioFinal(&((*raiz)->dir), estoque);
    }
}

typedef struct {
    char nome[30];
    int qtdTotal;
} ItemRanking;

// Função auxiliar recursiva para preencher os ingrediente sorganizados pela quantidade
void aux_PreencherVetorRanking(ArvAVL* raiz, ingrediente estoque[], ItemRanking vetor[]) { //RANKING DE INGREDIENTES MAIS CONSUMIDOS

    if (raiz == NULL || *raiz == NULL) return;

    aux_PreencherVetorRanking(&((*raiz)->esq), estoque, vetor);

    int id = (*raiz)->info;
    // O vetor é indexado pelo ID do ingrediente (0 a 13)
    strcpy(vetor[id].nome, estoque[id].nome);
    vetor[id].qtdTotal = (*raiz)->qntConsumida; 

    aux_PreencherVetorRanking(&((*raiz)->dir), estoque, vetor);
}

// Função de comparação para o qsort (Decrescente)
int compararRanking(const void *a, const void *b) {
    ItemRanking *ia = (ItemRanking *)a;
    ItemRanking *ib = (ItemRanking *)b;
    return (ib->qtdTotal - ia->qtdTotal); // Decrescente
}

void exibirRanking(ArvAVL* raizRelatorio, ingrediente estoque[]) {
    ItemRanking ranking[ingredienteMAX];
    
    //iniciaiza o vetor
    for(int i=0; i < ingredienteMAX; i++) {
        strcpy(ranking[i].nome, estoque[i].nome);
        ranking[i].qtdTotal = 0;
    }

    // Preenche com os dados da Árvore 
    if (raizRelatorio != NULL && *raizRelatorio != NULL) {
        aux_PreencherVetorRanking(raizRelatorio, estoque, ranking);
    }
    
    //ordena com quicksort
    qsort(ranking, ingredienteMAX, sizeof(ItemRanking), compararRanking); //ranking é o endereço, ingredientemax num de elementos, sizeof tamanho de bytes de cada elemento, comparaRanking funcao de comparacao para o qsort

    printf(CYAN "Ranking de Itens Mais Vendidos (Total Global):\n" RESET);
    printf("---------------------------------------------------\n");
    printf(MAGENTA "%-20s" RESET     " | " BRIGHT_GREEN "%s\n" RESET, "Ingrediente", "Qtd. Vendida");
    printf("---------------------------------------------------\n");
    
    for(int i=0; i < ingredienteMAX; i++) {
        if(ranking[i].qtdTotal > 0) {
            printf(BRIGHT_GREEN "%-20s" RESET " | " BRIGHT_YELLOW "%d\n" RESET, ranking[i].nome, ranking[i].qtdTotal);
        }
    }
    printf("---------------------------------------------------\n");
}


void aux_MergeArvores(ArvAVL* raizDia, ArvAVL* raizRelatorio) { //recursivamente, passa pelos valores a esquerda e pela direita e insere na arvore final, raiz relatorio
    if (raizDia == NULL || *raizDia == NULL) return;

    aux_MergeArvores(&((*raizDia)->esq), raizRelatorio);
    aux_MergeArvores(&((*raizDia)->dir), raizRelatorio);

    inserir(raizRelatorio, (*raizDia)->info, (*raizDia)->qntConsumida); //inserção
    
}

// Função chamada ao final do dia para atualizar o histórico global
void atualizarRelatorioGlobal(ArvAVL* relatorioDia, ArvAVL* relatorioGlobal) {
    aux_MergeArvores(relatorioDia, relatorioGlobal);
}

#endif