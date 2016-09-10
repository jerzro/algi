#include <stdio.h>
#define ITEMS_NR 10 // liczba elementow

struct Info { // struktura elementu (dane osoby)
  char Imie[20];
  char Nazwisko[30];
};
typedef struct Info info; // typ danych item (element)

#define QUEUE_SIZE 10 // rozmiar kolejki
info q[QUEUE_SIZE]; // tablica elementow dla kolejki
int head, tail; // wskazniki kolejki: przod i tyl
void put(info ); // wstawienie elementu do kolejki
info get(); // wyjecie elementu z kolejki
void print(info item);

int main() 
{
  int i;
  info item; // element
  info items_tab[ITEMS_NR] = // tablica wezlow
    {
      {"Cathy", "Ball"},
      {"Randy", "Crump"},
      {"Eric", "Dinehart"},
      {"Bill", "Hoffman"},
      {"Ed", "Sears"},
      {"Keith", "Toleman"},
      {"Michael", "Fayette"},
      {"Irving", "Gelb"},
      {"Diane", "Hollibaugh"},
      {"Betti", "Hufford"}
    };
  for (i = 0; i < ITEMS_NR; i++) { // umieszczenie wezlow w kolejce
    put(items_tab[i]);
    print(items_tab[i]);
  }
  printf("\n");
  for (i = 0; i <= ITEMS_NR; i++) { // wyjecie wezlow z kolejki
    item = get();
    print(item);
  }
  return 0;
}

void put(info item) 
{
  if (tail == QUEUE_SIZE) {
    fprintf(stderr,"error: queue overflow!\n");
    exit(-1);
      }
  else
    q[tail++] = item;
}

info get() 
{
  if (head == tail) {
    fprintf(stderr,"error: queue underflow!\n");
    exit(-1);
  }
  else
    return q[head++];
}

void print(info item)
{
  printf("%.20s %.30s\n", item.Imie, item.Nazwisko);
}
