/*  Neha Chawla
	nechawla
	pa5
	GraphTest.c
*/

#define UNDEF -1
#define NIL -9

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){

	Graph G = newGraph(6);
	List L = newList();
	List N = newList();
	
	for(int i = 1; i < getOrder(G); i++){
		append(L, i);
	}
	
	addEdge(G, 1, 4);
    addEdge(G, 10, 25);
    addEdge(G, 2, 40);
    addEdge(G, 3, 4);
    addEdge(G, 5, 6);
    addEdge(G, 7, 8);
    addEdge(G, 9, 10);
    addEdge(G, 29, 10);
    addEdge(G, 30, 10);
	
	addArc(G, 1, 4);
    addArc(G, 10, 25);
    addArc(G, 2, 40);
    addArc(G, 3, 4);
    addArc(G, 5, 6);
    addArc(G, 7, 8);
    addArc(G, 9, 10);
    addArc(G, 29, 10);
    addArc(G, 30, 10);
    
    fprintf(stdout, "getParent(1):%d", getParent(G, 5));
    printf("\n");
    fprintf(stdout, "getParent(2):%d", getParent(G, 29));
    printf("\n");
    fprintf(stdout, "getParent(3):%d", getParent(G, 30));
    printf("\n");

	printGraph(stdout, G);
	printf("Order: %d\n", getOrder(G));
	printf("Size: %d\n", getSize(G));
	printf("Parent: %d\n", getParent(G, 3));
	printf("Discover: %d\n", getDiscover(G, 3));
	printf("Finish: %d\n", getFinish(G, 3));
	DFS(G, L);
	
	freeList(&N);
	freeGraph(&G);
	freeList(&L);
}