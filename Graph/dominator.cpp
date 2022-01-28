#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
const int mxN = 1e5+5, oo = 1e9;
int in[mxN],sdom[mxN]= {}, idom[mxN]; // relabeled vertices
struct linkeval {
    int label[mxN], par[mxN];
    linkeval(int n) {
        iota(label,label+n+1, 0);
        iota(par,par+n+1, 0);
    }
    int find(int i, bool x=false) {
        if(i==par[i]) {
            return x?-1:i;
        }
        int newpar = find(par[i],true);
        if(newpar<0) return x?i:label[i];
        if(sdom[label[par[i]]] < sdom[label[i]])
            label[i] = label[par[i]];
        par[i] = newpar;
        return x?newpar:label[i];
    }
    void link(int i, int j) {
        par[i] = j;
    }

};
vi adj[mxN], rev[mxN], sdomof[mxN];

int vertex[mxN], par[mxN]; int cnt = 0;
void dfs(int at) {
    in[at] = ++cnt;
    vertex[cnt] = at;
    for(int to: adj[at]) {
        if(!in[to]) {
            sdom[cnt+1]=idom[cnt+1] = par[cnt+1] = in[at];
            dfs(to);
        }
        rev[in[cnt]].push_back(in[at]);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("dominator.in","r",stdin);
    int n,m; cin >> n >> m;
    for(int i=0;i<m;++i) {
        int a,b; cin >> a >> b; --a,--b;
        assert(a!=b);
        adj[a].push_back(b);
    }
    sdom[0]= idom[0] = 0;
    dfs(0);
    linkeval le(n);
    for(int i=n;i>=1;--i) {
        for(int from: rev[i]) {
            sdom[i] = min(sdom[i], sdom[le.find(from)]);
        }
        if(i>1) sdomof[sdom[i]].push_back(i);
        for(int w: sdomof[i]) {
            int u = le.find(w);
            if(sdom[u]==sdom[w]) idom[w] = sdom[w];
            else idom[w] = u;
        }
        if(i>1) le.link(i, par[i]);
    }
    for(int i=1;i<=n;++i) {
        if(idom[i]!=sdom[i]) idom[i] = idom[idom[i]];
    }
    int at = in[n-1];
    vi ans = {1};
    // cout << "Path retrievalling" << endl;
    while(at!=0) {
        ans.push_back(1+vertex[at]);
        at = idom[at];
        // cout << at << endl;
    }
    sort(all(ans));
    cout << ans.size() << '\n' << ans << '\n';

}