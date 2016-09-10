#include <iostream>
#include <stack>

#define ITEMS_NR 10 // rozmiar tablicy elementow

struct info { // struktura elementu faktury
  char* typ;
  double wartosc;
};

typedef stack<info, deque<info> > stackinfo;
