#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;

#define all(x) begin(x),end(x)
typedef long long ll;

const int mxN = 1e4;
struct flow {
    // Source is Node 0;
    // Sink is node n-1
    // Uses capacity scaling.
    // Runtime: O(|E|^2 *(1+log2(C )))
    struct edge {
        ll f,c;
        int to;
    };
    typedef vector<edge> ve;
    vector<vector<int>> adj;
    vector<edge> edges;
    vector<ll> excess;
    vector<int> h, arcp;
    int n;
    flow(int _n) {
        n=_n;
        h.resize(n);
        excess.resize(n);
        adj.resize(n);
        arcp.resize(n);
    }
    void addEdge(int a, int b, ll w, bool directed = true) {
        adj[a].push_back((int)edges.size());
        adj[b].push_back((int)edges.size()+1);
        edges.push_back({0,w,b});
        edges.push_back({0,directed?0:w,a});
    }
    queue<int> q; 
    void push(int at) {
        for(int i : adj[at]) {
            edge& e = edges[i];
            if(e.f<e.c and h[at] > h[e.to]) {
                ll tmp = min(e.c-e.f, excess[at]);
                excess[at]-=tmp;
                e.f+=tmp;
                if(e.to!=n-1 and excess[e.to]==0) q.push(e.to);
                excess[e.to] += tmp;
                edge& o = edges[i^1];
                o.f-=tmp;
            }
            if(excess[at]==0) return;
        }
        bool renew = false;
        for(int i : adj[at]) {
            auto& e = edges[i];
            if(h[e.to]>=h[at]) {
                h[at]+=1;
                renew = true;
            }
        }
        if(renew) {
            q.push(at);
        }
    }
    ll solve() {
        h[0] = n;
        q.push(0);
        excess[0] = 1e18;
        while(!q.empty()) {
            int at = q.front();
            q.pop();
            push(at);

        }
        return excess[n-1];
    }
};
int main() {
    int n,m; cin >> n >> m;
    flow f(n);
    for(int i=0;i<m;++i) {
        int a,b,c; cin >> a >> b >> c;
        --a, --b;
        f.addEdge(a,b,c);
    }
    cout << f.solve() << endl;
}