/*  Neha Chawla
	nechawla
	pa2
	List.c
*/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

//private NodeObj type
typedef struct NodeObj {
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj {
   Node front;
   Node back;
   int length;
   Node c;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->c = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
   Node f = (*pL)->front;
   if(pL!=NULL && *pL!=NULL) { 
      while( f != NULL && length(*pL) > 0) { 
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){ 
  if( L==NULL ){
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return L->length;
}

int index(List L) {
  if(L->c != NULL){
    return L->index;
  }
  return -1;
}

// front()
// Returns the value at the front of L.
// Pre: length() > 0
int front(List L){
  if( L==NULL ){
      printf("Queue Error: calling front() on NULL Queue reference\n");
      exit(1);
  }
  if(L->length >= 1){
    return L->front->data;
  }
  printf("List Error: calling front() on empty List reference\n");
  exit(1);
}

// back()
// Returns the value at the back of L.
// Pre: length() > 0
int back(List L) {
  if( L==NULL ){
      printf("Queue Error: calling back() on NULL Queue reference\n");
      exit(1);
  }
  if(L->length >= 1){
    return L->back->data;
  }
  printf("List Error: calling back() on empty List reference\n");
  exit(1);
}

int get(List L) {
  if(L->length > 0 && L->index >= 0){
    return L->c->data;
  } 
  printf("List Error: calling get() with an empty List\n");
  exit(1);
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;
   
   if( A==NULL || B==NULL )
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   
   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Manipulation procedures --------------------------------------------------------

void clear(List L) {
  if(L == NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
  while(L->back != NULL){
    deleteFront(L);
  }
  L->front = L->back = L->c = NULL;
  L->length = 0;
  L->index = -1;
}

void moveFront(List L) {
  if(L == NULL) {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
  if(L->length >= 1){
    L->c = L->front;
    L->index = 0;
  }
}

void moveBack(List L) {
  if(L == NULL) {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
  if(L->length >= 1){
    L->c = L->back;
    L->index = L->length-1;
  }
}

void movePrev(List L){
  if(L == NULL){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
  }
  if(L->c != NULL){
  	if(L->c != L->front){
   	  L->c = L->c->prev;
   	  (L->index)--;
  	}
  	else if(L->c == L->front){
   	  L->c = NULL;
   	  L->index = -1;
  	}
  }
}

void moveNext(List L) {
  if(L == NULL){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
  }
  if(L->c != NULL){
  	if(L->c != L->back){
  	  L->c = L->c->next;
   	  (L->index)++;
  	}
  	else if(L->c == L->back){
  	  L->c = NULL;
  	  L->index = -1;
  	}
  }
}

void prepend(List L, int data) {
  if(L == NULL) {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }  
  Node N = newNode(data);
  if(L->length == 0){
    L->front = L->back = N;
    (L->length)++;
    L->c = L->front = L->back;
  }
  else{ 
    if(L->c != NULL){
      (L->index)++;
    }
    L->front->prev = N;
    N->next = L->front;
    L->front = N;
    (L->length)++;
  }
}

void append(List L, int data) {
  if(L == NULL) {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
  Node N = newNode(data);
  if(L->length == 0){
    L->front = L->back = N;
    (L->length)++;
  }
  else{
    L->back->next = N;
    N->prev = L->back;
    L->back = N;      
    (L->length)++;
  }
}

void insertBefore(List L, int data) {
  if(L == NULL) {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
  }
  Node N = newNode(data);
  if(L->length <= 0 || L->index < 0){
    printf("List Error: insertBefore() called with an empty List");
    exit(1);
  }
  else if(L->c == L->front){
    N->prev = NULL;
    N->next = L->c;
    L->c->prev = N;
    L->front = N;
  }
  else{
    N->next = L->c;
    N->prev = L->c->prev;
    L->c->prev->next = N;
    L->c->prev = N;
  }
  (L->length)++;
  (L->index)++;
}

void insertAfter(List L, int data) {
  Node N = newNode(data);
  if(L->length <= 0 || index(L) < 0){
    printf("List Error: insertAfter() called with an empty List");
    exit(1);
  }
  else if(L->c == L->back){
    N->next = NULL;
    N->prev = L->c;
    L->c->next = N;
    L->back = N;
  }
  else{
    N->prev = L->c;
    N->next = L->c->next;
    L->c->next->prev = N;
    L->c->next = N;
  }
  (L->length)++;
}

void deleteFront(List L){
  if(L == NULL) {
      printf("List Error: deleteFront() called on NULL List reference\n");
      exit(1);
  }
  if(L->length == 0){
	return;
  }
  if(L->length > 1){
    L->front = L->front->next;
    if(L->c == L->front->prev){
      L->c = NULL;
    }
    L->index--;
    L->length--;
    freeNode(&L->front->prev);
  }
  else if (L->length == 1){ 
    (L->length)--;
    L->index = -1;
    L->c = NULL;
    L->back = NULL;
    freeNode(&L->front);
  }
  else{
    printf("List Error: deleteFront() called on an empty List\n");
    exit(1);
  }
}

void deleteBack(List L) {
  if(L == NULL){
      printf("List Error: deleteBack() called on NULL List reference\n");
      exit(1);
  }
  if(L->length == 0){
	return;
  }
  if(L->length > 1){ 
  	if(L->c == L->back){
      L->index = -1;
      L->c = NULL; 
      L->back = L->back->prev;
      (L->length)--;
      freeNode(&L->back->next);
    }
    else{ 
      L->back = L->back->prev;
      (L->length)--;
      freeNode(&L->back->next);
    }
  }
  else if (L->length == 1){
    freeNode(&L->back);
    L->back = L->front = NULL;
    (L->length)--;
    L->index = -1;
  }
  else{
    printf("List Error: deleteBack() called on an empty List\n");
    exit(1);
  }
}

void delete(List L) {
  if(L == NULL){
      printf("List Error: delete() called on NULL List reference\n");
      exit(1);
   }
  if(L->length <= 0 || L->index < 0){
    printf("List Error: delete() called with an empty List\n");
    exit(1);
  }
  else{
  	if(L->c == L->front){
   		deleteFront(L);
  	}
  	else if(L->c == L->back){
    	deleteBack(L);
  	}
  	else{
   		L->c->next->prev = L->c->prev;
    	L->c->prev->next = L->c->next;
    	freeNode(&L->c);
    	(L->length)--;
    	L->index = -1;
  	} 
  }
}


void printList(FILE* out, List L){
   Node N = NULL;
   if(L == NULL){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

List copyList(List L) { 
    List t = newList();
    Node N = NULL;
    for(N = L->front; N!= NULL; N=N->next){
		append(t, N->data);
    }
    return t;
}