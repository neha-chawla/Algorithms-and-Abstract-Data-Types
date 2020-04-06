/*  Neha Chawla
	nechawla
	pa4
	Graph.c
*/

#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>

typedef struct GraphObj{
   List *neighbors;
   char *color;
   int order;
   int size; 
   int source;
   int *parent;   
   int *distance;
   
} GraphObj;

Graph newGraph(int n){
   int i;
   Graph G = malloc(sizeof(GraphObj));
   G->order = n;
   G->size = 0; 
   G->source = NIL;		
   G->parent = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   G->color = calloc(n+1, sizeof(char));
   G->neighbors = calloc(n+1, sizeof(List));

   for(i = 0; i <= n+1; i++){
      G->neighbors[i] = newList();
      G->parent[i] = NIL;
      G->distance[i] = INF;
      G->color[i] = 'W';
   }
   return(G);
}

void freeGraph(Graph* pG){
   if(pG != NULL && *pG != NULL){
     for(int i = 1; i <= getOrder(*pG); i++){
         freeList(&((*pG)->neighbors[i]));
      }
      free((*pG)->parent);
      free((*pG)->distance);
      free((*pG)->color);
      free((*pG)->neighbors);
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

int getSource(Graph G){
   if(G == NULL) {
      printf("Error");
      exit(1);
   }
   return G->source;
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
   return G->parent[u];
}

int getDist(Graph G, int u){
   if(G == NULL) {
      printf("Error");
      exit(1);
   }
   if(u < 1 || u > getOrder(G)){
      printf("Error");
      exit(1);
   }
   return G->distance[u];
}

void getPath(List L, Graph G, int u){
   if(G == NULL) {
      printf("Error");
      exit(1);
   }
   if(getSource(G) == NIL){      
      printf("Error");
      exit(1);
   }
   else if(u < 1||u > getOrder(G)){
      printf("Error");
      exit(1);
   }
   if(getSource(G) == u){
        append(L, u);
   }
   else if(getParent(G, u) == NIL){
        append(L, NIL);
   }
   else{
        getPath(L, G, getParent(G, u));
        append(L, u);
   }
}

void makeNull(Graph G){
   if(G == NULL){
      printf("Error");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++){
      clear(G->neighbors[i]);
      G->parent[i] = NIL;
      G->distance[i] = INF;
      G->color[i] = 'W';
   }
   G->size = 0;
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
   moveFront(G->neighbors[u]);
   if(length(G->neighbors[u]) == 0){
      append(G->neighbors[u], v);
   }
   while(index(G->neighbors[u]) != -1){
      if(get(G->neighbors[u]) > v){
         insertBefore(G->neighbors[u], v);
         break;
      }
      moveNext(G->neighbors[u]);
      if(index(G->neighbors[u]) == -1){
         append(G->neighbors[u], v);
         break;
      }
   }
   moveFront(G->neighbors[v]);
   if(length(G->neighbors[v]) == 0){
      append(G->neighbors[v], u);
   }
   while(index(G->neighbors[v]) != -1){
      if(get(G->neighbors[v]) > u){
         insertBefore(G->neighbors[v], u);
         break;
      }
      moveNext(G->neighbors[v]);
      if(index(G->neighbors[v]) == -1){
         append(G->neighbors[v], u);
         break;
      }
   }
   ++G->size;
}

void addArc(Graph G, int u, int v){
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
   moveFront(G->neighbors[u]);
   while(index(G->neighbors[u]) > -1 && v > get(G->neighbors[u])){
        moveNext(G->neighbors[u]);
    }
    if(index(G->neighbors[u]) == -1){
        append(G->neighbors[u], v);
    }
    else{
        insertBefore(G->neighbors[u], v);
    }
    G->size++;
}
void BFS(Graph G, int s){
   if(G == NULL){
      printf("Error");
      exit(1);
   }
   List Q = newList();
   G->source = s;
   for(int i = 1; i <= G->order; i++){
      G->color[i] = 'W';
      G->distance[i] = INF;
      G->parent[i] = NIL;
   }
   G->color[s] = 'G';
   G->distance[s] = 0;
   G->parent[s] = NIL;
   append(Q,s);
   while(length(Q) != 0){
        int x = back(Q);
        deleteBack(Q);
        moveFront(G->neighbors[x]);
        while(index(G->neighbors[x]) != -1){
            int u = get(G->neighbors[x]);
            if(G->color[u] == 'W'){
                G->color[u] = 'G';
                G->parent[u] = x;
                G->distance[u] = G->distance[x] + 1;
                prepend(Q,u);
            }
            moveNext(G->neighbors[x]);
        }
    }
   freeList(&Q);
}

void printGraph(FILE* out, Graph G){
   if(G == NULL){
      printf("Error");
      exit(1);
   }
   for(int i = 1; i <= G->order; i++){
      fprintf(out, "%d:", i);
      printList(out, G->neighbors[i]);
      fprintf(out, "\n");
   }
}