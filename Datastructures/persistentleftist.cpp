#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1, oo = 1e9;
template<typename T>struct heap {
    T key;
    heap *c[2] = {};
    int r=1;
    friend int rnk(heap* a) {
        return a?a->r:0;
    } 
    void fix() {
        if(rnk(c[0])<rnk(c[1])) swap(c[0],c[1]);
        r=rnk(c[1])+1;
    }
    friend heap* merge(heap* a, heap* b) {
        if(!a) return b;
        if(!b) return a;
        if(a->key>b->key) swap(a,b);
        heap* res = new heap(*a);
        res->c[1] = merge(a->c[1],b);
        res->fix();
        return res;
    }
    
};
int main() {
    heap<int>* rt = NULL;
    for(int i=0;i<20;++i) {
        rt = merge(rt,new heap<int>{i});
    }

}