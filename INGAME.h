#ifndef INGAME_H
#define INGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "CARDAPIO.h"
#include "ESTOQUE.h"
#include "PEDIDOS.h"
#include "DIA.h"
#include "HISTORICO.h"
#include "LOJA.h"
#include "ARVOREAVL.h"
#include "COLORS.H"

#define CUSTO_OPERACIONAL 30.0f //custo diario de 30 conto

// Limpa a tela do terminal
void clearScreen() {
    system("clear"); //gdb/linux
    //system("cls"); //windows
}

//limpa o buffer de entrada pra evitar bugs
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

//pausa o jogo e espera o enter
void pauseGame() {
    printf("\n\n" CYAN " Pressione ENTER para continuar...\n" RESET);
    limparBufferEntrada(); //espera o enter e ignora a sujeira
}

//exibe o menu principal
void exibirMenu() {
    clearScreen(); // Adicionado para limpar a tela antes de exibir o menu
    printf(CYAN "\n================ MENU =================\n" RESET);
    printf(YELLOW "1" RESET " - Ver cardapio\n");
    printf(YELLOW "2" RESET " - Iniciar novo dia\n");
    printf(YELLOW "3" RESET " - Ver historico\n");
    printf(YELLOW "4" RESET " - Ver estoque\n");
    printf(YELLOW "5" RESET " - Acessar loja\n");
    printf(YELLOW "6" RESET " - Ingredientes consumidos\n");
    printf(YELLOW "7" RESET " - Salvar jogo\n");
    printf(YELLOW "8" RESET " - Salvar e sair\n");
    printf(CYAN "=======================================\n" RESET);
    printf("Escolha uma opcao: ");
}

//funcao para encerrar o jogo por falencia
void encerrarJogoPorFalencia(float saldo, ArvAVL* relatorioGlobal, ingrediente estoque[]) {
    clearScreen();
    printf(RED "\n===================================================\n" RESET);
    printf(RED "             FALENCIA... FIM DE JOGO\n" RESET);
    printf(RED "===================================================\n" RESET);
    printf(YELLOW "Seu saldo (R$%.2f) esta negativo e o estoque zerou.\n\n" RESET, saldo);
    
    if (relatorioGlobal != NULL) {
        printf(MAGENTA "\n=========== RELATORIO FINAL PATO BURGER ===========\n" RESET);
        exibirRanking(relatorioGlobal, estoque);
    }
    
    printf(RED "\nO jogo sera encerrado.\n" RESET);
    pauseGame(); // Adicionado para que o jogador possa ver o relatório final
    liberaABB(relatorioGlobal);
    exit(0);
}

//verifica a condicao de falencia
void verificarFalencia(float saldo, ingrediente estoque[], ArvAVL* relatorioGlobal) {
    if (saldo < 0.40 && estoqueVazio(estoque)) { //0.40 pois eh o valor de compra minima
        encerrarJogoPorFalencia(saldo, relatorioGlobal, estoque);
    }
}

// Funcao principal do jogo
void iniciarJogo() {
    srand(time(NULL));

    // Estruturas principais
    ingrediente estoque[ingredienteMAX];
    hamburguer cardapio[hamburguerMAX];
    tp_listade *historico = inicializaListade();

    if (historico == NULL) {
        printf(RED "Nao foi possivel alocar memoria para o jogo. Reinicie o sistema.\n" RESET);
        return;
    }
    
    ArvAVL* relatorioGlobal = criarAVL();
    
    // Carrega historico salvo, se existir
    carregarHistoricoDeDisco(historico, "historico.txt");

    // Inicializa estoque e cardapio
    inicializarEstoque(estoque);
    inicializarCardapio(cardapio, estoque);

    // Cria loja automaticamente com base no estoque
    tp_loja *loja = inicializarLoja(estoque, ingredienteMAX);

    float saldo = 70.00; // saldo inicial (R$)
    int opcao = 0;
    int jogando = 1;
    int dia = obterProximoDia(historico);
    
    
    printf("\n\n" YELLOW "PATO BURGER" RESET BRIGHT_WHITE " - " RESET RED "PILOTO STUDIOS\n" RESET);
    printf(CYAN "PRESSIONE ENTER PARA COMEÇAR\n" RESET);
    limparBufferEntrada();
    
    clearScreen(); // Adicionado para garantir que a tela inicial esteja limpa
    printf(MAGENTA "==============================================================================\n" RESET);
    printf(MAGENTA "===== Bem-vindo à Pato Burger, a hamburgueria mais otimizada do Brasil! ======\n" RESET);
    printf(MAGENTA "==============================================================================\n" RESET);
    
    printf("\n" BLUE " -- Gerente:                                --------------------------------------------------------------------------" RESET);
    printf("\n" BLUE " |" RESET YELLOW "OLA CHEFE, VIM TE DAR AS BOAS VINDAS AO SEU NOVO EMPREGO.                                                          "RESET BLUE "|" RESET);
    printf("\n" BLUE " |" RESET YELLOW "ULTIMAMENTE NAO ESTAMOS TENDO SORTE COM NOSSA COZINHA E PRECISAMOS DA SUA AJUDA PARA ORGANIZAR NOSSA HAMBURGUERIA! "RESET BLUE "|" RESET);
    printf("\n" BLUE " |" RESET YELLOW "PARA FACILITAR SUA EXPERIENCIA, ORGANIZAMOS UM MENU PARA VOCE NAO PERDER OS CABELOS COM OS PEDIDOS...              "RESET BLUE "|" RESET);
    printf("\n" BLUE " |" RESET YELLOW "NOSSO ULTIMO CHEFE TERMINOU CARECA... MAS NADA QUE TE PREOCUPE, CERTO?                                             "RESET BLUE "|" RESET);
    printf("\n" BLUE " |" RESET YELLOW "SE DIVIRTA E VAMOS COLOCAR A MAO NA MASSA (ou nos ingredientes, rs).                                               "RESET BLUE "|" RESET);
    printf("\n" BLUE " ---------------------------------------------------------------------------------------------------------------------" RESET);
    
    pauseGame();
    clearScreen();

    while (jogando) {
        
        //Verifica falencia (Pode ter falido após Loja ou dia anterior)
        verificarFalencia(saldo, estoque, relatorioGlobal);
        

        exibirMenu();

        int resultadoScan = scanf("%d", &opcao);
        limparBufferEntrada();

        if (resultadoScan == 0) {
            opcao = -1;
        }

        switch (opcao) {
            case 1: // cardapio
                clearScreen();
                exibirCardapio(cardapio, estoque);
                pauseGame();
                break;

            case 2: { // Iniciar dia de atendimento
                clearScreen();
                
                //aplica o custo operacional no INICIO de cada ciclo do jogo e desconta do saldo do usuario
                if (dia > 1) { // Não cobra o custo no primeiro dia (dia 1) {dia>1}
                    float saldoAnterior = saldo;
                    saldo -= CUSTO_OPERACIONAL;
                    printf(YELLOW "\n--- CUSTO DIARIO ---\n" RESET);
                    printf("Custo de operacao referente ao dia %d abatido: " RED "R$%.2f\n" RESET, dia, CUSTO_OPERACIONAL);
                    printf("Saldo: " GREEN "R$%.2f" RESET " -> " RED "R$%.2f\n" RESET, saldoAnterior, saldo);
                    printf(YELLOW "--------------------\n" RESET);
                    pauseGame(); // Adicionado para o usuário ver a cobrança do custo
                    clearScreen();

                    // Verifica falencia imediatamente após o débito, caso tenha zerado
                    verificarFalencia(saldo, estoque, relatorioGlobal);
                }
                
                printf(CYAN "\n--- INICIANDO DIA %d ---\n" RESET, dia);
                printf("Saldo atual antes das vendas: " GREEN "R$%.2f\n" RESET, saldo);
                printf(CYAN "------------------------\n" RESET);
                pauseGame();
                clearScreen();
                
                // Logica do atendimento
                tp_dia resultado = atenderDia(dia, cardapio, estoque, relatorioGlobal);

                tp_dia *ptrDia = (tp_dia*) malloc(sizeof(tp_dia));
                if (ptrDia == NULL) {
                    printf(RED "Erro ao registrar o dia. Memoria insuficiente.\n" RESET);
                    pauseGame();
                    break;
                }

                *ptrDia = resultado;
                registrarDia(historico, ptrDia);
                saldo += resultado.lucroTotal; // adiciona lucro do dia ao saldo
                dia++;

                printf(GREEN "\n -> CHEFE, o dia %d foi finalizado com lucro de R$%.2f... Nosso saldo atual é de R$%.2f.\n" RESET,
                        resultado.dia, resultado.lucroTotal, saldo);

                pauseGame();
                break;
            }

            case 3: // Historico dos dias
                clearScreen();
                exibirHistorico(historico);
                pauseGame();
                break;

            case 4: // Estoque
                clearScreen();
                exibirEstoque(estoque);
                pauseGame();
                break;

            case 5: // Loja Patonica
                clearScreen();
                abrirLoja(loja, estoque, &saldo);
                verificarFalencia(saldo, estoque, relatorioGlobal); // Checa falência após possível gasto na loja
                break;
                
            case 6: // Mostrar ingredientes ja consumidos
                clearScreen();
                
                if (relatorioGlobal != NULL) {
                     exibirRanking(relatorioGlobal, estoque); 
                } else {
                     printf(YELLOW "\nNenhum ingrediente consumido ainda.\n" RESET);
                }

                pauseGame(); 
                break;
                

            case 7: // Salvar jogo
                clearScreen();
                salvarHistoricoEmDisco(historico, "historico.txt");
                printf(GREEN "Jogo salvo com sucesso.\n" RESET);
                pauseGame();
                break;

            case 8: // Salvar e sair
                clearScreen();
                salvarHistoricoEmDisco(historico, "historico.txt");
                jogando = 0;
                printf(CYAN "Jogo salvo. Ate logo, CHEFE!\n" RESET);
                printf(CYAN "Saindo...\n" RESET);
                pauseGame(); 
                break;

            default:
                printf(RED "\nOpcao invalida. Tente novamente.\n" RESET);
                pauseGame();
                break;
        }

        if (jogando) {
        }
    }

    historico = DestroiHistorico(historico);
    
    liberaABB(relatorioGlobal);
}

#endif