#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

edge edgein(int v, int w) 
{ 
  edge e;
  e.v = v; e.w = w;
  return e;
}

int GraphImport(char *name, edge e[])
{
  int i = 1;
  int result; // wynik importu
  FILE *fp;
  char l; char *line; char s[255]; long tmp; char ft[4];
  const char *rdfmt1 = "%c\n"; const char *rdfmt2 = "%c %s %i %i\n"; const char *rdfmt3 = "%c %i %i\n"; // format rekordow w pliku
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

int GraphExport(char *name, char *c, int V, int E, edge e[])
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

graph GraphInit(int V)
{
  int v;
  graph g = malloc(sizeof *g);
  g->V = V; g->E = 0;
  g->adj = malloc(V*sizeof(link));
  for (v = 0; v <= V; v++){
    g->adj[v] = NULL;
  }
  return g;
}

link NewNode(int v, link next)
{
  link x = malloc(sizeof *x);
  x->v = v; x->next = next;     
  return x;                         
}

void EdgeIns(graph g, edge e)
{
  int v = e.v, w = e.w;
  g->adj[v] = NewNode(w, g->adj[v]);
  g->adj[w] = NewNode(v, g->adj[w]); 
  g->E++;
}

void EdgeRem(graph g, edge e)
{
  int u, v = e.v, w = e.w;
  link p, q, t;
  printf("GraphRem: \n");
  for (u = 1; u <= g->V; u++){
    if(u == v){
      p = g->adj[u];
      if(p->next == NULL)
	g->adj[u] = NULL;
      else
	for (t = p; t != NULL ; t = q){
	  q = t->next;
	  if(q != NULL){
	    if(q->v == w)
	      t->next = q->next;
	  }
	  else
	    t = NULL;
	}
    }
  }
  for (u = 1; u <= g->V; u++){
    if(u == w){
      p = g->adj[u];
      if(p->next == NULL)
	g->adj[u] = NULL;
      else
	for (t = p; t != NULL ; t = q){
	  q = t->next;
	}
    }
  }
  g->E--;
}

void GraphShow(graph g)
{
  int v = 1;
  link t;
  if(g->V <= 100){
    printf("GraphShow: %d vertices, %d edges, adjacency list:\n", g->V, g->E);
    for (v = 1; v <= g->V; v++){
      printf("%2d:", v);
      for (t = g->adj[v]; t != NULL ; t = t->next)      
	printf(" %2d", t->v);
      printf("\n");
    }
  }
  else
    printf("GraphShow: display off\n");
}

void GraphDel(graph g)
{
  int v = 0;
  link q, t;
  for (t = g->adj[v]; t != NULL ; t = q){
    q = t->next;
    free(t);
  }
}
