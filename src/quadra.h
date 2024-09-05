#ifndef QUADRA_h
#define QUADRA_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Quadra é uma forma que estrutura uma área retangular em um mapa de cidade.
 * A quadra possui coordenadas x e y, altura h, largura w e um CEP
 */

typedef void* Quadra;


/**
 * @brief Cria uma nova quadra
 * 
 * @param x coordenada x
 * @param y coordenada y
 * @param w largura
 * @param h altura
 * @param cep CEP da quadra
 * @return Quadra Ponteiro para a quadra criada
 */
Quadra criarQuadra(float x, float y, float w, float h, char* cep);

/**
 * @brief Define a coordenada x da quadra
 * 
 * @param q Quadra
 * @param x coordenada x
 */
void setQuadraX(Quadra q, float x);

/**
 * @brief Define a coordenada y da quadra
 * 
 * @param q Quadra
 * @param y coordenada y
 */
void setQuadraY(Quadra q, float y);

/**
 * @brief Define a largura da quadra
 * 
 * @param q Quadra
 * @param w largura
 */
void setQuadraW(Quadra q, float w);

/**
 * @brief Define a altura da quadra
 * 
 * @param q Quadra
 * @param h altura
 */
void setQuadraH(Quadra q, float h);

/**
 * @brief Define o CEP da quadra
 * 
 * @param q Quadra
 * @param cep CEP
 */
void setQuadraCep(Quadra q, char* cep);

/**
 * @brief Retorna a coordenada x da quadra
 * 
 * @param q Quadra
 * @return float coordenada x
 */
float getQuadraX(Quadra q);

/**
 * @brief Retorna a coordenada y da quadra
 * 
 * @param q Quadra
 * @return float coordenada y
 */
float getQuadraY(Quadra q);

/**
 * @brief Retorna a largura da quadra
 * 
 * @param q Quadra
 * @return float largura
 */
float getQuadraW(Quadra q);

/**
 * @brief Retorna a altura da quadra
 * 
 * @param q Quadra
 * @return float altura
 */
float getQuadraH(Quadra q);

/**
 * @brief Retorna o CEP da quadra
 * 
 * @param q Quadra
 * @return char* CEP
 */
char* getQuadraCep(Quadra q);

#endif