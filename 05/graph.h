#define false 0
#define true (! false)
#define MAXNRVERTICES 10000 // maksymalna liczba wierzcho³kow

typedef short int bool; // true, false
typedef struct {int v; int w;} edge; // typ dla krawedzi
typedef struct node *link;
struct node {int v; link next;};
struct Graph {int V; int E; link *adj;};
typedef struct Graph *graph;

edge Edge(int , int ); // wlozenie wierzcholka do grafu
int GraphImport(char *, edge *); // import grafu z pliku
int GraphExport(char *, char *, int , int , edge *); // eksport grafu do pliku
int GraphEds(edge *, graph ); // krawedzie grafu
void EdgeIns(graph , edge ); // wlozenie krawedzi w graf
void EdgeRem(graph, edge ); // usuniecie krawedzi z grafu
link NewNode(int , link ); // wstawienie nowego wezla
graph GraphInit(int ); // inicjowanie grafu
void GraphDel(graph ); // zniszczenie grafu
void GraphShow(graph ); // pokazanie grafu na ekranie
