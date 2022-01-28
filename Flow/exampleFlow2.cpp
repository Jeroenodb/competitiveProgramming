#include <iostream>
#include <vector>
#include <bitset>
#include <set>
#include <map>
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
    int n;
    ll scale=0;
    flow(int _n) {
        n=_n;
        adj.resize(n);
    }
    void addEdge(int a, int b, ll w, bool directed) {
        scale = max(w,scale);
        adj[a].push_back((int)edges.size());
        adj[b].push_back((int)edges.size()+1);
        edges.push_back({0,w,b});
        edges.push_back({0,directed?0:w,a});
    }
    bitset<mxN> visited;
    ll dfs(int at=0, ll mn=1e18) {
        if(at==n-1) return mn;
        visited[at] = true;
        for(int i: adj[at]) {
            auto& e = edges[i];
            if(!visited[e.to] and e.f+scale<=e.c) {
                ll tmp = min(mn,e.c-e.f);
                tmp =  min(tmp,dfs(e.to,tmp));
                if(tmp) {
                    e.f+=tmp;
                    auto& o = edges[i^1];
                    o.f-=tmp;
                    return tmp;
                }
            }
        }
        return 0;
    }

    ll solve() {
        ll res = 0;
        while(true) {
            visited.reset();
            ll tmp = dfs();
            if(tmp!=0) res+=tmp;
            else {
                scale/=2;
                if(!scale) break;
            }
        }
        return res;
    }
    vector<int> findpath() {
        int at = 0;
        vector<int> ans;
        while(at!=n-1) {
            for(int i: adj[at]) {
                auto& e = edges[i];
                if(e.f>0) {
                    at = e.to;
                    ans.push_back(at);
                    e.f--;
                    break;
                }
            }
        }
        return ans;
    }
};

int main() {
    int n,m,k; cin >> n >> m >> k;
    flow f(n+m+2);
    for(int i=1;i<=n;++i) {
        f.addEdge(0,i,1,true);
    }
    for(int i=n+1;i<=m+n;++i) {
        f.addEdge(i,m+n+1,1,true);
    }
    for(int i=0;i<k;++i) {
        int a,b; cin >> a >> b;
        b+=n;
        f.addEdge(a,b,1,true);
        
    }
    auto tmp =  f.solve();
    cout << tmp << endl;
    while(tmp--) {
        auto v = f.findpath();
        cout << v[0] << ' '<< v[1]-n << endl;
    }
    
}