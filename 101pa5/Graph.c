/*  Neha Chawla
	nechawla
	pa5
	Graph.c
*/

#define UNDEF -1
#define NIL -2

#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>
#include "List.h"

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj)); 
	G->adj = calloc(n+1, sizeof(List));
    G->colors = calloc(n+1, sizeof(int));
    G->parents = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));
	G->distance = malloc(sizeof(int)*(n + 1));
	for(int i = 1; i < n + 1; i++){ 
		G->adj[i] = newList();
		G->colors[i] = 'W';
		G->parents[i] = NIL;
		G->distance[i] = NIL;
		G->discover[i] = NIL;
		G->finish[i] = NIL;
		G->order = n + 1;
		G->size = 0;
	}
	return(G);
}

void freeGraph(Graph *pG) {
	if(pG != NULL && *pG != NULL) {
		for(int i = 1; i < (*pG)->order; i++) {
			freeList(&((*pG)->adj[i])); 
		}
		free((*pG)->adj);
		free((*pG)->colors);
		free((*pG)->parents);
		free((*pG)->distance);
		free((*pG)->discover);
		free((*pG)->finish);
		(*pG)->order = 0;
		(*pG)->size = 0;
		free(*pG);
		*pG = NULL;
	}
}

int getOrder(Graph G){
   if(G == NULL) {
      printf("Error");
      exit(1);
   }
   return G->order;
}

int getSize(Graph G){
   if(G == NULL) {
      printf("Error");
      exit(1);
   }
   return G->size;
}

int getParent(Graph G, int u){
   if(G == NULL) {
      printf("Error");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Error");
      exit(1);
   }
   return G->parents[u];
}


int getDiscover(Graph G, int u){ 
    if(G == NULL){
        printf("Error");
        exit(1);
    }
	if(G->discover[u] > 0){
		return G->discover[u];
	} 
	else{
		printf("Error");
		return(UNDEF);
	}
}

int getFinish(Graph G, int u) {
	if(G == NULL){
        printf("Error");
        exit(1);
    }
	if(G->finish[u] > 0){
		return G->finish[u];
	} 
	else{
		printf("Error");
		return(UNDEF);
	}
}

void addArc(Graph G, int u, int v){
	int i = 1;
    if(G == NULL){
       printf("Error");
       exit(1);
    }
    if(u < 1 || u > getOrder(G)){
       printf("Error");
       exit(1);
    }
    else if(v < 1 || v > getOrder(G)){
      printf("Error");
      exit(1);
    }
	if(u >= 1 && v >= 1 && u <= getOrder(G) && v <= getOrder(G)){
		if(length(G->adj[u]) <= 0) {
			append(G->adj[u], v);
		} 
		else{
			moveFront(G->adj[u]);
			while(get(G->adj[u]) < v && i < length(G->adj[u])){
				i++;
				moveNext(G->adj[u]);
			}
			if(i == length(G->adj[u]) && get(G->adj[u]) > v){
				insertBefore(G->adj[u], v);
			} 
			else if(i == length(G->adj[u]) && get(G->adj[u]) < v){
				insertAfter(G->adj[u], v);
			} 
			else if(get(G->adj[u]) > v){
				insertBefore(G->adj[u], v);
			}
		}
		G->size++;
	}
}

void addEdge(Graph G, int u, int v){
	if(G == NULL) {
       printf("Error");
       exit(1);
    }
    if(u < 1 || u > getOrder(G)){
       printf("Error");
       exit(1);
    }
    else if(v < 1 || v > getOrder(G)){
       printf("Error");
       exit(1);
    }
    else if(u == 0 || v == 0){
       return;
    }
	if(u >= 1 && v >= 1 && u <= getOrder(G) && v <= getOrder(G)){
		addArc(G, v, u);
		addArc(G, u, v);
		--G->size;
	}
}

void visit(Graph G, List S, int v, int* t, List Q){
	int i = 1;
	int j;
	int a = length(G->adj[v]);
	if(G == NULL){
       printf("Error");
       exit(1);
    }
	G->colors[v] = 1;
	G->discover[v] = ++(*t); 
	while(i <= a){
		List A = G->adj[v];
		moveFront(A);
		for(j = 0; j < i-1; j++){
			moveNext(A);
		}
		if(G->colors[get(A)] == 0){
			G->parents[get(A)] = v;
			visit(G, S, get(A), t, Q); 
		}
		i++;
	}
	prepend(Q, v);
	G->colors[v] = 2;
	G->finish[v] = ++(*t);
}

void DFS(Graph G, List S){
	int i;
	if(G == NULL) {
       printf("Error");
       exit(1);
    }
    i = 0;
	while(i < getOrder(G)-1){
		G->colors[i+1] = 0;
		G->parents[i+1] = NIL;
		i++;
	}
	int t = 0;
	i = 0;
	List Q = newList();
	moveFront(S);
	while(i < length(S)){
		if(G->colors[get(S)] == 0){
			visit(G, S, get(S), &t, Q);
		}
		moveNext(S);
		i++;
	}
	i = 0;
	clear(S);
	moveFront(Q);
	while(i < length(Q)){ 
		append(S, get(Q));
		moveNext(Q);
		i++;
	}
	freeList(&Q);
}

Graph transpose(Graph G){ 
	int a = getOrder(G);
	int i, j;
	Graph GTwo = newGraph(a - 1);
	if(G == NULL) {
       printf("Error");
       exit(1);
    }
	for(i = 0; i < a-1; i++){
		List adj = G->adj[i+1];
		if(length(adj) > 0) {
			moveFront(adj);
			for(j = 0; j < length(adj); j++){
				addArc(GTwo, get(adj), i+1); 
				moveNext(adj);
			}
		}
	}
	return(GTwo);
}

Graph copyGraph(Graph G){
	int a = getOrder(G);
	int i = 1;
	int j = 0;
	if(G == NULL){
        printf("Error");
        exit(1);
    }
	Graph copyGraph = newGraph(getOrder(G) - 1);
	while(i < a){
		List adj = G->adj[i];
		moveFront(adj);
		while(j < length(adj)){
			addArc(copyGraph, i, get(adj));
			j++;
			moveNext(adj);
		}
	}
	i++;
	return(copyGraph);
}

void printGraph(FILE* out, Graph G){
	Node N = NULL;
	int i = 1;
	if(G == NULL){
		printf("Error");
		exit(1);
	}
	while(i < getOrder(G)){
		fprintf(out, "%d: ", i);
		if(G->adj[i] != NULL){
			for(N = G->adj[i]->front; N != NULL; N = N->next){
				fprintf(out, "%d ", N->data);
			}
		}
		i++;
		fprintf(out, "\n");
	}
}