#ifndef PILHA_h
#define PILHA_h
#include <stdio.h>
#define MAX 100

typedef int 
    tp_item;


typedef struct {
    int topo;
    tp_item item[MAX];
} tp_pilha;

void inicializaPilha (tp_pilha *p) {
    p -> topo = -1;
}

int pilhaVazia (tp_pilha *p) {
    if (p -> topo == -1) return 1;
    return 0;
}

int pilhaCheia (tp_pilha *p) {
    if (p -> topo == MAX - 1) return 1;
    return 0;
}

int push (tp_pilha *p, tp_item e) {
    if (pilhaCheia(p) == 1) return 0;
    p->topo++;
    p->item[p->topo] = e;
    return 1;
}

int pop (tp_pilha *p, tp_item *e) {
    if (pilhaVazia(p) == 1) return 0;
    *e=p->item[p->topo];
    p->topo--;
    return 1;
}

int top (tp_pilha *p, tp_item *e) {
    if (pilhaVazia(p) == 1) return 0;
    *e=p->item[p->topo];
    return 1;
}

void imprimePilha(tp_pilha p) {
    tp_item e;
    printf("\n");
    while (!pilhaVazia(&p)) {
        pop(&p, &e);
        printf("%d ", e);
    }
}

int alturaPilha (tp_pilha *p) {
    return p-> topo+1;
}

#endif