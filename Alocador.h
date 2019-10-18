//
// Created by guilherme on 11/17/18.
//

#ifndef T3_COMPILADORES_ALOCADOR_H
#define T3_COMPILADORES_ALOCADOR_H
#include "Grafo.h"
#include "Pilha.h"

int alocar(Grafo grafo);
/*
 * Se retornar 1, deu certo
 * Se retornar 0, deu SPILL
 */

Pilha simplify(Grafo grafo);

//int potencialSpill(Grafo grafo);

int assign(Grafo grafo, Pilha pilha);
/*
 * Se Assign retornar -1, deu SPILL
 * se Assign retornar 1, nao deu SPILL
 */
#endif //T3_COMPILADORES_ALOCADOR_H
