//
// Created by guilherme on 11/17/18.
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

	imprimeGrafo(grafo);
	k = getKGrafo(grafo);
	kOriginal = getKGrafo(grafo);
	printf("Graph %d -> Physical Registers: %d\n",getIdGrafo(grafo),kOriginal);
	printf("----------------------------------------\n");
	printf("----------------------------------------\n");

	while(k>1){
		printf("K = %d\n\n",k);
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
		k=0;
		if(k==1)
			printf("----------------------------------------\n");
		setKGrafo(grafo, k);
	}

	while(kOriginal>1){
		if(vetor[kOriginal]==-1){
			printf("Graph %d -> K = %d: SPILL",getIdGrafo(grafo),kOriginal);
		}
		else
		{
			printf("Graph %d -> K = %d: Successful Allocation",getIdGrafo(grafo), kOriginal);
		}
		kOriginal=0;
		if(kOriginal!=1)
			printf("\n");
	}
	
	
}

Vertice potencialSpill(Grafo grafo);

Pilha simplify(Grafo gra){
	int i, removeu, k, ps;
	Pilha pilha;
	Vertice vertice, verticePS;
	Lista vertices;
	Posic item;
	pilha = createPilha();
	k = getKGrafo(gra);

	vertices = getVertices(gra);

	removeu = 1;
	while(removeu){
		removeu = 0;
		// vertice = getVerticeMenorGrau(gra);
		// if(vertice != NULL){
		// 	if(verificaVerticeValido(gra, vertice)){
		// 		removeVertice(gra, vertice);
		// 		push(pilha,vertice);
		// 		printf("Push: %d\n",getIdVertice(gra, vertice));
		// 		removeu = 1;
		// 	}
		// }
		// if(!removeu && existeVerticeValido(gra)){
		// 	verticePS = potencialSpill(gra);
		// 	removeVertice(gra, verticePS);
		// 	push(pilha, verticePS);
		// 	printf("Push: %d *\n",getIdVertice(gra, verticePS));
		// 	removeu = 1;
		// }
		item = getFirst(vertices);
		while(item != NULL){
			vertice = get(vertices,item);
			if(getGrauVertice(gra, vertice) < k && verificaVerticeValido(gra,vertice)){
				removeVertice(gra, vertice);
				push(pilha,vertice);
				printf("Push: %d\n",getIdVertice(gra, vertice));
				removeu = 1;
			}
			item = getNext(vertices,item);
		}
		if(!removeu && existeVerticeValido(gra)){
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
	Vertice vertice, aux;
	Lista vList;
	Posic item;
	vertice = buscaVertice(gra,0);
	maior = getGrauVertice(gra,vertice);


	vList = getVertices(gra);
	item = getFirst(vList);
	while(item != NULL){
		aux = get(vList,item);
		if(getGrauVertice(gra,aux) > maior){
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
	k = getKGrafo(grafo);

	// printf("TAMANHO DA PILHA NO ASSIGN: %d\n", getSizePilha(pilha));
	item = pop(pilha);

	while(item != NULL){
		v = item;
		addVertice(grafo, getIdVertice(grafo,v));
		// imprimeGrafo(grafo);
		color = verificaCoresVertice(grafo, v);
		// printf("COLOR: %d\n", color);
		if(color == -1){
			printf("Pop %d -> NO COLOR AVAILABLE\n",getIdVertice(grafo, v));
			return -1;
		}
		pintaVertice(grafo, v, color);
		item = pop(pilha);
		printf("Pop: %d -> %d\n",getIdVertice(grafo, v),getColorVertice(grafo,v));
	}


	return 1;
}
