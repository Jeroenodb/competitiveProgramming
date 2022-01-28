#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,ll> pil;
const int mxN = 3e5+1;
const ll oo = 2e18;
template<typename T> struct heap {
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
vector<pil> adj[mxN], rev[mxN];
int nxt[mxN]; 
ll dist[mxN];
struct el {
    int at;
    ll d;
    bool operator<(const el& o) const {return d<o.d;}
    bool operator>(const el& o) const {return d>o.d;}
};
void dijkstra(int s, int n) {
    fill(dist,dist+n,oo);
    dist[s]=0;
    priority_queue<el, vector<el>,greater<el>> pq;
    pq.push({s,0});
    fill(nxt,nxt+n,-1);
    while(!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if(dist[c.at]!=c.d) continue;
        for(auto [to,d] : rev[c.at]) {
            d+=c.d;
            if(d<dist[to]) {
                nxt[to]=c.at;
                dist[to]=d;
                pq.push({to,d});
            }
        }
    }
}
void fixEdges(int n) {
    for(int i=0;i<n;++i) {
        if(dist[i]==oo) {
            adj[i].clear();
            continue;
        }
        sort(all(adj[i]));
        if(nxt[i]!=-1) adj[i].erase(find(all(adj[i]),pil{nxt[i],dist[i]-dist[nxt[i]]}));
        {
            vector<pil> good;
            for(auto [to,w] : adj[i]) {
                if(dist[to]!=oo) {
                    good.push_back({to,w});
                } 
            }
            adj[i]=good;
        }
        for(auto& [to,w] : adj[i]) {
            w+=dist[to]-dist[i];
        }
        sort(all(adj[i]),[&](pil a, pil b) {return a.second<b.second;});
    }
}
heap<el>* heaps[mxN] = {};
bitset<mxN> vis;
heap<el>* getheap(int at) {
    if(at==-1) return NULL;
    if(vis[at]) return heaps[at];
    vis[at]=true;
    if(!adj[at].empty()) heaps[at] = new heap<el>{el{at,adj[at][0].second}};
    heaps[at]=merge(heaps[at],getheap(nxt[at]));
    return heaps[at];
}
struct state {
    heap<el>* at=NULL;
    int edge=0;
    ll cost=0;
    bool operator<(const state& o) const { return cost>o.cost;}
};
int main() {
    int n,m,s,t,k; cin >> n >> m >> s >> t >> k;
    while(m--) {
        int u,v,c; cin >> u >> v >> c;
        adj[u].push_back({v,c}),rev[v].push_back({u,c});
    }
    dijkstra(t,n);
    fixEdges(n);
    state beg = {getheap(s)};
    vector<ll> ans;
    ans.push_back(dist[s]==oo?-1:dist[s]);
    priority_queue<state> pq;
    if(beg.at) {
        beg.cost = dist[s]+beg.at->key.d;
        pq.push(beg);
    }
    while(!pq.empty() and (int)ans.size()<k) {
        auto c = pq.top(); pq.pop();
        auto hp = c.at;
        ans.push_back(c.cost);
        if(c.edge==0) {
            // walk in heap
            for(int i: {0,1}) if(hp->c[i]) {
                pq.push(state{hp->c[i], 0, c.cost-hp->key.d+hp->c[i]->key.d});
            }
        }
        int at = c.at->key.at;
        auto [to,d] = adj[at][c.edge];
        if(c.edge<(int)adj[at].size()-1) {
            // go to next edge
            ll d2 = adj[at][c.edge+1].second;
            pq.push({state{hp,c.edge+1,c.cost+d2-d}});
        }
        // take current edge
        if(getheap(to)) {
            pq.push({heaps[to],0,c.cost+heaps[to]->key.d});
        }
    } 
    ans.resize(k,-1);
    for(auto i : ans) cout << i << '\n';

}