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
const int mxN = 2e5+1, oo = 1e9;
int par[mxN],d[mxN],jmp[mxN];
void add(int i) {
    int p = par[i];
    d[i]=1+d[p];
    if(d[p] - d[jmp[p]] == d[jmp[p]] - d[jmp[jmp[p]]]) jmp[i] = jmp[jmp[p]];
    else jmp[i] = p;
}
int jump(int a, int k) {
    int D = max(0,d[a]-k);
    while(d[a]>D) {
        if(d[jmp[a]]>=D) a = jmp[a];
        else a = par[a];
    }
    return a;
}
int lca(int a, int b) {
    if(d[a]<d[b]) swap(a,b);
    a = jump(a,d[a]-d[b]);
    while(a!=b) {
        if(jmp[a]!=jmp[b]) a=jmp[a],b=jmp[b];
        else a=par[a],b=par[b];
    }
    return a;
}
vi adj[mxN];
void dfs(int at) {
    for(int to: adj[at]) {
        add(to);
        dfs(to);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q; cin >> n >> q;
    for(int i=1;i<n;++i) {
        cin >> par[i],--par[i];
        adj[par[i]].push_back(i);
    }
    dfs(0);
    while(q--) {
        int a,b; cin >> a >> b,--a,--b;
        cout << lca(a,b)+1<<'\n';
    }
}
