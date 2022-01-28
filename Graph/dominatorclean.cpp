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
int sdom[mxN], dom[mxN];
struct linkeval {
    vi label, par;
    linkeval(int n) {
        label.resize(n);
        iota(all(label), 0);
        par.resize(n);
        iota(all(par), 0);
    }
    int find(int i, bool x=false) {
        if(i==par[i]) {
            return x?-1:i;
        }
        int newpar = find(par[i],true);
        if(newpar<0) 
            return x?par[i]:label[i]; // under the root
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
bitset<mxN> vis;
int par[mxN], in[mxN],cnt=0;
void dfs(int at) {
    in[at]=cnt++;
    vis[at]=true;
    for(int to : adj[at]) {
        if(!vis[to]) {
            dfs(to);
            par[in[to]]=in[at];
        }
        rev[in[to]].push_back(in[at]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin >> n >> m;
    for(int i=0;i<m;++i) {
        int a,b; cin >> a >> b; --a,--b;
        adj[a].push_back(b);
    }
    dfs(0);
    for(int i=0;i<n;++i) sdom[i]=i;
    linkeval le(n);
    vis.reset();
    for(int i=n-1;i>=0;--i) {
        for(int from: rev[i]) {
            if(from<i) sdom[i] = min(sdom[i],from);
            else sdom[i] = min(sdom[i], sdom[le.find(from)]);
        }
        if(i) sdomof[sdom[i]].push_back(i);
        for(int w : sdomof[i]) {
            int u = le.find(w); // vertex with lowest sdom inside path (sdom[w], w]
            if(sdom[u]==sdom[w]) dom[w] = sdom[w];
            else dom[w] = u,vis[w]=true; // can't know if dominator of u is already set, need to wait
        }
        if(i) le.link(i, par[i]);
    }
    for(int i=0;i<n;++i) if(vis[i]) dom[i]=dom[dom[i]]; // fix dominator, because know we know
    
    vi ans = {1};
    int at = in[n-1];
    for(int i=0;i<n;++i) par[in[i]]=i;
    while(at!=0) {
        ans.push_back(1+par[at]);
        at = dom[at];
    }
    sort(all(ans));
    cout << ans.size() << '\n' << ans << '\n';
}