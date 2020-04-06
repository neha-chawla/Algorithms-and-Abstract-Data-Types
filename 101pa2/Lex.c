/*  Neha Chawla
	nechawla
	pa2
	Lex.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 1600

int main(int argc, char * argv[]){
   
   int count, b = 0;
   FILE *in, *out;
   FILE *inTwo;
   char line[MAX_LEN];
   
   
   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   
   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out == NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   /* read each line of input file, then count and print tokens */
   while( fgets(line, MAX_LEN, in) != NULL){
      count++;
      /*n = 0;
      token = strtok(line, " \n");
      tokenlist[0] = '\0';
      while( token!=NULL ){
         strcat(tokenlist, "   ");
         strcat(tokenlist, token);
         strcat(tokenlist, "\n");
         n++;
         token = strtok(NULL, " \n");
      }*/
   }
   /*fprintf(out, "line %d contains %d token%s: \n", count, n, n==1?"":"s");
   fprintf(out, "%s\n", tokenlist);*/
   
   fclose(in);
   inTwo = fopen(argv[1], "r");
   char *str[count];
   
   while(fgets(line, MAX_LEN, inTwo) != NULL){
      str[b] = malloc(strlen(line) + 1);
      strcpy(str[b], line);
      b++;
   }
   
   List list = newList();

   append(list, 0);
   moveFront(list);

   for(int c = 1; c < count; ++c){
      char *temp = str[c];
      moveBack(list);
      while(index(list) >= 0 && strcmp(temp, str[get(list)]) < 0){
         movePrev(list); 
      }
      if(index(list) >= 0){
         insertAfter(list,c);
      } 
      else{
         prepend(list, c);
      }
   }
   moveFront(list);

   while(index(list) >= 0){
      fprintf(out, str[get(list)]); 
      moveNext(list);
   }
   
   /* close files */  
   fclose(inTwo);
   fclose(out);
   
   clear(list);
   freeList(&list);
   
   return (0);
}