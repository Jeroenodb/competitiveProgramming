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
typedef unsigned long long ull;
template<typename V> struct vEB {
    int pwr;
    V mn,mx;
    bool empty=true;
    unordered_map<ull,vEB> chunk;
    vEB* summary=NULL;
    pair<V,V> coord(V a) {
        return {a>>((pwr+1)/2), a&((1<<(pwr/2)) -1)};
    }
    vEB(int _pwr) pwr(_pwr) {

    }
    void insert(const V& a) {
        if(empty) {
            empty=false;
            mn=mx=a;
            return;
        }
        if(a<mn) swap(a,mn);
        mx = max(mn,mx);
        auto [c,i] = coord(a);
        if(!summary) summary = new vEB(pwr/2);
        auto it = chunk.find(c);
        if(it==chunk.end()) {
            auto vb = vEB((pwr+1)/2);
            vb.insert(i);
            chunk[c]=vb;
            summary->insert(c);
        } else it->second.insert(i);
    }
    V pred(const V& a) {
        if(empty or a<=mn) return 0;
        if(!summary) return mn;
        auto [c,i] = coord(a);
        auto it = chunk.find(c);
        if(it!=chunk.end() and it->second.mn<a) {
            return 
        }
    }
};
int main() {
    
}