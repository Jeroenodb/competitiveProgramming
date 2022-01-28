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
#ifdef DEBUG
const int mxN = 1e1+1, oo = 1e9;
#else
const int mxN = 2e5+10, oo = 1e9;
#endif
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
int ind[mxN],outd[mxN];
void dfs2(int at) {
    ind[at]=cnt++;
    for(int to : adj[at]) 
        dfs2(to);
    outd[at]=cnt-1;
}

void solve() {
    int n,m; 
    if(!(cin >> n >> m)) {
        exit(0);
    }
    for(int i=0;i<n;++i) adj[i].clear(),rev[i].clear(),sdomof[i].clear();
    vector<pi> es(m);
    for(auto& [a,b]: es) {
        cin >> a >> b; --a,--b;
        adj[a].push_back(b);
    }
    cnt=0;
    vis.reset();
    dfs(0);
    for(int i=0;i<n;++i) sdom[i]=i;
    linkeval le(n);
    for(int i=cnt-1;i>=0;--i) {
        for(int from: rev[i]) {
            if(from<i) sdom[i] = min(sdom[i],from);
            else sdom[i] = min(sdom[i], sdom[le.find(from)]);
        }
        if(i) sdomof[sdom[i]].push_back(i);
        for(int w : sdomof[i]) {
            int u = le.find(w); // vertex with lowest sdom inside path (sdom[w], w]
            if(sdom[u]==sdom[w]) dom[w] = sdom[w];
            else dom[w] = u; // can't know if dominator of u is already set, need to wait
        }
        if(i) le.link(i, par[i]);
    }
    for(int i=0;i<n;++i) if(dom[i]!=sdom[i]) dom[i]=dom[dom[i]]; // fix dominator, because now we know
    for(int i=0;i<n;++i) adj[i].clear();
    for(int i=1;i<cnt;++i) adj[dom[i]].push_back(i);
    // adj contains dom tree
    cnt=0;
    dfs2(0);
    vi ans;
    for(int i=0;i<m;++i) {
        auto& [a,b] = es[i];
        if(!vis[a]) continue;
        a=in[a],b=in[b];
        // check if b is dominator of a
        if(ind[a]<ind[b] or outd[b]<ind[a])
            ans.push_back(i+1);
    }
    cout << ans.size() << '\n' << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(true) solve();
}