/*  Neha Chawla
	nechawla
	pa4
	GraphTest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
   List L = newList();
   List N = newList();
   Graph G = newGraph(50);
   
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
   
   BFS(G, 1);
   BFS(G, 29);
   BFS(G, 30);
   BFS(G, 40);
    
   fprintf(stdout, "getParent(1):%d", getParent(G, 5));
   printf("\n");
   fprintf(stdout, "getParent(2):%d", getParent(G, 29));
   printf("\n");
   fprintf(stdout, "getParent(3):%d", getParent(G, 30));
   printf("\n");

   fprintf(stdout,"getDist(1):%d",getDist(G, 5));
   printf("\n");
   getPath(L, G, 5);
   printList(stdout, L);
   clear(L);
   printf("\n");
   fprintf(stdout,"getDist(2):%d",getDist(G, 29));
   printf("\n");
   getPath(N, G, 29);
   printList(stdout, N);
   clear(N);
   printf("\n");
   fprintf(stdout,"getDist(3):%d",getDist(G, 30));
   printf("\n");
   getPath(N, G, 30);
   printList(stdout, N);
   clear(N);
   printf("\n");
   freeList(&L);
   freeList(&N);
   freeGraph(&G);
   
   return(0);
}
