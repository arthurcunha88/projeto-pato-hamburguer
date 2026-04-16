/// =========================================================================================================
// PATO BURGER GAME - GRUPO PILOTO
// Feito por Arthur Andrade Cunha, Arthur Piloto Bastos, Isaque Pessoa, Marcel Guedes, Pedro Henrique Aguiar.
/// =========================================================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h> //biblioteca para randomizar
#include "PILHA.h"
#include "FILA.h"
#include "COLORS.H"
#include "ESTOQUE.h"
#include "CARDAPIO.h"
#include "PEDIDOS.h"
#include "LISTADE.h"
#include "DIA.h"
#include "INGAME.h"

int main() {
    iniciarJogo(); //main simplificada, tudo controlado pelo ingame que abriga as funcoes de todas as outras .h's
    return 0;
}