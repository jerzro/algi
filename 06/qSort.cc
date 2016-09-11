#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

typedef char node;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {node t = A; A = B; B = t;}

int partition(vector<node> &, int, int);
void qsort(vector<node> &, int, int);

int main() {
	string s = "SORTOWANI";
	vector<node> v;
	v.push_back('E');
	for(int i=0; i<9; i++) {
	v.insert(v.begin()+i, s[i]);
	}; copy(v.begin(), v.end(), ostream_iterator<char>(cout, " ")); cout << endl;

	qsort(v, 0, v.size());
	return 0;
}

int partition(vector<node>& v, int l, int r) {
  int i = l-1, j = r;
  node vi = v[r];
  for (;;) {
      while (less(v[++i], vi)) ;
      while (less(vi, v[--j]))
	if (j == l) break;
      if (i >= j) break;
      exch(v[i], v[j]);
    }
  exch(v[i], v[r]);
  return i;
}

void qsort(vector<node>& v, int l, int r) {
  int pivot;
  if (r <= l) return ;
  pivot = partition(v, l, r);
  qsort(v, l, pivot-1);
  qsort(v, pivot+1, r);
}
