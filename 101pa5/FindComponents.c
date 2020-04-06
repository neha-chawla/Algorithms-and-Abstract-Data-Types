/*  Neha Chawla
	nechawla
	pa5
	FindComponents.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
#include <string.h>

int main(int argc, char* argv[]){
	FILE *inFile;
    FILE *outFile;
    List S = newList();
	char* in[200];
	char ln[200];
	int c = sizeof(ln);
	char *strdup(const char *s); 
	int i;

	if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

	inFile = fopen(argv[1], "r"); 
	outFile = fopen(argv[2], "w");

	if(inFile == NULL || outFile == NULL){
        printf("Unable to open file\n");
        exit(1);
    }
    
	for(int i = 0; fgets(ln, c, inFile) != NULL; i++){
		in[i] = strdup(ln);
	}

	Graph G = newGraph(atoi(in[0]));
	int a = getOrder(G);
	char* firstS;
	char* secondS;
	
	int indivSplit, indivSplitN;

	for(i = 1; i != -1; i++){
		firstS = strtok(in[i], " ");
		indivSplit = atol(firstS);
		secondS = strtok(NULL, " ");
		indivSplitN = atol(secondS);
		if(indivSplit == 0){
			if(indivSplitN == 0){
				break;
			}
		}
		addArc(G, indivSplit, indivSplitN);
	}

	for(i = 1; i < a; i++){
		append(S, i);
	}

	fprintf(outFile, "Adjacency list representation of G:\n");
	printGraph(outFile, G);

	DFS(G, S);
	Graph t = transpose(G); 
	DFS(t, S); 
	int e = 0;
	moveFront(S);
	int d = length(S);
	
	for(int i = 0; i < d; i++){ 
		if(t->parents[get(S)] == NIL){ 
			e++;
		}
		moveNext(S);
	}
	i = 0;
	fprintf(outFile, "G contains %d strongly connected components:\n", e); 
	
	moveBack(S);
	while(i < e){
		List Q = newList();
		if(i > 0){
			movePrev(S);
		}
		if(t->parents[get(S)] != NIL){
			while(t->parents[get(S)] != NIL){
				prepend(Q, get(S));
				movePrev(S);
			}
		} 
		prepend(Q, get(S));
		fprintf(outFile, "Component %d: ", i + 1);
		printList(outFile, Q);
		fprintf(outFile, "\n");
		freeList(&Q);
		i++;
	}

	freeList(&S);
	freeGraph(&G);
	freeGraph(&t);
	
	fclose(inFile);
	fclose(outFile);
	return(0);
}