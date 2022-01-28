#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
const int mxN = 1e5+1;
const ll oo = 1e18;
vector<vector<pair<int,int>>> adj;
vector<vector<int>> dag;
bitset<mxN> reaches;
void dfsdag(int at) {
    reaches[at] = true;
    for(int to: dag[at]) {
        if(!reaches[to]) dfsdag(to);
    }
}
int n;
struct AP {

    int n;
    vector<vector<int>> adj;
    AP(int _n) {
        n = _n;
        low.resize(n);
        d.resize(n);
        adj.resize(n);
        ans.insert(0); ans.insert(n-1);
    }
    vector<int> low, d;
    set<int> ans;
    bitset<mxN> visited;
    void dfs(int at=0, int from=-1, int depth=0) {
        visited[at] = true;
        d[at]=depth;
        low[at] = depth;
        for(auto to: adj[at]) {
            if(to==from) continue;
            if(!visited[to]) {
                dfs(to,at,depth+1);
                if(low[to]>=d[at]) {
                  ans.insert(at);
                }
                low[at] = min(low[at], low[to]);
            } else {
                low[at] = min(low[at],d[to]);
            }
        }
    } 

    void solve() {
        adj.resize(n);
        dfsdag(n-1);
        for(int i=0;i<n;++i) {
            if(!reaches[i]) continue;
            for(int to:dag[i] ) {
                adj[i].push_back(to);
                adj[to].push_back(i);
            }
        }
        dfs();
    }

};
int main() {
    int m; cin >> n >> m;
    adj.resize(n); dag.resize(n);
    for(int i=0;i<m;++i) {
        int a,b,w; cin >> a >> b >> w;
        --a,--b;
        adj[a].push_back({b,w});
    }
    AP ap(n);
    vector<ll> dist(n,oo);
    dist[0] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>> > pq;
    pq.push({0,0});
    while(!pq.empty()) {
        auto [d,at] = pq.top();
        pq.pop();
        if(dist[at]<d) continue;
        for(auto& [to, w] : adj[at]) {
            if(d+w < dist[to]) {
                dag[to].clear();
                dag[to].push_back(at);
                dist[to] = d+w;
                pq.push({d+w,to});
            } else if(d+w==dist[to]) {
                dag[to].push_back(at);
            }
        }
    }
    ap.solve();

    cout << ap.ans.size() << endl;
    for(int i: ap.ans) {
        cout << i+1 << ' ';
    }

}