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
    #define L c[0]
    #define R c[1]
    struct node {
        T val;
        node *c[2] = {NULL,NULL}, *par =NULL;
        bool flip=false,pathtop=true;
        node(const T& v) : val(v) {}
        node() {}
    };
    static void doFlip(node* at) {
        if(!at) return;
        at->flip^=1, swap(at->c[0],at->c[1]);
    }
    static void push(node* at) {
        if(at->flip) {
            doFlip(at->L),doFlip(at->R);
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
        assert(n and !n->pathtop and n->par);
        node* par = n->par;
        push(par),push(n);
        if(!par->pathtop) {
            auto gp = par->par;
            if(gp->L==par) gp->L=n;
            else if(gp->R==par) gp->R=n;
        }
        n->par = par->par;
        bool b= n!=par->L;
        #define l c[b]
        #define r c[b^1]
        par->l = n->r; // Fix right child of current node
        if(n->r) n->r->par = par;
        n->r = par; // Put parent under current node
        #undef l
        #undef r
        par->par = n;
        swap(par->pathtop, n->pathtop);
        recalc(par),recalc(n);
    }
    static void splay(node* n) {
        while(!n->pathtop) {
            if(n->par->pathtop) {
                rotate(n);
            } else {
                auto p = n->par, gp = p->par;
                // Double rotations
                if((p->L==n) == (gp->L==p)) rotate(p);
                else rotate(n);
                rotate(n);
            }
        }
        push(n);
    }
    #undef L
    #undef R
};

struct vertex{
    // int id,sm;
    vertex(){}
    vertex(int idd) {
        // id = sm = idd;
    }
    void recalc(const vertex& o) {
        // sm += o.sm;
    }
    void recalc() {
        // sm = id;
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
    linkcut(int nn) {
        n=nn;
        t = new node[n];
        for(int i=0;i<n;++i) {
            t[i] = node(vertex{i});
        }
    }
    node* expose(int u) {
        node *at = NULL, *par = t+u;
        for(;par; at=par,par = par->par) {
            bst::splay(par);
            if(par->c[1]) {
                par->c[1]->pathtop = true;
                par->c[1] = NULL;
            }
            if(at) at->pathtop = false;
            par->c[1] = at;
            bst::recalc(par);     
        }
        bst::splay(t+u);
        return t+u;
    }
    void reroot(int u) {
        node* root = expose(u); 
        bst::doFlip(root);
    }
    void link(int u, int v) {
        reroot(u); 
        t[u].par = t+v;         // connect with unmarked edge
    }
    void cut(int u, int v) {
        reroot(u); expose(v);
        node* at = t+v;
        if(at->c[0]) {
            auto& prev = at->c[0];
            prev->par=NULL;
            prev->pathtop = true;
            prev = NULL;
        }
        bst::recalc(at);
    }
    vertex calc(int u) {
        auto root = expose(u);
        return root->val;
    }
    node* root(int u) {
        node* root = expose(u);
        while(root->c[0]) {
            bst::push(root);
            root= root->c[0];
        }
        bst::splay(root);
        return root;
    }
};

linkcut lc;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("dynacon.in","r",stdin);
    // freopen("output.out","w",stdout);
    int n,m; cin >> n >> m;
    lc = linkcut(n+2);
    for(int i=0;i<m;++i) {
        string type; cin >> type;
        int a,b; cin >> a >> b;
        if(type=="add") {
            lc.link(b,a);
        } else if(type=="rem") {
            lc.cut(b,a);
        } else {
            auto ra = lc.root(a), rb = lc.root(b);
            cout << (ra==rb?"YES\n":"NO\n");
        }
    }
    

}