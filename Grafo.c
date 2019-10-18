#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#include "Pilha.h"



typedef struct _vertice{
  Lista arestas;
  int id;
  int grau;
  int valid;
  int color;
}vertice;

typedef struct _grafo{
  int k;
  int id;
  Lista vertices;
}grafo;

Lista getVertices(Grafo gra){
  grafo *g = (grafo*) gra;

  return g->vertices;
}

Grafo criaGrafo(int colors, int id){
  int i;
  grafo *g = (grafo*) malloc(sizeof(grafo));
  vertice *v = NULL;
  g->vertices = createList();
  for(i = 0; i < colors; i++){
    v = (vertice*) malloc(sizeof(vertice));
    v->arestas = createList();
    v->id = i;
    v->grau = 0;
    v->color = -1;
    v->valid = 1;
    insert(g->vertices,v);
  }
  g->k = colors;
  g->id = id;
  return g;
}

void setKGrafo(Grafo gra, int newK){
  grafo *g = (grafo*) gra;

  g->k = newK;
}


int getIdGrafo(Grafo gra){
  grafo *g = (grafo*) gra;

  return g->id;
}

int addVertice(Grafo gra, int a){
  grafo *g = (grafo*) gra;
  vertice *v = NULL;

  if(verificaVerticeExistencia(gra,a)){
    v = (vertice*)buscaVertice(gra,a);
    v->valid = 1;
    return 0;
  }

  printf("B");
  v = (vertice*) malloc(sizeof(vertice));

  v->arestas = createList();
  v->id = a;
  v->grau = 0;
  v->valid = 1;
  v->color = -1;

  insert(g->vertices,v);
}

int verificaVerticeExistencia(Grafo gra, int a){
  grafo *g = (grafo*) gra;
  vertice *v;
  Posic item;


  item = getFirst(g->vertices);
  while(item != NULL){
    v = (vertice*) get(g->vertices,item);
    if(v->id == a)
      return 1;
    item = getNext(g->vertices, item);
  }

  return 0;
}

int verificaArestaExistencia(Grafo gra, int a, int b){
  grafo *g = (grafo*) gra;
  vertice *v = NULL, *v2;
  int *aresta = NULL;
  Posic item, item2;


  item = getFirst(g->vertices);
  // printf("\n\n\n========== VERIFICANDO EXISTENCIA DE ARESTA ===========\n");
  while(item != NULL){
    v = (vertice*) get(g->vertices, item);
    // printf("v->id: %d\n", v->id);
    if(v->id == a){
      item2 = getFirst(v->arestas);
      while(item2 != NULL){
        aresta = (int*) get(v->arestas, item2);
        v2 = (vertice*) aresta;
        // printf("v2->id: %d B: %d", v2->id, b);
        if(v2->id == b)
          return 1;
        item2 = getNext(v->arestas,item2);
        }
        return 0;
    }
    item = getNext(g->vertices, item);
  }
  return 0;

}

int addAresta(Grafo gra, int a, int b){
  // printf("Add Aresta %d %d \n",a,b);
	int *A, *B;
	Lista arestas, vertices;
  vertice *v, *vA = NULL, *vB = NULL;
	Posic item;
  grafo *g;
  g = (grafo*) gra;

  // printf("tentando ligar vertice %d com %d\n", a, b);
  if(verificaArestaExistencia(gra,a,b) || a == b){
    // printf("Deu ruim ligando %d ao %d\n", a, b);
    return 0;
  }

  A = (int*) malloc(sizeof(int));
  B = (int*) malloc(sizeof(int));

  *A = a;
  *B = b;
  item = getFirst(g->vertices);
  while(item != NULL){

    v = (vertice*) get(g->vertices, item);

    if(v->id == a || v->id == b){

      if(v->id == a){
        vA = v;
      }
      else{
        vB = v;
      }

    }


    item = getNext(g->vertices, item);
  }
  if(vA == NULL || vB == NULL)
    return 0;
  // antes = length(vB->arestas);
  // Inserindo vertices
  // printf("Ligando vertice %d com %d\n", vA->id, vB->id);
  insert(vA->arestas,vB);
  insert(vB->arestas,vA);
  //Aumentando contador de grau;
  vA->grau = vA->grau + 1;
  vB->grau = vB->grau + 1;
  // printf("INSERIU %d AO %d tamanho geral %d tamanho arestas vA %d tamanho arestas vB %d\n", vA->id, vB->id, length(g->vertices), length(vA->arestas),  length(vB->arestas));
  return 1;
}


Vertice buscaVertice(Grafo gra, int a){
  grafo *g = (grafo*) gra;
  Posic item;
  vertice *v;

  item = getFirst(g->vertices);
  while(item != NULL){
    v = (vertice*) get(g->vertices,item);
    if(v->id == a){
      return v;
    }
    item = getNext(g->vertices, item);
  }

  return NULL;
}

void removeVertice(Grafo gra, Vertice a){
  grafo *g = NULL;
  vertice *v = NULL, *v2;
  int cond;
  Posic item;

  g = (grafo*) gra;
  v = (vertice*) a;

  item = getFirst(v->arestas);

  while(item != NULL){
    v2 = (vertice*) get(v->arestas, item);
    v2->grau = v2->grau - 1;
    item = getNext(v->arestas,item);
  }

  v->valid = 0;

}

int imprimeGrafo(Grafo gra){
  grafo *g = (grafo*) gra;
  Lista vertices = NULL;
  Lista arestas = NULL;
  vertice *v = NULL;
  vertice *v2 = NULL;
  Posic item = NULL;
  Posic item2 = NULL;

  printf("\n\n>>>>>>> COMECANDO IMPRESSAO DE GRAFO <<<<<<<<<<\n");
  vertices = g->vertices;
  item = getFirst(vertices);
  while(item != NULL){
    v = (vertice*) get(vertices,item);

    printf("Vertice %d valid? %d:", v->id, v->valid);
    arestas = v->arestas;
    item2 = getFirst(arestas);
    while(item2 != NULL){
      v2 = (vertice*) get(arestas,item2);

      printf(" ->%d", v2->id);

      item2 = getNext(arestas,item2);
    }
    printf("   grau: %d\n", v->grau);

    item = getNext(vertices,item);
  }


}


int getGrauVertice(Grafo gra, Vertice x){
  vertice *v = (vertice*) x;
  // printf("V->grau: %d\n",v->grau);
  return v->grau;

}
//
void destroiGrafo(Grafo gra){
  grafo *g = (grafo*) gra;
  vertice *v;
  Lista vertices, arestas;
  Posic item;

  vertices = g->vertices;
  item = getFirst(vertices);

  while(item != NULL){
    v = (vertice*) get(g->vertices, item);
    liberaLista(v->arestas);
    free(v);
    item = getNext(g->vertices, item);
  }
  free(g->vertices);

  free(g);



}

int getSizeGrafo(Grafo gra){
	grafo *g = (grafo*) gra;
  vertice *v = NULL;
  Posic item;
  int cont;


  cont = 0;
  item = getFirst(g->vertices);
  while(item != NULL){
    v = (vertice*) get(g->vertices, item);
    if(v->valid)
      cont++;
    item = getNext(g->vertices, item);
  }
  return cont;
}

int getKGrafo(Grafo gra){
	grafo *g = (grafo*) gra;
	return g->k;
}

int verificaVerticeValido(Grafo gra, Vertice vert){
	vertice *v = (vertice*) vert;

	return v->valid;
}

int existeVerticeValido(Grafo gra){

	grafo *g = (grafo*) gra;
  vertice *v = NULL;
  Posic item;

  item = getFirst(g->vertices);
  while(item != NULL){
    v = (vertice*) get(g->vertices, item);
    if(v->valid)
      return 1;

    item = getNext(g->vertices, item);
  }

	return 0;

}



int verificaCoresVertice(Grafo gra, Vertice vert){
	int *disp, i, k;
  grafo *g = (grafo*) gra;
  vertice *v = (vertice*) vert, *vAux = NULL;
  Posic item;

  k = g->k;
  disp = (int*) malloc(sizeof(int)*k);
  //Seta todos como disponiveis
  for(i = 0; i < k; i++)
    disp[i] = 1;

  item = getFirst(v->arestas);
  while(item != NULL){
    vAux = (vertice*) get(v->arestas,item);
    if(vAux->id < k){
      disp[vAux->id] = 0;
    }
    else{
      if(vAux->valid && vAux->color != -1){
        disp[vAux->color] = 0;
      }
    }


    item = getNext(v->arestas, item);
  }

  for(i = 0; i < k; i++){
    if(disp[i])
      return i;
  }

	return -1;
}

int pintaVertice(Grafo gra, Vertice vert, int color){
	grafo *g = (grafo*) gra;
  vertice *v = (vertice*) vert;

  if(!v->valid || color >= g->k)
    return -1;

  v->color = color;
  // printf("Pintando vertice %d com a cor %d\n", v->id, v->color);
	return 1;
}

int getColorVertice(Grafo gra, Vertice vert){
  grafo *g = (grafo*) gra;
  vertice *v = (vertice*) vert;

  return v->color;
}

int getIdVertice(Grafo gra, Vertice vert){
  vertice *v = (vertice*) vert;

  return v->id;
}

Vertice getVerticeMenorGrau(Grafo gra){
  grafo *g = (grafo*)gra;
  Lista vertices;
  Posic item;
  vertice *v,*vAux;
  int num,menorGrau;
  vertices = g->vertices;

  item = getFirst(g->vertices);
  v = (vertice*) get(g->vertices,item);
  menorGrau = v->grau;
  vAux = v;
  item = getNext(g->vertices, item);

  while(item != NULL){
    v = (vertice*) get(g->vertices,item);
    if(v->valid){
      if(v->grau < g->k){
        if(v->grau < menorGrau){
          vAux = v;
          menorGrau = v->grau;
        }
        if(v->grau == menorGrau){
          if(v->id < vAux->id){
            vAux = v;
            menorGrau = v->grau;
          }
        }
      }
    }
    
    item = getNext(g->vertices, item);
  }
  if(vAux->valid && menorGrau < g->k){
    printf("V");
    vAux->valid = 0;
    return vAux;
  }
  else
    return NULL;

}
/*
 * Codigo antes de mudar o removeEdgeint *n = NULL;

  grafo *g;
  Lista vertices;
  Posic item, item2;
  g = (grafo*) gra;

 vertices = g->vertices[*a].arestas;


item = getFirst(vertices);
while(length(vertices) > 0){
*n = (int*) get(vertices,item);
printf("Aresta referencia a: %d", *n);

item2 = getFirst(g->vertices[*n].arestas);
//Removendo referencias da primeira aresta
while(length(g->vertices[*n].arestas) > 0){
//Se o no referenciado for igual ao no passado
if((int)get(g->vertices[*n].arestas, item2) == *a){

}

}
}
*/
