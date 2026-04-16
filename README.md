# 🍔 Pato Burger - Simulador de Hamburgueria

**Pato Burger** é um simulador de gestão de hamburgueria desenvolvido em **Linguagem C**. O projeto foi concebido para aplicar, de forma prática e lúdica, os conceitos de **Estruturas de Dados Dinâmicas e Estáticas**, abordando desde o gerenciamento de filas de clientes até o balanceamento complexo de árvores de busca para relatórios.

---

## 🧠 Engenharia de Dados e Estruturas

O projeto destaca-se pela integração de múltiplas estruturas de dados, cada uma escolhida para otimizar uma parte específica da lógica do jogo:

### 1. Árvore AVL (`ARVOREAVL.h`)
Utilizada para o **Ranking Global de Consumo de Ingredientes**.
- **Complexidade:** Garante operações de inserção, remoção e busca em $O(\log n)$.
- **Lógica:** Implementa rotações à esquerda (RR), à direita (LL) e duplas (LR/RL) para manter o fator de balanceamento entre -1 e 1, essencial para processar grandes volumes de dados históricos sem perda de performance.

### 2. Lista Duplamente Encadeada Genérica (`LISTADE.h`)
Uma estrutura versátil que utiliza **ponteiros genéricos (`void*`)**.
- **Versatilidade:** Permite que a mesma implementação de lista gerencie tanto o **Histórico de Atendimentos** (`tp_dia`) quanto os **Itens da Loja** (`tp_itemLoja`).
- **Navegação:** Possui ponteiros para o próximo e anterior, facilitando a exibição de relatórios em ordem direta ou reversa.

### 3. Pilha Estática (`PILHA.h`)
Responsável pela **Lógica de Preparo na Cozinha**.
- **Conceito LIFO:** Os ingredientes são "empilhados" conforme o jogador os adiciona. 
- **Validação:** Para finalizar um pedido, o sistema realiza o `pop` dos ingredientes e compara com a receita oficial (também armazenada em pilha), garantindo que a ordem de montagem foi respeitada.

### 4. Fila Estática (`FILA.h`)
Gere a **Fila de Espera de Clientes**.
- **Conceito FIFO:** Garante que o primeiro pedido gerado aleatoriamente (`PEDIDOS.h`) seja o primeiro a ser processado pelo jogador, simulando o fluxo real de uma lanchonete.

---

## 🛠️ Módulos e Funcionalidades Técnicas

### 🎮 Núcleo do Jogo (`INGAME.h` & `main.c`)
- **Arquitetura:** Segue o princípio de **Encapsulamento**. A `main.c` contém apenas a chamada `iniciarJogo()`, enquanto o módulo `INGAME.h` coordena o loop principal, eventos de falência e menus.
- **Lógica de Falência:** Verifica constantemente o saldo e o estoque; se o jogador não possuir recursos para operar, o jogo encerra.

### 🏬 Loja e Economia (`LOJA.h` & `ESTOQUE.h`)
- **Gestão de Inventário:** Controle de 14 ingredientes com IDs únicos.
- **Mercado:** Sistema dinâmico de compra de insumos e venda de excedentes com fator de depreciação de preço.

### 📝 Histórico e Persistência (`HISTORICO.h`)
- **Arquivos:** Implementa funções de leitura e escrita em disco (`.txt`). O jogo é capaz de reconstruir a lista duplamente encadeada de histórico ao iniciar, permitindo a continuidade do progresso.

### 🎨 Interface Visual (`COLORS.h`)
- **Experiência do Usuário (UX):** Utiliza sequências de escape ANSI para colorir o terminal. Isso facilita a distinção visual entre avisos de erro (vermelho), lucros (verde), pedidos (magenta) e menus (ciano).

---

## 🚀 Como Executar

1.  **Pré-requisitos:** Possuir um compilador C (ex: GCC).
2.  **Compilação:**
    ```bash
    gcc main.c -o PatoBurger
    ```
3.  **Execução:**
    ```bash
    ./PatoBurger
    ```

---

## 👥 Desenvolvedores 
* Grupo Arthur Cunha - Arthur Andrade Cunha

---
*Projeto desenvolvido para a disciplina de Análise de Estrutura de Dados - Curso de Engenharia da Computação.*
# projeto-pato-hamburguer
