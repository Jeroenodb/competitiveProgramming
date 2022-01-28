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
struct DSU{
    vector<int> parent;
    vector<bool> deleted;
    void add(int p) {
        parent.push_back(p);
    }
    void remove(int a) {
        deleted[a] = true;
    }
    int find(int a) {
        if(!deleted[a]) return a;
        return parent[a] = find(parent[a]);
    }
    int findparent(int a) {
        return parent[a] = find(parent[a]);
    }
} dsu;

struct subdata {
    int depth, id;
    int lazy=0, mind, lca;
    subdata(int d, int myid) {
        depth = mind = depth;
        lca = id = myid;
    }
    subdata(){}
};
struct Node{
    static int size(Node* a) {
        return (a?a->sz:0);
    }
    static int mind(Node* a) {
        return (a?a->d.mind+a->d.lazy:oo);
    }
    Node* kids[2] = {};
    Node* parent=NULL;
    int sz,priority;
    subdata d;
    Node(int depth, int id) {
        d = subdata(depth,id);
        priority = rand();
        sz = 1;
    }
    void prop() {
        if(!d.lazy) return;
        d.depth+=d.lazy;
        d.mind+=d.lazy;
        if(kids[0]) kids[0]->d.lazy+=d.lazy;
        if(kids[1]) kids[1]->d.lazy+=d.lazy;
        d.lazy=0;
    }
    void recalc() {
        sz=1+size(kids[0])+size(kids[1]);
        assert(!d.lazy);
        d.mind = min({d.depth, mind(kids[0]), mind(kids[1])});
        d.lca = d.id;
        for(int i :{0,1}) {
            if(mind(kids[i])==d.mind) 
                d.lca = kids[i]->d.lca;
            if(kids[i]) kids[i]->parent = this;
        }
    }
    int pos(Node* prev = NULL) {
        int ans = 0;
        if(kids[0]!=prev) {
            ans+= size(kids[0]);
        }
        if(parent) return ans+parent->pos();
        return ans;
    }
    array<Node*,2> split(int lastinleft) {
        prop();
        if(size(kids[0])>=lastinleft) {
            if(kids[0]==NULL) {
                return {NULL,this};
            }
            auto ans = kids[0]->split(lastinleft);
            kids[0]=ans[1];
            recalc();
            return {ans[0],this};
        } else {
            if(kids[1]==NULL) {
                return {this,NULL};
            }
            lastinleft-=size(kids[0])+1;
            auto ans = kids[1]->split(lastinleft);
            kids[1]=ans[0];
            recalc();
            return {this,ans[1]};

        }
    }
    void print() {
        prop();
        if(kids[0]) kids[0]->print();
        cout << d.id << ' ';
        if(kids[1]) kids[1]->print();
    }
};

Node* merge(Node* a, Node* b) {
    if(a==NULL) return b;
    if(b==NULL) return a;
    a->prop();
    b->prop();
    if(a->priority<b->priority) {
        a->kids[1] = merge(a->kids[1],b);
        a->recalc();
        return a;
    } else {
        b->kids[0] = merge(a,b->kids[0]);
        b->recalc();
        return b;
    }
}


vector<Node*> in, out;
Node* root=NULL;
void add(int par) {
    auto pin = in[par]->pos();
    in[par]->prop();

    int id = in.size(), mydepth = in[par]->d.depth;
    auto tup = root->split(pin);
    auto newel = new Node(mydepth+1,id);
    in.push_back(newel);
    out.push_back(NULL);
    if(!out[par]) {
        out[par] = new Node(mydepth,par);
        newel = merge(newel, out[par]);
    } else {
        newel = merge(newel,new Node(mydepth,par));
    }
    root = merge(merge(tup[0], newel), tup[1]);
    dsu.add(par);
}
void deletenode(int id) {
    assert(id!=0);
    if(out[id]==NULL) {
        // easier case
        return;
    }
    int l = in[id]->pos(), r = out[id]->pos();
    auto tup = root->split(r+1);
    auto tup2 = tup[0]->split(l);
    auto tup3 = tup2[1]->split(1);
    auto tup4 = tup3[1]->split(r-l-1);
    delete tup3[0];
    delete tup4[1];
    if(tup4[0]) tup4[1]->d.lazy--;
    root = merge(tup2[0],merge(tup4[0],tup[1]));
    dsu.remove(id);
}
int lca(int a, int b) {
    int l = in[a]->pos(), r = in[b]->pos();
    auto tup = root->split(r+1);
    auto tup2 = tup[0]->split(l);
    int ans =  dsu.find(tup2[1]->d.lca);
    root = merge(tup2[0],merge(tup2[1],tup[1]));
    return ans;
}
void print(Node* treap) {
    if(treap==NULL) {
        cout << "Empty" << endl;
        return;
    } 
    treap->print();
    cout << endl;
}

int main() {
    // hold euler tour of tree in treap
    // tree starts with one node
    in.push_back(new Node(0,0));
    out = {in[0]};
    root = in[0];
    dsu.add(0);

}