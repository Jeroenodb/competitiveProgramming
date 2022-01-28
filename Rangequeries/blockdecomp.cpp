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
template<typename T> struct blocktree {
    vector<T> a;
    using IT = typename vector<T>::iterator;
    int B;
    struct block {
        IT s;
        ll lazy=0;
        // maybe extra stuffs for the DS
        vector<T> myA;
        void build() {
            // build the data structure with the values from [s,s+B)
            myA = vector<T>(s,s+B);
            sort(all(myA));
        }
        void push() {

        }
        T query() {

        }
    };
    vector<block> bs;
    blocktree(int n) {
        a.resize(n);
        B= sqrt(n+0.5);
        bs.resize(n/B);
        for(int i=0;i<n/B;++i) {
            bs[i].s = a.begin()+i*B;
        }
    }
    void init() {
        for(auto& i : bs) i.build();
    }
    void update(int l, int r, T lazy) {
        T res=0;
        int bl = l/B, br = r/B;
        bs[bl].push();
        for(int lim = min(r,bl*B+B-1);l<=lim;++l) {
            // update a[l]
        }
        bs[bl].build();
        if(bl==br) return;
        for(++bl;bl<br;++bl) {
            // update bs[bl]
            bs[bl];
        }
        bs[br].push();
        for(int lim = br*B;r>=lim;--r) {
            // update a[r]
            
        }
        bs[br].build();
    }
    T query(int l, int r) {
        T res=0;
        int bl = l/B, br = r/B;
        bs[bl].push();
        for(int lim = min(r,bl*B+B-1);l<=lim;++l) {
            // add contribution from a[l] to answer

        }
        bs[bl].build();
        if(bl==br) return;
        for(++bl;bl<br;++bl) {
            res+=bs[bl].query();
        }
        bs[br].push();
        for(int lim = br*B;r>=lim;--r) {
            // add contribution from a[r] to answer

        }
        bs[br].build();
        return res;
    }
};

int main() {
    
}