#include <stdio.h>
#include <string.h>
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
struct Node { // dwuczesciowa struktura wezla
  info item;
  link next;
};	
typedef struct Node node; // typ danych wezel
int nodes_nr; // liczba wezlow
node nodes_tab[MAX_NODES_NR]; // tablica wezlow rozmiaru NodesNr
int read_data(char * ); // czytanie danych z pliku
void write_data(char * ); // zapis danych do pliku

#define STACK_SIZE 100
link top; // wskaznik wierzcholka stosu
void push(node ); // wstawianie do stosu
node pop( ); // sciaganie ze stosu

int main() 
{
  int i; // iterator dla tablicy 
  link t; // iterator dla dowiazania
  top = NULL;
  nodes_nr = read_data("stos.in"); // wypelnienie tablicy wezlow
// wlozenie wezlow na stos
  for (i = 0; i < nodes_nr; i++) 
    push(nodes_tab[i]);
// sciagniecie wezlow ze stosu z wykorzystaniem dowiazan
  i = 0;
  for (t = top; t != NULL; t = t->next) {
    nodes_tab[i] = pop();
    i = i+1;
  }
  write_data("stos.out"); // zapis danych do pliku
  return 0;
}

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

void push(node a) 
{
  info x = a.item;
  link s = (node*)malloc(sizeof(node));
  s->item = x;
  s->next = top;
  top = s;
}

node pop()
{
  link t;
  node a;
  if (top == NULL) {
    fprintf(stderr,"error: The stack is empty!\n");
    exit(-1);
  }
  a.item = top->item;
  a.next = top->next;
  t = top->next;
  top = t;
  return a;
}
