// #pragma GCC optimize "Ofast"
#include "bits/stdc++.h"
#ifdef LOCAL
#include "treinc.h"
#else
#include "treasure.h"
#endif

using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 6*4e5+1, oo = 1e9;
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
        at->val.recalc(at->L?at->L->val.sm:0,at->R?at->R->val.sm:0);
    }
    static void print(node* n) {
        if(n==NULL) return;
        push(n);
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
    int a=0,sm=0,id=0;
    vertex(){}
    vertex(int idd, int v) {
        id = idd;
        a = sm = v;
    }
    void recalc(int lo, int ro) {
        sm = a+lo+ro;
    }
    void recalc() {
        sm = a;
    }
}; 
ostream& operator<<(ostream& c, const vertex& v) {
    return c << v.id;
}
struct linkcut {
    // initially the linkcut tree consists of n disconnected size 1 trees.
    typedef splaytree<vertex> bst;
    typedef bst::node node;
    int n=1;
    node* t=NULL;
    linkcut() {
        t = new node[mxN*2+2];
    }
    int add(int id, int length) {
        t[n++] = node(vertex(id,length));
        return n-1;
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
        t[u].par = t+v; // connect with unmarked edge
    }
    void cut(int u, int v) {
        reroot(u); 
        node* at = expose(v);
        if(at->kid(0)) {
            auto& prev = at->kid(0);
            prev->par=NULL;
            prev->pathtop = true;
            prev = NULL;
        }
        bst::recalc(at);
    }
    int find(int l,node* root) {
        // root is root of BST
        while(root) {
            bst::push(root);
            auto L = root->kid(0), R = root->kid(1);
            int left = (L?L->val.sm:0);
            if(left==l and root->val.a==0) {
                bst::splay(root);
                return root->val.id;
            } else if(l<=left) {
                root = L;
            } else if(left+root->val.a <= l) {
                l-=left+root->val.a;
                root = R;
            } else {
                // on this edge
                l-=left;
                bst::splay(root);
                auto succ = root->kid(1);
                bst::push(succ);
                while(succ->kid(0)) {
                    succ = succ->kid(0);
                    bst::push(succ);
                }
                bst::splay(succ);
                int ans = root->val.id;
                if(succ->val.id == ans) {
                    return ans-root->val.a+l;
                }
                return ans - l;
            }
        }
        return root->val.id;
    }
    ll calc(int u, int v) {
        reroot(u);
        auto root = expose(v);
        // bst::print(root);
        // cout << endl;
        ll length = root->val.sm;
        return find(length/2, root);
    }
    int split(int from, int to, int place, int id) {
        reroot(to); 
        auto root = expose(from);
        auto edge = (root->kid(0)->kid(1)?root->kid(0)->kid(1):root->kid(0));
        int total = edge->val.a;
        bst::splay(edge);  // O(1) splay, just a rotation
        edge->val.a=place;
        bst::recalc(edge);

        int newedge = add(id,total-place);
        int at = add(id,0);
        cut(edge-t,from);
        link(newedge,at);
        link(at,edge-t);
        link(newedge,from);
        return at;
    }


} lc;
map<int,pi> m;
int created=0;
void init() {
    m[1] = {lc.add(1,0), 0};
    created=1;
}

void addedge(int from, int l) {
    int edge = lc.add(created,l);
    int to = lc.add(created,0);
    lc.link(edge,to);
    lc.link(edge,from);
    m[created] = {to,from};
}
int split(int a) {
    auto iter = m.lower_bound(a);
    int at;
    if(iter->first == a) {
        at = iter->second.first;
    } else {
        int dif = iter->first-a;
        auto [to, from] = iter->second;
        at = lc.split(from,to,dif,a);
        m[a] = {at,from};
        m[iter->first] = {to, at};
    }
    return at;
}
int k=0;
void path(int a, int l) {
    k++;
    if(k%20000==0) debug(lc.n);
    // debug(a); debug(l);
    created+=l;
    addedge(split(a),l);
}

int dig(int a, int b) {
    k++;
    if(k%20000==0) debug(lc.n);
    // maybe not even real vertices
    // make these vertices
    auto tmp = lc.calc(split(a), split(b));
    // debug(tmp);
    return tmp;
}
