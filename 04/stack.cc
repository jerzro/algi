// stack STL

#include "stack.h"
using namespace std;

int main() 
{
  int i;
  info item; // element typu info
  stackinfo stackFv; // stos 
  info itemsTab[ITEMS_NR] = // tablica danych 
    {
      {"FVZ", 123.456},
      {"FVZ", 321.654},
      {"FVZ", 654.123},
      {"FV", 987.456},
      {"FV", 789.098},
      {"FVZ", 123.321},
      {"FVZ", 234.432},
      {"FV", 345.543},
      {"FV", 567.765},
      {"FVZ", 1.0}
    };
  
  for (i=0; i < ITEMS_NR; i++) stackFv.push(itemsTab[i]); // wstawienie na stos
  for (i = 0; i < ITEMS_NR; i++) {
    cout << stackFv.top().typ << '\t' << stackFv.top().wartosc << endl; // ekran
    stackFv.pop(); // zdjecie ze stosu
  }
  return 0;
}
