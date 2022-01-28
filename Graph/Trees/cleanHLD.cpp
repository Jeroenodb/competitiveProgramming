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
    vector<node> seg[2];
    segtree(){}
    segtree(int nn) {
        // ptwo=1;
        // while(ptwo<nn) 
        //     ptwo*=2;  // Want to do walk on segtree ops?
        ptwo = nn;
        seg[0].resize(ptwo*2);
        seg[1].resize(ptwo*2);
    }
    auto query(int l, int r, bool rev) {
        node res[2];
        for(l+=ptwo, r+=ptwo;l and l<=r;l/=2, r/=2) {
            if(l%2==1) res[0] = op(res[0],seg[rev][l++],rev);
            if(r%2==0) res[1] = op(seg[rev][r--], res[1],rev);
        }
        return op(res[0],res[1],rev);
    }
    void pull(int i) {
        for(int rev:{0,1}) 
            seg[rev][i] = op(seg[rev][2*i],seg[rev][2*i+1],rev);
    }
    void build() {
        for(int i=ptwo;i<ptwo*2;++i) {
            seg[1][i] = seg[0][i];
        }
        for(int i = ptwo-1;i>=1;--i) {
            pull(i);
        }
    }
    void update(int i, node val) {
        assert(i>=0 and i<ptwo);
        i+=ptwo;
        seg[1][i] = seg[0][i] = val;
        for(i/=2;i>=1;i/=2) {
            pull(i);
        }
    }
    node& operator[](int i) {return seg[0][i+ptwo];}
};
template<typename node> struct HLD {
    int n;
    vi chain, in, parent, sz;
    vvi adj;
    segtree<node> seg;
    int cnt;
    void dfs(int at=0) {
        in[at] = cnt;
        bool heavy = true;
        for(int to: adj[at]) {
            parent[cnt] = in[at];
            chain[cnt] = heavy?chain[in[at]]:cnt;
            dfs(to), heavy = false;
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
            vector<pi> q; q.reserve(n); 
            q.emplace_back(0,-1);
            for(int i=0;i<(int)q.size();++i) {
                auto [at,from] = q[i];
                if(from!=-1) adj[at].erase(find(all(adj[at]),from)); // remove parent from adjacency list
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
        bool rev = false;
        for(a = in[a],b = in[b];chain[a]!=chain[b];b = parent[chain[b]]) {
            if(a>b) swap(a,b);
            ans  = op(ans,seg.query(chain[b], b,rev)); 
        }
        if(a>b) swap(a,b);
        return op(ans,seg.query(a, b,rev));
    }
    void update(int i, node val) {
        seg.update(in[i], val);
    }
    node& operator[](int i) {
        return seg[in[i]];
    }
};
const int MOD = 998'244'353;
struct F {
    ll a=1,b = 0;
    int operator()(int x) {return (a*x+b)%MOD;}
    friend F op(F u, F v, bool rev=false) {
        if(rev) 
            swap(u,v);
        //  u o v = u(v(x))
        return F{u.a*v.a%MOD, (u.a*v.b + u.b)%MOD};
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q; cin >> n >> q;
    HLD<F> hld(n);
    vector<pi> functions(n);
    for(auto& p : functions) {
        cin >> p.first >> p.second;
    }
    for(int i=0;i<n-1;++i) {
        int a,b; cin >> a >> b;
        hld.addedge(a,b);
    }
    hld.init();
    for(int i=0;i<n;++i) {
        hld[i] = F{functions[i].first,functions[i].second};
    }
    hld.seg.build();
    while(q--) {
        char type; cin >> type;
        int a,b,x; cin >> a >> b >> x;
        if(type=='1')
            cout << hld.query(b,a)(x) << '\n';
        else
            hld.update(a,F{b,x});
    }
}