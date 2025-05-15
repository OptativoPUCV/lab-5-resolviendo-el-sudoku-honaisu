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

int verificarConLista(const int sudo[9][9], int i, int k) {
  for (i = 0, k = 0; i < 9; i++, k = 0) {
    int lista[10] = {0} ;
    do {
      if (!sudo[i][k]) continue;
      if (lista[sudo[i][k]]) return 0;

      lista[sudo[i][k]] = 1;
    } while((k++)<8);
  }
  return 1;
}

int is_valid(Node* n){
  // Caso 1 y 2: Filas y columnas
  int a = 0, b = 0;
  if (!verificarConLista(n->sudo, a, b)) return 0;
  if (!verificarConLista(n->sudo, b, a)) return 0;

  // Caso 3: Submatrices
  int k = 4, p;
  for(p = 0; p < 9; p++) {
    int listaSub[10] = {0};
    int i = 3 * (k / 3) + (p / 3);
    int j = 3 * (k % 3) + (p % 3);
    //if (!n->sudo[i][j]) continue;
    //if (listaSub[n->sudo[i][j]]) return 0;
    printf("%d ", n->sudo[i][j]);
    listaSub[n->sudo[i][j]] = 1;
    if(p % 3 == 2) putchar('\n');
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int counter = 1;
    for(int i = 0, k = 0; i < 9; i++, k = 0) {
      while(k < 9){
        if (!n->sudo[i][k]) {
          // Si encuentra un valor nulo (0) en el sudo 
          // va agregando copias del nodo con ese valor rellenado (1 a 9)
          while (counter < 9) {
            int* new_number = (int*) malloc(sizeof(int));
            *new_number = counter; 
            Node* node_copy = copy(n);
            node_copy->sudo[i][k] = *new_number;

            (is_valid(node_copy)) ? pushBack(list, node_copy) : free(node_copy);
            counter++;
          };
          // Por si hay más de un espacio vacío,
          // vuelve al valor original (?)
          counter = 1;
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