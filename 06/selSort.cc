#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

typedef int node;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {node t = A; A = B; B = t;}

void selection_sort(vector<node> & );

int main() {
    vector<node> v;
    v.push_back(0);
    for(int i=1; i<100; i++) {
        int pos = rand() % v.size();
        v.insert(v.begin() + pos, i);
    }; copy(v.begin(), v.end(), ostream_iterator<unsigned int>(cout, " ")); cout << endl;

    selection_sort(v);
	return 0;
}

void selection_sort(vector<node>& v) {
    if ( v.empty() ) return;
    int i, j, min;
    for (i = 0; i < v.size(); i++) {
    	min = i;
    	for (j = i + 1; j < v.size(); j++)
    		if (less(v[j], v[min])) min = j;
    exch(v[i], v[min]);
    }
    copy(v.begin(), v.end(), ostream_iterator<unsigned int>(cout, " ")); cout << endl;
}
