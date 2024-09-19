#include "prio.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _PQNode {
    Chave chave;
    PInfo info;
    int prioridade;
    struct _PQNode *prox;
} PQNode;

typedef struct _PQueue {
    PQNode *inicio;
    PQNode *fim;
} Pqueue;

PQueue createPQ() {
    Pqueue *pq = malloc(sizeof(struct _PQueue));
    pq->inicio = NULL;
    pq->fim = NULL;
    return pq;
}

bool emptyPQ(PQueue pq) {
    Pqueue *p = pq;
    return p->inicio == NULL;
}

void insertPQ(PQueue pq, Chave ch, PInfo info, int prio) {
    Pqueue *p = pq;
    PQNode *novo = malloc(sizeof(struct _PQNode));
    novo->chave = ch;
    novo->info = info;
    novo->prioridade = prio;
    novo->prox = NULL;
    if (emptyPQ(pq)) {
        p->inicio = novo;
        p->fim = novo;
    } else {
        PQNode *atual = p->inicio;
        PQNode *anterior = NULL;
        while (atual != NULL && atual->prioridade > prio) {
            anterior = atual;
            atual = atual->prox;
        }
        if (anterior == NULL) {
            novo->prox = p->inicio;
            p->inicio = novo;
        } else {
            anterior->prox = novo;
            novo->prox = atual;
            if (atual == NULL) {
                p->fim = novo;
            }
        }
    }
}

bool existsPQ(PQueue pq, Chave ch) {
    Pqueue *p = pq;
    PQNode *atual = p->inicio;
    while (atual != NULL && atual->chave != ch) {
        atual = atual->prox;
    }
    return atual != NULL;
}

int priorityPQ(PQueue pq, Chave ch) {
    Pqueue *p = pq;
    PQNode *atual = p->inicio;
    while (atual != NULL && atual->chave != ch) {
        atual = atual->prox;
    }
    return atual->prioridade;
}

PInfo removeMaximunPQ(PQueue pq, int *prio) {
    Pqueue *p = pq;
    if (emptyPQ(pq)) {
        return NULL;
    }
    PQNode *removido = p->inicio;
    p->inicio = p->inicio->prox;
    if (p->inicio == NULL) {
        p->fim = NULL;
    }
    *prio = removido->prioridade;
    PInfo info = removido->info;
    free(removido);
    return info;
}

PInfo getMaximumPQ(PQueue pq, int *prio) {
    Pqueue *p = pq;
    if (emptyPQ(pq)) {
        return NULL;
    }
    *prio = p->inicio->prioridade;
    return p->inicio->info;
}

void increasePrioPQ(PQueue pq, Chave ch, int dp) {
    Pqueue *p = pq;
    PQNode *atual = p->inicio;
    while (atual != NULL && atual->chave != ch) {
        atual = atual->prox;
    }
    atual->prioridade += dp;
}

void decreasePrioPQ(PQueue pq, Chave ch, int dp) {
    Pqueue *p = pq;
    PQNode *atual = p->inicio;
    while (atual != NULL && atual->chave != ch) {
        atual = atual->prox;
    }
    atual->prioridade -= dp;
}