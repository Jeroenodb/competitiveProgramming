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
const int mxN = 1e5+10, oo = 1e9;


vector<pi> adj[mxN];
vector<array<int,3>> updates[mxN];

bitset<mxN> vis;
int sz[mxN];
vector<pi> par[mxN];
auto update(int at,int d, int c, int t) {
    for(auto& [p,dist]: par[at]) {
        if(dist<=d) {
            auto& v = updates[p];
            int myd = d-dist;
            while(!v.empty() and v.back()[0]<=myd) v.pop_back();
            v.push_back({myd,c,t});
        }
    }
}
int D,P;
void dfsz(int at) {
    if(P) par[at].push_back({P,D});
    sz[at]=1;
    vis[at]=true;
    for(auto [to,w]: adj[at])if(!vis[to]) {
        D+=w;
        dfsz(to);
        D-=w;
        sz[at]+=sz[to];
    }
    vis[at]=false;
}
int centroid(int at) {
    int from=at, n=sz[at];
    bool done=false;
    while(!done) {
        done=true;
        for(auto [to,w]: adj[at]) if(!vis[to] and to!=from) {
            if(sz[to]*2>n) {
                from = at, at = to, done=false;
                break;
            }
        }
    }
    return at;
}
void decomp(int at, int p, int ww) {
    D=ww,P=p;
    dfsz(at);
    int c = centroid(at);
    par[c].push_back({c,0});
    vis[c]=true;
    for(auto [to,w]: adj[c]) if(!vis[to]) {
        decomp(to,c,w);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i=0;i<n-1;++i) {
        int a,b,w; cin >> a >> b >> w;
        adj[a].emplace_back(b,w);
        adj[b].emplace_back(a,w);
    }
    decomp(1,0,0);
    int q; cin >> q;
    for(int t=0;t<q;++t) {
        int type,v; cin >> type >> v;
        if(type==2) {
            pi ans = {-1,0};
            // go through all CD parents
            for(auto [p,d]: par[v]) {
                auto& vv = updates[p];
                auto it = lower_bound(vv.rbegin(),vv.rend(),array<int,3>{d,0,0});
                if(it!=vv.rend()) {
                    ans = max(ans,{(*it)[2],(*it)[1]});
                }
            }
            cout << ans.second << '\n';
        } else {
            int d,c; cin >> d >> c;
            update(v,d,c,t);
        }
    }
}