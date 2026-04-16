#ifndef LISTADE_H
#define LISTADE_H

#include <stdlib.h>
#include <stdio.h>

//funcao da listade que assume ponteiros como tp_item
typedef void* tp_item_de; 

typedef struct tp_no_aux {
    tp_item_de info; 
    struct tp_no_aux *ant;
    struct tp_no_aux *prox;
} tp_no;

typedef struct {
    tp_no *ini;
    tp_no *fim;
} tp_listade;

tp_listade * inicializaListade() {
    tp_listade *lista=(tp_listade*) malloc(sizeof(tp_listade));
    if (lista == NULL) {
        printf("Falha ao alocar memória para a lista.\n");
        return NULL;
    }
    lista->ini =NULL;
    lista->fim =NULL; 
    
    return lista;
}

int listadeVazia (tp_listade *lista){
    if ( (lista->ini == NULL) ) return 1;
    return 0;
}

tp_no * alocaListade() { 
    tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
    return pt;
}

int insereListadeNoFim (tp_listade *lista, tp_item_de e){ 
    tp_no *novo; 
    novo=alocaListade();
    if (!novo) return 0;
    novo->info = e; 
    novo->prox = NULL; 
    if ( listadeVazia(lista) ){ 
        novo->ant = NULL; 
        lista->ini = lista->fim = novo;
    } 
    else { 
        novo->ant = lista->fim; 
        lista->fim->prox = novo;
        lista->fim = novo;
    } 
    return 1; 
} 

int removeListade (tp_listade *lista, tp_item_de e){ 
    tp_no *atu;
    atu = lista->ini;
    while ( (atu != NULL) && (atu->info != e) ) { 
        atu=atu->prox;}
    if ( atu == NULL) return 0; 
    if (lista->ini == lista->fim) { 
        lista->ini = lista->fim = NULL; }
    else { 
        if (lista->ini == atu) { 
            lista->ini = atu->prox;
            atu->prox->ant = NULL;
        } 
        else {
            if (lista->fim == atu) { 
                lista->fim = atu->ant;
                atu->ant->prox = NULL; 
            }
            else {
                atu->prox->ant = atu->ant; 
                atu->ant->prox = atu->prox;
            } 
        }
    } 
    free(atu); 
    return 1; 
}

void imprimeListade(tp_listade *lista, int ordem) {
	if (lista==NULL)
		printf("Lista não inicializada");
	else {
        tp_no *atu; 
        switch (ordem) {
            case 1: atu = lista->ini;
                printf("Imprimindo endereços de memória: ");
                while (atu != NULL) {
                    printf("%p ", atu->info); 
                    atu=atu->prox; 
                }
                break; 
            case 2: atu = lista->fim;
                printf("Imprimindo endereços de memória: ");
                while (atu != NULL) {
                    printf("%p ", atu->info);
                    atu=atu->ant; 
                }
                break; 
            default: printf("codigo invalido"); 
        }
	}
    printf("\n");
}

tp_no * buscaListade (tp_listade *lista, tp_item_de e){ 
    tp_no *atu;
    atu = lista->ini;
    while ( (atu != NULL) && (atu->info != e) ) { 
        atu=atu->prox;}
    return atu;
} 

tp_listade * DestroiListade (tp_listade *lista){ 
    tp_no *atu;
    atu = lista->ini;
    while (atu != NULL) { 
        lista->ini = atu->prox;
        free(atu);
        atu=lista->ini;
	}
    free(lista);
    return NULL;
} 

#endif