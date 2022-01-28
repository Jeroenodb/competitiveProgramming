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
struct myset {
    vi perm,rank;
    int size=0;
    myset(){}
    myset(int n) {
        perm.resize(n),rank.resize(n);
    }
    void insert(int i) {
        int pos = rank[i];
        if(pos<size) return;
        swap(perm[size],perm[pos]);
        swap(rank[perm[size]],rank[i]);
        size++;
    }
    void erase(int i) {
        int pos = rank[i];
        if(pos>=size) return;
        size--;
        swap(perm[size],perm[pos]);
        swap(rank[perm[size]],rank[i]);
    }
} 
int main() {
    
}