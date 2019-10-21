#ifndef GRAFO__H
#define GRAFO__H
#include "Lista.h"


typedef void* Grafo;
typedef void* Vertice;
typedef int Aresta;




/*
 * Grafo desenvolvido para alocar registradores,
 * nao deve ser utilizado para outros fins
 */


Lista getVertices(Grafo gra);
/*Retorna a lista de todos os vertices do grafo
*/

void setKColor(Grafo gra, int k);

int getKColor(Grafo gra);

int getValid(Grafo gra, Vertice v);

Grafo criaGrafo(int colors,int id);
/*Cria um grafo com numero de nos = colors, ou seja
  o numero maximo de cores aceitas
  e id = id
*/

void setKGrafo(Grafo gra, int newK);
/*Seta um novo valor de K para o grafo
*/
int getIdGrafo(Grafo gra);
/*Recebe um grafo.
Retorna o seu id;
*/

int addVertice(Grafo gra, int a, int verify);
/*Adiciona o vertice a ao grafo.
Se conseguir inserir, retorna 1
Caso ja exista um vertice com o mesmo id, retorna 0
*/

int verificaVerticeExistencia(Grafo gra, int a);
/*Verifica se vertice a ja existe no grafo.
Se ja existir, retorna 1
caso nao exista, retorna 0;
*/

int verificaArestaExistencia(Grafo gra, int a, int b);
/* Se ja houver uma aresta ligando o vertice a com b
retorna 1
se nao houver, retorna 0
*/

int addAresta(Grafo gra, int a, int b);
/*Conecta o vertice a com o vertibe b.
Se adicionou, retorna 1;
Se nao adiciou, seja por já existir ou acontecer um erro, retorna 0;
*/

Vertice buscaVertice(Grafo gra, int a);
/* Busca o vertice de id = a;
Caso encontre, retorna o vertice;
Caso contrario, retorna NULL;
*/



void removeVertice(Grafo gra, Vertice a);
/* Remove o vertice a do grafo e todas as arestas relacionadas
 * Na realidadade o proposito eh "fingir" remover, pois todos os
 * vertices removidos serao incluidos novamente.
*/

int getGrauVertice(Grafo g, Vertice v);
/*Retorna o grau do vertice v do grafo g
se v nao existir,
*/

void destroiGrafo(Grafo gra);
/*Libera a memoria do grafo.*/

int getSizeGrafo(Grafo grafo);
/*
 * retorna o numero de vertices do grafo
 */

int getKGrafo(Grafo grafo);
/* Retorna o atributo K do grafo
 *  que corresponde ao seu numero maximo de cores
 */

int verificaVerticeValido(Grafo gra, Vertice vert);
/*
 * Verifica se o vertice eh valido, ou seja, nao foi removido
 * Caso seja valido, retorna 1;
 */

int existeVerticeValido(Grafo gra);
/*
 * Se existe ao menos 1 vertice valido no grafo
 * retorna 1.
 * Caso contrario
 * retorna 0.
 */

int existeVerticeValidoMenorGrau(Grafo gra);
/*
 * Se existe ao menos 1 vertice valido no grafo e seu grau é menor que K
 * retorna 1.
 * Caso contrario
 * retorna 0.
 */

void setaValid(Grafo gra);


int pintaVertice(Grafo gra, Vertice v, int color);
/* Pinta o vertice v com a cor color
 *
 */

int getColorVertice(Grafo gra, Vertice vert);
/*Retorna a cor do vértice*/

int verificaCoresVertice(Grafo grafo, Vertice v);
/* Vertice se o vertice "v" pode ser pintado
*	Caso possa ser pintado, a funcao retorna a menor cor
*	no intervalo [0,k] que o vertice v pode ser pintado.
*	Caso nao possa ser pintado, retorna -1
*/



int imprimeGrafo(Grafo gra);
/*Imprime o vertices do grafo no intervalo [a,b].
 * Apenas para testes
 * */

int getIdVertice(Grafo gra, Vertice vert);
/* Retorna o ID do vertice vert
*/

Vertice getVerticeMenorGrau(Grafo gra);



#endif
