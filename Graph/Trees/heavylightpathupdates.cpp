#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const ll oo = 1e18;
template<typename node> struct segtree {
    int ptwo=0;
    vector<node> seg;
    segtree(){}
    segtree(int nn) {
        ptwo=1;
        while(ptwo<nn) 
            ptwo*=2;
        seg.resize(ptwo*2);
    }
    auto query(int l, int r) {
        node res;
        for(l+=ptwo, r+=ptwo;l and l<=r;l/=2, r/=2) {
            if(l%2==1) res = op(res,seg[l++]);
            if(r%2==0) res = op(res,seg[r--]);
        }
        return res;
    }
    void update(int i, node val) {
        assert(i>=0 and i<ptwo);
        i+=ptwo;
        seg[i] = seg[i]+val;
        for(i/=2;i>=1;i/=2) {
            seg[i] = op(seg[2*i],seg[2*i+1]);
        }
    }
};
template<typename node> struct HLD {
    int n;
    vi chain, in, parent, sz;
    vvi adj;
    segtree<node> seg;
    int cnt;
    void dfs(int at=0, int path=0) {
        in[at] = cnt;
        chain[cnt++] = path;
        bool heavy = true;
        for(int to: adj[at]) {
            parent[cnt] = in[at];
            dfs(to,heavy?path:cnt);
            heavy = false;
        }
    }
    HLD(int nn) {
        n=nn;
        adj.assign(n,{});
        seg = segtree<node>(n);
        in.assign(n,-1);
        sz.assign(n,1);
    }
    void addedge(int a,int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void init() {
        {
            vector<pi> q; q.reserve(n); q.emplace_back(0,-1);
            for(int i=0;i<(int)q.size();++i) {
                auto [at,from] = q[i];
                if(from!=-1) 
                    adj[at].erase(find(all(adj[at]),from)); // remove parent from adjacency list
                for(int to: adj[at])
                    q.emplace_back(to,at);
            }
            for(int i=n-1;i>=0;--i) {
                auto at = q[i].first;
                auto heavy = adj[at].begin();
                for(auto to = heavy; to!=adj[at].end();++to){
                    sz[at]+=sz[*to]; // calculate sizes of subtrees
                    if(sz[*to]>sz[*heavy]) {
                        swap(*to,*heavy); // move heaviest child to front
                    }
                }
            }
        }
        chain.assign(n,-1);
        parent.assign(n,-1);
        cnt=0;
        dfs();
    }
    auto query(int a, int b) {
        node ans;
        for(a = in[a],b = in[b];chain[a]!=chain[b];b = parent[chain[b]]) {
            if(a>b) swap(a,b);
            ans = op(ans,seg.query(chain[b], b));
        }
        if(a>b) swap(a,b);
        ans = op(ans,seg.query(a, b));
        return ans;
    }
    void update(int i, node val) {
        seg.update(in[i], val);
    }
};
struct MAX {
    ll v = 0;
    friend MAX op(const MAX& a, const MAX& b) {return MAX{max(a.v,b.v)};}
    friend MAX operator+(const MAX& a, const MAX& b) {return MAX{a.v+b.v};}
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    HLD<MAX> hld(n);
    for(int i=0;i<n-1;++i) {
        int a,b; cin >> a >> b;
        hld.addedge(a-1,b-1);
    }
    hld.init();
    int q; cin >> q;
    while(q--) {
        char type; cin >> type;
        int a,b; cin >> a >> b;
        if(type=='G')
            cout << hld.query(a-1,b-1).v << '\n';
        else
            hld.update(a-1,MAX{(ll)b});
    }
}