//
// Created by eduardo on 11/17/18.
//

#include "Alocador.h"


int alocar(Grafo grafo){
	int cond,k,i,kOriginal;
	int vetor[getKGrafo(grafo)];
	Pilha pilha;
	Lista teste;
	cond = 0;

	// teste = getVertices(grafo);
	// printf("CHEGOU  EM ALOCAR, GRAFO: %d num. de vertices: %d\n", getIdGrafo(grafo), length(teste));

	// imprimeGrafo(grafo);
	k = getKGrafo(grafo);
	kOriginal = getKGrafo(grafo);
	printf("Graph %d -> Physical Registers: %d\n",getIdGrafo(grafo),kOriginal);
	printf("----------------------------------------\n");
	printf("----------------------------------------\n");
	while(k>1){
		printf("K = %d\n\n",k);
		setKColor(grafo,k);
		pilha = simplify(grafo);
		// printf("TAMANHO DA PILHA NO ALOCAR: %d\n", getSizePilha(pilha));
		cond = assign(grafo, pilha);
		printf("----------------------------------------\n");
		if(cond == -1){
			vetor[k] = -1;
		}	
		else{
			vetor[k] = 1;
		}
		k--;
		if(k==1)
			printf("----------------------------------------\n");
		setaValid(grafo);
		// setKGrafo(grafo, k);
	}

	while(kOriginal>1){
		if(vetor[kOriginal]==-1){
			if(kOriginal > 9)
				printf("Graph %d -> K = %d: SPILL",getIdGrafo(grafo),kOriginal);
			else
				printf("Graph %d -> K =  %d: SPILL",getIdGrafo(grafo),kOriginal);
		}
		else
		{
			if(kOriginal > 9)
				printf("Graph %d -> K = %d: Successful Allocation",getIdGrafo(grafo), kOriginal);
			else
				printf("Graph %d -> K =  %d: Successful Allocation",getIdGrafo(grafo), kOriginal);
		}
		kOriginal--;
		if(kOriginal!=1)
			printf("\n");
	}
	
	
}

Vertice potencialSpill(Grafo grafo);

Pilha simplify(Grafo gra){
	int removeu;
	Pilha pilha;
	Vertice vertice, verticePS;
	Lista vertices;
	Posic item;
	pilha = createPilha();

	removeu = 1;
	while(removeu){
		removeu = 0;
		vertice = getVerticeMenorGrau(gra);
		if(vertice != NULL){
			// printf("Grau: %d ",getGrauVertice(gra, vertice));
			removeVertice(gra, vertice);
			push(pilha, vertice);
			printf("Push: %d\n",getIdVertice(gra, vertice));
			removeu = 1;
		}
		if(!removeu && existeVerticeValidoMenorGrau(gra)){
			verticePS = potencialSpill(gra);
			removeVertice(gra, verticePS);
			push(pilha, verticePS);
			printf("Push: %d *\n",getIdVertice(gra, verticePS));
			removeu = 1;
		}
	}

	// printf("TAMANHO DA PILHA NO SIMPLIFY: %d\n", getSizePilha(pilha));
	return pilha;
}


Vertice potencialSpill(Grafo gra){
	int i, maior;
	Grafo g = (Grafo*)gra;
	Vertice vertice, aux;
	Lista vList;
	Posic item;
	vList = getVertices(gra);
	vertice = getFirst(vList);
	item = getFirst(vList);
	maior = getGrauVertice(gra,get(vList, item));

	while(item != NULL){
		aux = get(vList,item);
		if(getGrauVertice(gra,aux) > maior && getIdVertice(gra, aux) > getKGrafo(gra) && getValid(gra, aux)){
			maior = getGrauVertice(gra,aux);
			vertice = aux;
		}
		item = getNext(vList,item);
	}

	return vertice;
}

int assign(Grafo grafo, Pilha pilha){
	Posic item;
	int k, color, x;
	Vertice v;
	k = getKColor(grafo);
	// printf("TAMANHO DA PILHA NO ASSIGN: %d\n", getSizePilha(pilha));
	item = pop(pilha);
	while(item != NULL){
		v = item;
		addVertice(grafo, getIdVertice(grafo,v),1);
		// imprimeGrafo(grafo);
		color = verificaCoresVertice(grafo, v);
		// printf("COLOR: %d\n", color);
		if(color == -1){
			printf("Pop: %d -> NO COLOR AVAILABLE\n",getIdVertice(grafo, v));
			item = pop(pilha);
			while(item != NULL){
				v = item;
				addVertice(grafo, getIdVertice(grafo, v),1);
				item = pop(pilha);
			}
			return -1;
		}
		pintaVertice(grafo, v, color);
		item = pop(pilha);
		printf("Pop: %d -> %d\n",getIdVertice(grafo, v),getColorVertice(grafo,v));
	}


	return 1;
}
