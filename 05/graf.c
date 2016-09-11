#include <stdio.h>
#include "graph.h"

int main(int argc, char **argv)
{ 
  if( argc > 3 || argc < 2){
    printf("Usage: %s infile [outfile = graph.out]\n", argv[0]);
    return -1;
  }
  int i = 0; // iterator
  char *filename; // nazwa pliku wejsciowego
  int V; int E;
  edge e[100]; // tablica 100 wierzcho³ków
  filename = argv[1];
  GraphImport(filename, e); // wstawienie krawedzi e[] z pliku
  V = e[0].v; E = e[0].w;
  graph g = GraphInit(V);
  for(i = 1; i <= E; i++)
    EdgeIns(g, e[i]);
  GraphShow(g);
  GraphDel(g);
  return 0;
}
