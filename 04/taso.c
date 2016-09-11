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
node nodes_tab[MAX_NODES_NR]; // tablica wezlow rozmiaru MAX_NODES_NR
int read_data(char * ); // czytanie danych z pliku
void write_data(char * ); // zapis danych do pliku

// lista
link head; // glowa listy
void node_ins(node, link ); // wstawienie wezla do listy
void card_sh(int ); // tasowanie wezlow

int main() 
{
  int i;
  link t;
  int k;
  nodes_nr = read_data("stos.in");
  for (i = 0; i < nodes_nr; i++) // wlozenie wezlow do listy
    node_ins(nodes_tab[i], head);
  k = 26;
  card_sh(k); // przelozenie
  for (t = head; t != NULL; t = t->next) // wydruk
    printf("%s\t%s\n", t->item.suit, t->item.title); 
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

// funkcje dla listy
void node_ins(node a, link u) 
{
  link t = (node*)malloc(sizeof(node )); 
  if (u == NULL) {
    head = t;
    head->item = a.item;
    head->next = NULL;
  }
  else if (u == head) {
    head = t;
    head->item = a.item;
    head->next = u;
  }
  else {
    t->item = a.item;
    t->next = u;
    u->next = t;
  }
}       

void card_sh(k)
{
  int i;
  link t = head, u = head, w, s;
  for (i = 0; i < k; i++)
    t = t->next;
  for (w = t->next; w != NULL; w = w->next) {
    if (w->next == NULL) {
      s = w;
    }
  }
  head = t->next;
  s->next = u;
  t->next = NULL;
}
