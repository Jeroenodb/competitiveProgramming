#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
namespace {
template<class T1, class T2> void prin(const pair<T1,T2>& x);
template<class T> void prin(const vector<T>& x);
template<class T> void prin(const T& x) {cout << x;}
template<class H, class... T> void prin(const H& h, const T&... t) {prin(h); prin(t...); }
template<class T1, class T2> void prin(const pair<T1,T2>& x) {prin(x.first,' ',x.second);}
template<class T> void prin(const vector<T>& x) {for(int i=0;i<(int)x.size();++i) prin(i==0?"":" ",x[i]);}
template<class... T> void print(const T&... t) {prin(t..., "\n"); }
#define debug(x) cout << #x << ": "; print(x)
}
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int oo = 1e9;
struct segtree {
    int ptwo;
    vi seg;
    // Weights are stored in nodes instead of edges
    // seg[node+ptwo] = weight of Edge to parent
    segtree(){}
    segtree(int nn) {
        ptwo=1;
        while(ptwo<nn) 
            ptwo*=2;
        seg.assign(ptwo*2,-oo);
    }
    int query(int l, int r) {
        assert(l>=0 and l<ptwo and r >=0 and r<ptwo);
        l+=ptwo; r+=ptwo;
        int res = -oo;
        while(l<=r) {
            if(l%2==1) res = max(res,seg[l++]);
            if(r%2==0) res = max(res,seg[r--]);
            l/=2; r/=2;
        }
        return res;
    }
    void update(int i, int val) {
        assert(i>=0 and i<ptwo);
        i+=ptwo;
        seg[i] = val;
        for(i/=2;i>=1;i/=2) {
            seg[i] = max(seg[2*i],seg[2*i+1]);
        }
    }
    void build() {
        for(int i=ptwo-1;i>0;--i) {
            seg[i] = max(seg[i*2],seg[i*2+1]);
        }
    }
};
struct HLD {
    int n;
    vi chain, in,sz, parent,d;
    struct edge{
        int a,b,w;
    };
    vector<edge> edges;
    vvi adj;
    segtree seg;
    int cnt;
    void dfs(int at=0, int path=-1) {
        chain[at] = (path==-1)?at:path;
        in[at] = cnt++;
        if(adj[at].empty()) 
            return;
        int mx=0,heavy = -1;
        for(int to: adj[at]) {
            if(sz[to] > mx) {
                mx = sz[to];
                heavy=to;
            } 
        }

        dfs(heavy,chain[at]);
        for(int to: adj[at]) {
            if(to!=heavy)
                dfs(to);
        }
    }
    HLD(int nn) {
        n=nn;
        adj.assign(n,{});
        seg = segtree(n);
        chain.assign(n,0);
        sz.assign(n,1);
        parent.assign(n,0);
        d.assign(n,0);
        in.assign(n,0);
    }
    void addedge(int a,int b, int c) {
        edges.push_back({a,b,c});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void init() {
        vector<pi> q; q.reserve(n); q.emplace_back(0,-1);
        // Graph must be a tree
        parent[0] = -1;
        for(int i=0;i<n;++i) {
            int at,from; tie(at,from) = q[i];
            for(int j=0;j<(int)adj[at].size();++j) {
                int& to = adj[at][j];

                if(to!=from) {
                    parent[to] = at;
                    d[to] = d[at]+1;
                    q.emplace_back(to,at);
                } else {
                    swap(to,adj[at].back());
                    adj[at].pop_back();
                    j--;
                }
            }
        }
        assert(q.size()==n);
        for(int i=n-1;i>=0;--i) {
            int at = q[i].first;
            for(int to: adj[at]) sz[at]+=sz[to];
        }
        cnt=0;
        dfs();
        assert(edges.size()==n-1);
        assert(cnt==n);
        for(auto& e: edges) {
            if(d[e.a]>d[e.b]) 
                swap(e.a,e.b);
            seg.seg[seg.ptwo+in[e.b]] = e.w;
        }
        seg.build();
    }
    auto query(int a, int b) {
        // Move pointers a and b up, until 
        // they are in the same chain
        int ans = -oo;
        while(chain[a]!=chain[b]) {
            if(d[chain[a]]<d[chain[b]]) 
                swap(a,b);
            ans = max(ans,seg.query(in[chain[a]], in[a]));
            a = parent[chain[a]];
        }
        if(d[a]>d[b]) swap(a,b);
        ans = max(ans,seg.query(in[a]+1, in[b]));
        return ans;
    }
    void update(int i, int val) {
        seg.update(in[edges[i].b], val);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        HLD hld(n);
        for(int i=0;i<n-1;++i) {
            int a,b,c; cin >> a >> b >> c;
            hld.addedge(a-1,b-1,c);
        }
        hld.init();
        while(true) {
            string s; cin >> s;
            if("DONE"==s) break;
            int a,b; cin >> a >> b;
            if(s=="QUERY") {
                cout << hld.query(a-1,b-1) << '\n';
            } else if ("CHANGE"==s) {
                hld.update(a-1,b);
            } else 
                assert(false);
        }
    }
    return 0;
}