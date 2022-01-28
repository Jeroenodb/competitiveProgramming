#include "bits/stdc++.h"
#include "elephants.h"
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
    int sm=0, id;
    bool white=false;
    vertex(int idd, bool b){id=idd, white = b, sm=!b;}
    vertex(){}
    void recalc(const vertex& o) {
        sm += o.sm;
    }
    void recalc() {
        sm = !white;
    }
}; 
ostream& operator<<(ostream& c, const vertex& v) {
    return c << v.id << (v.white?"W ":"B ");
}
struct linkcut {
    // initially the linkcut tree consists of n disconnected size 1 trees.
    typedef splaytree<vertex> bst;
    typedef bst::node node;
    int n=0;
    node* t=NULL;
    linkcut() {}
    linkcut(int N) {
        n=N;
        t = new node[n+1];
        // for(int i=0;i<n;++i) {
        //     t[i] = node(vertex());
        // }
    }
    void add(int i, bool white) {
        int id = i;
        if(i>=n and i<2*n) i-=n;
        t[i] = node(vertex(id,white));
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
        assert(at->kid(0) == t+u);
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
        // bst::print(root);
        return root->val.sm;
    }

};

int n,l;
map<pi,int> m;
linkcut lc;
vi xs;
void init(int N, int L, int X[]) {
    l=L;
    lc = linkcut(N*2+2);
    n = N;
    xs = vi(X,X+n);
    lc.add(n*2,true), lc.add(n*2+1,true);
    for(int i=0;i<n;++i) {
        int x = X[i];
        m[{x,i}] = i;
        m[{x+L,i+n}]= i+n;
        lc.add(i,false), lc.add(i+n,true);
        lc.link(i,i+n);
    }

    m[{-2*oo,n*2}] = n*2;
    m[{oo*2,n*2+1}] = n*2+1;
    for(int i=0;i<n;++i) {
        auto iter = m.upper_bound({X[i]+L,i+n});
        lc.link(i+n,iter->second);
    }
    auto iter = m.upper_bound({-2*oo+L,2*n});
    lc.link(n*2,iter->second);
}

int update(int i, int y) {
    int X = xs[i];
    // white node -> cut 
    lc.cut(i+n,m.upper_bound({X+l,i+n})->second);
    auto fix = [](int x, int j) {
        auto iter = m.find({x,j});
        auto maybe = prev(iter);
        m.erase(iter);
        if(maybe->second>=n) {
            // node is white and thus connected
            lc.cut(j, maybe->second);
            lc.link(maybe->second, next(maybe)->second);
        }
    };
    fix(X+l,i+n);
    fix(X,i);

    xs[i] = y;
    // debug(xs);
    auto fix2 = [](int x, int j) {
        auto iter = m.lower_bound({x,j});
        auto maybe = prev(iter);
        if(maybe->second>=n) {
            // node is white and thus connected
            lc.cut(maybe->second, next(maybe)->second);
            lc.link(maybe->second, j);

        }
        m[{x,j}] = j;
    };
    auto iter = m.upper_bound({y+l,i+n});
    lc.link(i+n,iter->second);
    fix2(y+l,i+n);
    fix2(y,i);
    return lc.calc(n*2,n*2+1);
}
