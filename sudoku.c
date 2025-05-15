#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int verificar_filas(const int sudo[9][9]) {
  int casilla;
  for (int i = 0; i < 9; i++) {
    int lista[10] = {0} ;
    for (int k = 0; k < 9; k++) {
      casilla = sudo[i][k];
      if (lista[casilla]) return 0;
      else if (!casilla) continue;

      lista[casilla] = 1;
    }
  }
  return 1;
}

int verificar_columnas(const int sudo[9][9]) {
  int casilla;
  for (int i = 0; i < 9; i++) {
    int lista[10] = {0} ;
    for (int k = 0; k < 9; k++) {
      casilla = sudo[k][i];
      if (lista[casilla]) return 0;
      else if (!casilla) continue;

      lista[casilla] = 1;
    }
  }
  return 1;
}

int verificar_submatrices(const int sudo[9][9]) {
  int i, j, casilla;
  for (int k = 0; k < 9; k++) {
    int lista[10] = {0};
    for (int p = 0; p < 9; p++) {
      i = 3 * (k / 3) + (p / 3);
      j = 3 * (k % 3) + (p % 3);
      
      casilla = sudo[i][j];
      if (lista[casilla]) return 0;
      else if (!casilla) continue;
      
      lista[casilla] = 1;
    }
  }
  return 1;
}

int is_valid(Node* n){
  return (verificar_filas(n->sudo) 
  && verificar_columnas(n->sudo) 
  && verificar_submatrices(n->sudo)) ? 1 : 0;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    for(int i = 0, k = 0; i < 9; i++, k = 0) {
      while(k < 9){
        if (!n->sudo[i][k]) {
          // Si encuentra un valor nulo (0) en el sudo 
          // va agregando copias del nodo con ese valor rellenado (1 a 9)
          for (int counter = 1; counter <= 9; counter++) {
            int* new_number = (int*) malloc(sizeof(int));
            *new_number = counter; 
            Node* node_copy = copy(n);
            node_copy->sudo[i][k] = *new_number;

            (is_valid(node_copy)) ? pushBack(list, node_copy) : free(node_copy);
          };
          return list;
        }
        k++;
      }
    }

    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S, initial);
  while (top(S) != NULL) {
    pop(S);
    Node* current = top(S);
    if (is_final(current)) return current;

    List* adj_nodes = get_adj_nodes(current);
    Node* adj = first(adj_nodes);
    while (adj != NULL) {
      push(S, adj);
      adj = next(adj);
    }

    free(current);
    (*cont)++;
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/