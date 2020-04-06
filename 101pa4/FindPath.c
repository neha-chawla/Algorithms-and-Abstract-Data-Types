/*  Neha Chawla
	nechawla
	pa4
	FindPath.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
   FILE *inFile;
   FILE *outFile;
   char line[MAX_LEN];
   
   List L = newList();
   int vertexA = 1;
   int vertexB = 1;

   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   inFile = fopen(argv[1], "r");
   outFile = fopen(argv[2], "w");
   
   if(inFile == NULL || outFile == NULL){
      printf("Unable to open file\n");
      exit(1);
   }
   
   fgets(line, MAX_LEN, inFile);
   Graph G = newGraph(atoi(strtok(line, " \n")));
   
   while(vertexA > 0){
      fgets(line, MAX_LEN, inFile);
      vertexA = atoi(strtok(line, " \n"));
      if(vertexA == 0){	
         break;
      }
      vertexB = atoi(strtok(NULL, " \n"));  
      addEdge(G, vertexA, vertexB);
   }
   printGraph(outFile, G);
   fprintf(outFile, "\n");
   vertexA = 1;
   
   while(vertexA != 0) {
      fgets(line, MAX_LEN, inFile);
	  vertexA = atoi(strtok(line, " \n"));	
	  if(vertexA == 0){
         break;
      }
      BFS(G, vertexA);
	  
      vertexB = atoi(strtok(NULL, " \n"));		
      if(getDist(G, vertexB) != INF){	
         fprintf(outFile, "The distance from %d to %d is %d\n",vertexA, vertexB, getDist(G, vertexB));
         fprintf(outFile, "A shortest %d-%d path is:", vertexA, vertexB);
         clear(L);
         getPath(L, G, vertexB);
         printList(outFile, L);
         fprintf(outFile, "\n");
         fprintf(outFile, "\n");
      }
      else{
         fprintf(outFile, "The distance from %d to %d is infinity\n",vertexA, vertexB);
         fprintf(outFile, "No %d-%d path exists\n\n", vertexA, vertexB);
      }
   }
   fprintf(outFile, "\n");
   freeGraph(&G);
   freeList(&L);
   fclose(inFile);
   fclose(outFile);
   return(0);
}
