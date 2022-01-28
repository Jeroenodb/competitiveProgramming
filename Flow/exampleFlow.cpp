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
        vector<int> ans = {1};
        while(at!=n-1) {
            for(int i: adj[at]) {
                auto& e = edges[i];
                if(e.f>0) {
                    at = e.to;
                    ans.push_back(at+1);
                    e.f--;
                    break;
                }
            }
        }
        return ans;
    }
};
struct medge {
    int a,b;
    pair<int,int> getordered() const {
        if(a<b) 
            return {a,b};
        else 
            return {b,a};
    }
    friend bool operator<(const medge& m,const medge& o) {
        return m.getordered() < o.getordered();
    }
};

int main() {
    int n,m; cin >> n >> m;
    flow f(n);
    map<medge,bool> edges;
    for(int i=0;i<m;++i) {
        int a,b; cin >> a >> b;
        --a,--b;
        auto iter = edges.find({a,b});
        if(iter!=edges.end()) {
            iter->second = false;
        } else {
            edges[{a,b}] = true;
        }
    }
    for(auto& p: edges) {
        auto [e,directed] = p;
        f.addEdge(e.a,e.b,1,p.second);
    }
    edges.clear();
    auto tmp =  f.solve();
    cout << tmp << endl;
    while(tmp--) {
        auto v = f.findpath();
        cout << v.size() << endl;
        for(int i: v) cout << i << ' ';
        cout << endl;
    }
    
}