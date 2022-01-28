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
    #define l c[b]
    #define r c[b^1]
    #define L c[0]
    #define R c[1]
    struct node {
        T val;
        node *c[2] = {}, *par =NULL;
    };
    node *root=NULL;
    friend ostream& operator<<(ostream& c,node* n) {
        if(n==NULL) 
            return c << "(empty)";
        c << '(';
        if(n->L) c << n->L << ',';
        c << n->val;
        if(n->R) c << ',' << n->R;
        return c << ')';
    }
    void rotate(node* n) {
        // Precondition: n is not the root
        // Rotates n to the place of its parent
        // Corrects the pointers
        assert(n->par);
        assert(n->par->L == n or n->par->R == n);
        node* par = n->par;
        if(par->par) {
            auto gp = par->par;
            if(gp->L==par) {
                gp->L=n;
            } else {
                gp->R=n;
            }
        }
        n->par = par->par;
        bool b= n!=par->L;
        // Fix right child of current node
        par->l = n->r;
        if(n->r) 
            n->r->par = par;
        // Put parent under current node
        n->r = par;
        par->par = n;
    }
    void splay(node* n) {
        if(!n or n==root) return;
        bool finished =false;
        while(!finished) {
            if(!n->par->par) {
                finished = true;
                rotate(n);
            } else {
                auto p = n->par, gp = p->par;
                if(gp==root) finished = true;
                // Double rotations
                if((p->L==n) == (gp->L==p)) {
                    rotate(p);
                } else {
                    rotate(n);
                }
                rotate(n);
            }
        }
        root = n;
    }
    node* insert(T val) {
        if(!root) {
            root = new node{val};
            return root;
        }
        auto p = root;
        while(true) {
            node* tmp;
            if(val < p->val) {
                tmp = p->L;
                if(!tmp) {
                    tmp = p->L = new node{val,NULL,NULL,p};
                    splay(tmp);
                    return tmp;
                }
            } else if(p->val == val) {
                splay(p);
                return NULL;
            } else {
                tmp = p->R;
                if(!tmp) {
                    tmp = p->R = new node{val,NULL,NULL,p};
                    splay(tmp);
                    return tmp;
                }
            }
            p = tmp;
        }
    }
    node* succ(node* n, bool b) {
        #warning Just splay at the front of this op.
        node* p;
        if(n->r) {
            p = n->r;
            while(p->l) 
                p = p->l;
        } else {
            p = n->par; 
            auto pp = n;
            while(p and p->r == pp) {
                pp=p;
                p = p->par;
            }
        }
        splay(p);
        return p;
    }
    node* insert(node* c, node* n, bool b) {
        if(c->r) {
            auto p = c->r;
            while(p->l) 
                p = p->l;
            p->l = n;
            n->par = p;
        } else {
            c->r = n;
            n->par=c;
        }
        splay(n);
    }
    void erase(node* n) {
        splay(n);
        if(n->L) {
            auto c = n->L;
            root = c;
            c->par = NULL;
            while(c->R) {
                c=c->R;
            }
            splay(c);
            assert(!c->R);
            c->R = n->R;
            if(n->R) {
                n->R->par = c;
            }
        } else {
            root = n->R;
            if(n->R) {
                n->R->par=NULL;
            }
        }
        delete n;

    }
    #undef l
    #undef r
    #undef L
    #undef R
};

int main() {
    splaytree<int> s;
    for(int i=0;i<10;++i) {
        int tmp = rand()%100;
        auto p  = s.insert(tmp);
        
        // cout << "insert " << tmp << ' ';
        // debug(s.root);

    }
    
    debug(s.root);
    debug(s.succ(s.root,1));
    s.erase(s.root);
    debug(s.root);
    
}