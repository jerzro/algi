#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

typedef vector<unsigned int> node;

void radix_sort(node & v)
{
    if ( v.empty() ) return;

    typedef vector< vector< node::value_type > > buckets_type;
    buckets_type buckets;
    buckets.resize(10);
    int pow10 = 1;
    node::value_type max = *max_element(v.begin(), v.end());

    for(; max != 0 ; max/=10, pow10*=10) {
        for(node::const_iterator elem = v.begin(); elem != v.end(); ++elem) {
                size_t const bucket_num = ( *elem / pow10 ) % 10;
                buckets[ bucket_num ].push_back( *elem );
        }

        node::iterator store_pos = v.begin();
        for(buckets_type::iterator bucket = buckets.begin(); bucket != buckets.end(); ++bucket) {
                for(buckets_type::value_type::const_iterator bucket_elem = bucket->begin();
                        bucket_elem != bucket->end(); ++bucket_elem)
                        *store_pos++ = *bucket_elem;
                bucket->clear();
        }
    }
}

int main(){
    node v;
    v.push_back(0);
    for(int i=1; i<100; i++) {
        int pos = rand() % v.size();
        v.insert(v.begin() + pos, i);
    }
    copy(v.begin(), v.end(), ostream_iterator<unsigned int>(cout, " ")); cout << endl;

    radix_sort(v);
    copy(v.begin(), v.end(), ostream_iterator<unsigned int>(cout, " "));
    return 0;
}
