#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const ll oo = 1e18;
struct BIT {
    vector<ll> fen;
    int n;
    BIT() {}
    BIT(int nn) {
        n=nn;
        fen.resize(n+1);
    }
    void pointupdate(int i, int val) {
        ++i;
        while(i) {
            fen[i]+=val;
            i&=i-1;
        }
    }
    void update(int i, int j, int val) {
        pointupdate(j,val);
        pointupdate(i-1,-val);
    }
    int point(int i) {
        i++;
        ll ans = 0;
        while(i<=n) {
            ans+=fen[i];
            i+=i&(-i);
        }
        return ans;
    }
};
struct HLD {
    int n;
    vi chain, in,sz, parent,d;
    struct edge{
        int a,b,w;
    };
    // vector<edge> edges;
    vvi adj;
    BIT fenwick;
    int cnt;
    void dfs(int at=0, int path=-1) {
        chain[cnt] = (path==-1)?cnt:path;
        int id = in[at] = cnt++;
        if(adj[at].empty()) 
            return;
        int mx=-2,heavy = -1;
        for(int to: adj[at]) {
            if(sz[to] > mx) {
                mx = sz[to];
                heavy=to;
            } 
        }
        assert(heavy!=-1);
        parent[cnt] = id;
        dfs(heavy,chain[id]);
        for(int to: adj[at]) {
            if(to!=heavy) {
                parent[cnt] = id;
                dfs(to);
            }
        }
    }
    HLD(int nn) {
        n=nn;
        adj.assign(n+2,{});
        fenwick = BIT(n);
        chain.assign(n,-1);
        sz.assign(n,1);
        parent.assign(n,-1);
        in.assign(n+2,-99);
    }
    void addedge(int a,int b) {
        // edges.push_back({a,b,c});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void init() {
        vector<pi> q; q.reserve(n); q.emplace_back(0,-1);
        // Graph must be a tree
        // Do a bfs on nodes
        for(int i=0;i<(int)q.size();++i) {
            int at,from; tie(at,from) = q[i];
            for(int j=0;j<(int)adj[at].size();++j) {
                int& to = adj[at][j];
                if(to!=from) {
                    q.emplace_back(to,at);
                } else {
                    swap(to,adj[at].back());
                    adj[at].pop_back();
                    j--;
                }
            }
        }
        assert((int)q.size()==n);
        for(int i=n-1;i>=0;--i) {
            int at = q[i].first;
            for(int to: adj[at]) 
                sz[at]+=sz[to];
        }
        cnt=0;
        dfs();
        assert(cnt==n);
    }
    auto update(int a, int b) {
        // Move pointers a and b up, until 
        // they are in the same chain
        while(chain[a]!=chain[b]) {
            if(a<b) swap(a,b);
            fenwick.update(chain[a], a,1);
            a = parent[chain[a]];
            assert(a!=-1);
        }
        if(a<b) swap(a,b);
        if(a!=b) fenwick.update(b+1,a,1); // don't update edge of the lca
    }
    auto query(int i) {
        return fenwick.point(i);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q; cin >> n >> q;
    HLD hld(n);
    for(int i=0;i<n-1;++i) {
        int a,b; cin >> a >> b;
        hld.addedge(a-1,b-1);
    }
    hld.init();
    while(q--) {
        char type; cin >> type;
        int a,b; cin >> a >> b;
        a = hld.in[a-1], b = hld.in[b-1];
        if(type=='Q')
            cout << hld.query(max(a,b)) << '\n';
        else
            hld.update(a,b);
    }
    return 0;
}