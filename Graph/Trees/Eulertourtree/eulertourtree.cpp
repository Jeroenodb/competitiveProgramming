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
    #define l c[b]
    #define r c[b^1]
    #define L c[0]
    #define R c[1]
    struct node {
        T val;
        node *c[2] = {NULL,NULL}, *par =NULL;
        node(const T& v) : val(v) {}
        node() {}
        bool isroot() {return par==NULL;}
    };

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
        // assert(n and !n->isroot() and n->par);
        node* par = n->par;
        if(!par->isroot()) {
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
        recalc(par);
        recalc(n);
    }
    static void splay(node* n) {
        while(!n->isroot()) {
            if(n->par->isroot()) {
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
    }
    static node* merge(node* a, node* b) {
        if(a==NULL) return b;
        if(b==NULL) return a;
        splay(a);
        while(a->R) a = a->R;
        splay(a),splay(b);
        a->R = b;
        b->par = a;
        recalc(a);
        return a;
    }
    static node* merge(vector<node*> nodes) {
        int n= nodes.size();
        node* root = nodes[0];
        for(int i=1;i<n;++i) root = merge(root,nodes[i]);
        return root;
    }
    #undef l
    #undef r
    // #undef L
    // #undef R
};

struct info{
    ll a=0,sm=0;
    info(){}
    info(ll v) {
        a = sm = v;
    }
    void recalc(const info& o) {
        sm += o.sm;
    }
    void recalc() {
        sm = a;
    }
}; 
struct ETT {
    typedef splaytree<info> BST;
    typedef splaytree<info>::node node;
    node ver[mxN];
    map<pi,node*> edges;
    void link(int u, int v) {
        BST::splay(ver+u);
        BST::splay(ver+v);
        if(ver[u].par) return;
        node* uright = ver[u].R, *vright = ver[v].R;
        ver[u].R=ver[v].R = NULL;
        if(uright) uright->par = NULL;
        if(vright) vright->par = NULL;
        BST::recalc(ver+u), BST::recalc(ver+v);
        node* to = new node(), *from = new node();
        BST::merge({ver+u,to,vright,ver+v,from,uright});
        edges[{u,v}]=to;
        edges[{v,u}]=from;
    }
    void cut(int u, int v) {
        auto to = edges[{u,v}], from = edges[{v,u}];
        // check whether to and from are oriented correctly
        BST::splay(from); BST::splay(to); BST::splay(from);
        if(from->R != to) swap(to,from);
        node* fromleft = from->L;
        if(fromleft) fromleft->par = NULL;
        if(to->L) to->L->par=NULL;
        if(to->R) to->R->par = NULL;
        BST::merge(fromleft, to->R);
        delete to, delete from;
        edges.erase({u,v}), edges.erase({v,u});
    }
    info calctree(int u) {
        BST::splay(ver+u);
        return ver[u].val;
    }
};
int main() {
    
}