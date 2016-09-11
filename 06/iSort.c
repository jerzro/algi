#include <stdio.h>

#define MAX_NODES 52
struct Node {
  int suit;
  int rank;
} v[MAX_NODES];	
typedef struct Node node;

#define key(A) (A.suit)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { node t = A; A = B; B = t; }
#define cmpexch(A, B) if (less(B, A)) exch(A, B)

int read_data(char* ); // z pliku data.in
void isort(node* , int , int ); // sortowanie przez wstawianie

int main() {
  int n; // liczba wezlow
  n = read_data("isort.in"); // wypelnienie tablicy wezlow z pliku data.in
  isort(v, 0, n-1); // sortowanie
	int i; for (i = 0; i < n; i++) printf("%i\t%i\n", v[i].suit, v[i].rank);
  return 0;
}

int read_data(char *FileName) 
{
  FILE *fp;
  fp = fopen(FileName, "r");
  int suit;
  int rank;  
  node x; // element
  char *fmt = "%i\t%i"; // format danych pliku wejsciowego
  int count = 0; // licznik
  while (fscanf(fp, fmt, &suit, &rank) != EOF) {  
    x.suit = suit;
    x.rank = rank;
    v[count] = x;
    count++;
  }
  fclose(fp);  
  return count;
}

void isort(node x[], int l, int r)
{ 
  int i, j;
  node v;
  for (i = r; i > l; i--) cmpexch(x[i-1], x[i]);
  for (i = l+2; i <= r; i++) { 
    j = i; 
    v = x[i]; 
    while (less(v, x[j-1])) { 
      x[j] = x[j-1]; 
      j--; 
    }
    x[j] = v; 
  } 
}

