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
    node* root = NULL;
    node* insert(const T& val) {
        // insertion
        auto nw = new node(val);
        if(!root) {
            return root=nw;
        }
        node* cur = root;
        while(true) {
            if(val < cur->val) {
                if(cur->L) cur = cur->L;
                else {
                    cur->L = nw;
                    nw->par = cur;
                    break;
                }
            } else {
                if(cur->R) cur = cur->R;
                else {
                    cur->R = nw;
                    nw->par = cur;
                    break;
                }
            }
        }
        splay(nw);
        return nw;
    }
    void erase(const T& val) {
        // erase node
        node* cur = root;
        while(true) {
            assert(cur);
            if(val < cur->val) cur = cur->L;
            else if(val>cur->val) cur = cur->R;
            else break;
        }
        splay(cur);
        if(cur->L) {
            auto left = cur->L;
            left->par = NULL;
            while(left->R) left = left->R;
            splay(left);
            left->R = cur->R;
            if(cur->R) cur->R->par = left;
            recalc(left);
        } else {
            root = cur->R;
            if(root) root->par=NULL;
        }
        delete cur;
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
    void splay(node* n) {
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
        // assert(n->isroot());
        root = n;
    }
    #undef l
    #undef r
    // #undef L
    // #undef R
};

struct info{
    int a=0,sm=0;
    info(){}
    bool operator<(const info& o) const {return a<o.a;}
    bool operator>(const info& o) const {return a>o.a;}
    info(int v) {
        a = sm = v;
    }
    void recalc(const info& o) {
        sm = __gcd(sm,o.sm);
    }
    void recalc() {
        sm = a;
    }
}; 
ostream& operator<<(ostream& c, const info& i) {
    return c << i.a;
}
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
void gen() {
    ofstream fout("gcd.in");
    int q = 10;
    fout << q << '\n';
    multiset<int> s;
    for(int i=0;i<q;++i) {
        if(rnd(0,1)==0) {
            fout << "+ ";
            int v = rnd(1,100);
            fout << v << '\n';
            s.insert(v);
        } else {
            if(s.empty()) {
                --i;
                continue;
            }
            vi cur(s.begin(),s.end());
            int g = cur[rnd(0,(int)cur.size()-1)];
            s.erase(s.lower_bound(g));
            fout << "- " << g << '\n';
        }
    }
    fout.close();
}
void test() {
    // freopen("gcd.in","r",stdin);
    splaytree<info> tree;
    int q; cin >> q;
    while(q--) {
        char op; cin >> op;
        int x; cin >> x;
        if(op=='+') {
            tree.insert(info(x));
        } else {
            tree.erase(info(x));
        }
        if(!tree.root) {
            cout << "1\n";
        } else {
            cout << tree.root->val.sm << '\n';
        }
        // tree.print(tree.root); cout << '\n';
    }
}
int main() {
    // while(true) {
    //     gen();
    //     test();
        
    // }
    test();
}