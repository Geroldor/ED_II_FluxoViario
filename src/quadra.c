
#include "quadra.h"

typedef struct quadra{
    float x, y, w, h;
    char cep[20];
} quadra;

Quadra criarQuadra(float x, float y, float w, float h, char* cep){
    quadra* q = (quadra*) malloc(sizeof(quadra));
    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;
    strcpy(q->cep, cep);
    return q;
}

void setQuadraX(quadra* q, float x){
    q->x = x;
}

void setQuadraY(quadra* q, float y){
    q->y = y;
}

void setQuadraW(quadra* q, float w){
    q->w = w;
}

void setQuadraH(quadra* q, float h){
    q->h = h;
}

void setQuadraCep(quadra* q, char* cep){
    strcpy(q->cep, cep);
}

float getQuadraX(quadra* q){
    return q->x;
}

float getQuadraY(quadra* q){
    return q->y;
}

float getQuadraW(quadra* q){
    return q->w;
}

float getQuadraH(quadra* q){
    return q->h;
}

char* getQuadraCep(quadra* q){
    return q->cep;
}
