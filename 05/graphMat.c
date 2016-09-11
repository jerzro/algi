#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true (! false)
#define MAXNRVERTICES 10000 // maksymalna liczba wierzcho³ków
typedef short int bool; // true, false
typedef struct {int v; int w;} edge; // typ dla krawedzi
struct Graph {int V; int E; int **adj;}; // struktura grafu
typedef struct Graph *graph; // typ dla grafu
edge Edge(int , int ); // krawedz pomiedzy wierzcholkami
int graph_import(char* , edge *); // import grafu z pliku
int graph_export(char* , char *, int , int , edge *); // eksport grafu do pliku
int graph_eds(edge *, graph ); // krawedzie grafu
void edge_ins(graph , edge ); // wlozenie krawedzi w graf
void edge_rem(graph, edge ); // usuniecie krawedzi z grafu
graph graph_init(int ); // inicjowanie grafu
void graph_del(graph ); // zniszczenie grafu
graph graph_rand(int , int ); // utworzenie grafu losowego
void graph_show(graph ); // druk grafu w terminalu
void am_show(graph ); // pokazanie macierzy sasiedztwa na ekranie

int main(int argc, char *argv[])
{ 
  if ( argc > 3 || argc < 2) {
    printf("Usage: %s number of vertices number of edges\n",argv[0]);
    return -1;
  }
  int V = atoi(argv[1]), E = atoi(argv[2]); // ilosc wierzcholkow i krawedzi
  graph g = graph_rand(V, E);
  graph_show(g);
  graph_del(g);
  return 0;
}

// funkcje grafowe
edge Edge(int v, int w) 
{ 
  edge e;
  e.v = v; e.w = w;
  return e;
}

int graph_import(char *name, edge e[])
{
  int i = 1;
  int result; // wynik importu
  FILE *fp;
  char l; char *line; char s[255]; long tmp; char ft[4];
  const char *rdfmt1 = "%c\n"; const char *rdfmt2 = "%c %s %i %i\n"; const char *rdfmt3 = "%c %i %i\n"; // format rekordów w pliku
  printf("GraphImport: ");
  printf("g < %s, ", name);
  fp = fopen(name,"r");
  if(fp == NULL) {
    printf("Error: can't open file.\n"); 
    return -1;
  }
  while(!feof(fp)){
    tmp = ftell(fp);
    fscanf(fp, rdfmt1, &l, &s); 
    switch(l)
      {
      case 'c' :
	line = fgets(s, 256, fp);
	break;
      case 'p' :
	fseek(fp, tmp, SEEK_SET);
	fscanf(fp, rdfmt2, &l, &ft, &e[0].v, &e[0].w);
	if(ft[0] == 'e'){
	  printf(" format: edge\n");
	}
	if(ft[0] == 'a'){
	  printf(" format: arc\n");
	}
	break; 
      case 'e' :
	fseek(fp, tmp, SEEK_SET);
	fscanf(fp, rdfmt3, &l, &e[i].v, &e[i].w);
	i++;
	break;
      default :
       	printf("Unknown prefix %c in line %i\n",l, i);
	result = -1;
      } 
  }
  fclose(fp);
  return result;
}

int graph_export(char *name, char *c, int V, int E, edge e[])
{
  int i = 0;
  FILE *fp;
  printf("GraphExport: ");
  printf("g > %s\n", name);
  fp = fopen(name ,"w");
  if(fp == NULL) {
    printf("Error: can't open file.\n"); 
    return -1;
  }
  fprintf(fp, "c\t%s\n",c);  
  fprintf(fp, "p\tedge\t%i\t%i\n", V, E);
  for(i = 1; i <= E; i++)
    fprintf(fp, "e\t%i\t%i\n", e[i].v, e[i].w);
  fclose(fp);
  return 0;
}

int **adm(int r, int c, int val)
{ 
  int i, j;
  int **t = malloc(r * sizeof(int *));
  for (i = 0; i < r; i++)
    t[i] = malloc(c * sizeof(int ));
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
      t[i][j] = val;
  return t;
}

graph graph_init(int V)
{ 
  graph g = malloc(sizeof *g);
  g->V = V; g->E = 0;
  g->adj = adm(V+1, V+1, 0);
  return g;
}

void edge_ins(graph g, edge e)
{ 
  int v = e.v, w = e.w;
  g->adj[v][w] = 1; 
  g->adj[w][v] = 1;
  g->E++;
}

void edge_rem(graph g, edge e)
{ 
  int v = e.v, w = e.w;
  if(g->adj[v][w] == 1)
    g->E--;
  g->adj[v][w] = 0; 
  g->adj[w][v] = 0;
}

int graph_eds(edge e[], graph g)
{
  int v, w;
  int i = 0;
  for (v = 1; v <= g->V; v++)
    for (w = v+1; w <= g->V; w++)
      if (g->adj[v][w] == 1) 
	e[i++] = Edge(v, w);
  return i;
}

graph graph_rand(int V, int E)
{ 
  int i, j;
  double p = 2.0*E/V/(V-1);
  graph g = graph_init(V);
  for (i = 1; i <= V; i++)
    for (j = 1; j < i; j++)
      if (rand() <= p*RAND_MAX)
	edge_ins(g, Edge(i, j)); 
  return g;
}

void graph_show(graph g)
{ 
  int i, j; 
  if(g->V <= 100){
  if (g != NULL){ 
    printf("GraphShow: %d vertices, %d edges\n", g->V, g->E);
    for (i = 1; i <= g->V; i++){
      printf("%2d:", i);
      for (j = 1; j <= g->V; j++)
	if (g->adj[i][j] == 1) printf(" %2d", j);
      printf("\n");
    }
  }
  else
    printf(" has been destroyed\n", g);
  }
  else
    printf("number of vertices > 100, splay off\n");
}

void am_show(graph g)
{ 
  int i, j; 
  if(g->V <= 100){
    if (g != NULL){ 
      printf("adjacency matrix show: %d vertices, %d edges:\n", g->V, g->E);
      for (i = 1; i <= g->V; i++){
	for (j = 1; j <= g->V; j++)
	  printf(" %2d", g->adj[i][j]);
	printf("\n");
      }
    }
    else
      printf("graph has been destroyed\n", g);
  }
  else
    printf("number of vertices > 100, display off\n");
}

void graph_del(graph g)
{
  free(g);
}
