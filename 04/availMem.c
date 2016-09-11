#include <stdio.h>

// wezly
#define MAX_NODES_NR 100 // maksymalna ilosc wezlow
#define false 0
#define true (! false)
typedef short int bool; // typ logiczny 
struct Info {
  bool tag;
  char suit[4];
  int rank;
  char title[10];
};
typedef struct Info info;
typedef struct Node *link; // typ danych dowiazanie
typedef struct Node node; // typ danych wezel
struct Node { // dwuczesciowa struktura wezla
  info item;
  link next;
};	
int nodes_nr; // liczba wezlow
node nodes_tab[MAX_NODES_NR]; // tablica wezlow rozmiaru NodesNr
int read_data(char * ); // czytanie danych z pliku
void write_data(char * ); // zapis danych do pliku

// stos wolnej pamieci
#define new(type) (type *)calloc(sizeof(type), 1) // makro przydzialu pamieci dla struktury
#define STACK_SIZE 256
link top; // wskaznik wierzcholka stosu wolnej pamieci
void push(node ); // wstawianie do stosu
node pop( ); // sciaganie ze stosu
void construct(int ); // konstrukcja stosu wolnej pamieci

int main()
{
  int i;
  link t;
  link head;
  nodes_nr = read_data("stos.in"); 
  construct(nodes_nr); // przydzial wolnej pamieci
  head = top;
  for (i = 0; i < nodes_nr; i++) { // pobieranie wezlow ze stosu
    t = top;    
    pop();
    t->item = nodes_tab[i].item;
  }
    for (t = head; t != NULL; t = t->next) { // wydruk informacji w wezlach
    printf("%s\t%s\n", t->item.suit, t->item.title);
    }
  return 0;
}

// funkcje dla wezlow
int read_data(char *stream) 
{
  FILE *fp;
  fp = fopen(stream, "r");  
  bool tag;
  char suit[4];
  int rank;
  char title[10];
  char *fmt = "%c %s %i %s\n"; // format danych pliku wejsciowego
  info x; // element
  node a; // wezel
  int count = 0; // licznik
  while (fscanf(fp, fmt, &tag, &suit, &rank, &title) != EOF) {  
    x.tag = tag;
    strcpy(x.suit, suit); 
    x.rank = rank;
    strcpy(x.title, title);
    nodes_tab[count].item = x;
    count++;
  }
  fclose(fp); 
  return count;
}

void write_data(char *stream) 
{
  FILE *fp;
  int i;
  fp = fopen(stream, "w");
  for (i = 0; i < nodes_nr; i++) {  
    info x = nodes_tab[i].item; 
    fprintf(fp,"%c\t%s\t%i\t%s\n", x.tag, x.suit, x.rank, x.title);
  }
  fclose(fp); 
}

// funkcje obslugi stosu wolnej pamieci
void push(node a) 
{
  link s;
  info x = a.item;
  s = new(node);
  s->item = x;
  s->next = top;
  top = s;
}

node pop()
{
  link t;
  node a;
  if (top == NULL) {
    fprintf(stderr,"error: top is empty!\n");
    exit(-1);
  }
  a.item = top->item;
  a.next = top->next;
  t = top->next;
  top = t;
  return a;
}

void construct(int n) 
{
  int i;
  node nodenull;// = {true, "kier", 10, "dziesiatka", NULL};
  for (i = 0; i < n; i++) 
    push(nodenull);
}
