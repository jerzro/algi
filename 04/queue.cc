#include <iostream>
#include <list>
#include <queue> // STL
using namespace std;

typedef list<char*, allocator<char*>> CHARLIST;
typedef queue<char*, CHARLIST> CHARQUEUE;

int main() 
{
	int i;	
    CHARQUEUE q; // kolejka lancucha znakow	
	char *itemsTab[10] = // tablica elementow
    {
      {"Cathy Ball"},
      {"Randy Crump"},
      {"Eric Dinehart"},
      {"Bill Hoffman"},
      {"Ed Sears"},
      {"Keith Toleman"},
      {"Michael Fayette"},
      {"Irving Gelb"},
      {"Diane Hollibaugh"},
      {"Betti Hufford"}
    };
	for (i = 0; i < 10; i++) q.push(itemsTab[i]);
	while (!q.empty()) {
		cout << q.front() << endl;
        q.pop();}
	return 0;
}
