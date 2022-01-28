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
const int mxN = 1e5+1, oo = 1e9;
template<class T> struct splaytree {
    // flip
    #define l kid(b)
    #define r kid(b^1)
    #define L kid(0)
    #define R kid(1)
    struct node {
        T val;
        node *c[2] = {NULL,NULL}, *par =NULL;
        bool flip=false,pathtop=true;
        node(const T& v) : val(v) {}
        node*& kid(bool k) {return c[k^flip];}
        node() {}
    };
    static void push(node* at) {
        if(at->flip) {
            if(at->L) at->L->flip^=1;
            if(at->R) at->R->flip^=1;
            swap(at->L,at->R);
            at->flip=0;
        }
    }
    static void recalc(node* at) {
        at->val.recalc();
        if(at->L) at->val.recalc(at->L->val); 
        if(at->R) at->val.recalc(at->R->val);
    }
    static void print(node* n) {
        if(n==NULL) return;
        print(n->L);
        cout << n->val << ' ';
        print(n->R);
    }
    static void rotate(node* n) {
        // Precondition: n is not the root, Postcondition: rotates n to the place of its parent
        // assert(n and !n->pathtop and n->par);
        node* par = n->par;
        push(par);
        push(n);
        if(!par->pathtop) {
            auto gp = par->par;
            if(gp->L==par) gp->L=n;
            else if(gp->R==par) gp->R=n;
        }
        n->par = par->par;
        bool b= n!=par->L;
        par->l = n->r; // Fix right child of current node
        if(n->r) n->r->par = par;
        n->r = par; // Put parent under current node
        par->par = n;
        swap(par->pathtop, n->pathtop);
        recalc(par);
        recalc(n);
    }
    static void splay(node* n) {
        while(!n->pathtop) {
            if(n->par->pathtop) {
                rotate(n);
            } else {
                auto p = n->par, gp = p->par;
                // Double rotations
                if((p->L==n) == (gp->L==p)) {
                    rotate(p);
                } else {
                    rotate(n);
                }
                rotate(n);
            }
        }
        push(n);
    }
    #undef l
    #undef r
    #undef L
    #undef R
};

struct vertex{
    ll a=0,sm=0;
    vertex(){}
    vertex(ll v) {
        a = sm = v;
    }
    void recalc(const vertex& o) {
        sm += o.sm;
    }
    void recalc() {
        sm = a;
    }
}; 
ostream& operator<<(ostream& c, const vertex& v) {
    return c << "Yeah";
}
struct linkcut {
    // initially the linkcut tree consists of n disconnected size 1 trees.
    typedef splaytree<vertex> bst;
    typedef bst::node node;
    int n=0;
    node* t=NULL;
    linkcut() {}
    linkcut(vi& a) {
        n=a.size();
        t = new node[n+1];
        for(int i=0;i<n;++i) {
            t[i] = node(vertex(a[i]));
        }
    }
    node* expose(int u) {
        node *at = NULL, *par = t+u;
        for(;par; at=par,par = par->par) {
            bst::splay(par);
            if(par->kid(1)) {
                par->kid(1)->pathtop = true;
                par->kid(1) = NULL;
            }
            if(at) at->pathtop = false;
            par->kid(1) = at;
            bst::recalc(par);     
        }
        bst::splay(t+u);
        return t+u;
    }
    void reroot(int u) {
        node* root = expose(u); 
        root->flip^=1;
    }
    void link(int u, int v) {
        reroot(u); 
        t[u].par = t+v;         // connect with unmarked edge
    }
    void cut(int u, int v) {
        reroot(u); expose(v);
        node* at = t+v;
        if(at->kid(0)) {
            auto& prev = at->kid(0);
            prev->par=NULL;
            prev->pathtop = true;
            prev = NULL;
        }
        bst::recalc(at);
    }
    ll calc(int u, int v) {
        reroot(u);
        auto root = expose(v);
        return root->val.sm;
    }
    void update(int u, int val) {
        node* root = expose(u);
        root->val.a+=val;
        bst::recalc(root);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q; cin >> n >> q;
    vi a(n);
    for(int& i : a) cin >> i;
    linkcut lc(a);
    for(int i=0;i<n-1;++i) {
        int u,v; cin >> u >> v;
        lc.link(u,v);
    }
    while(q--) {
        int t; cin >> t;
        if(t==0) {
            int u,v,w,x; cin >> u >> v >> w >> x;
            lc.cut(u,v);
            lc.link(w,x);
        } else if(t==1) {
            int p,x; cin >> p >> x;
            lc.update(p,x);
        } else {
            int u,v; cin >> u >> v;
            cout << lc.calc(u,v) << '\n';
        }
    }
    

}