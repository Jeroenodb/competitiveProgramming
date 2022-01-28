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
ll cost=0;
template<typename T, int N=110> struct mystack {
    T st[N];
    int p = 0;
    void reset(){p=0;}
    T& top() {return st[p-1];}
    void pop(){p--;}
    void push(const T& val) {st[p++] = val;}
    int size() {return p;}
    bool empty() {return !p;}
};
template<class T>
struct BBbst {
    // all keys in leafs
    struct Node {
        T key; 
        int sz=1;
        Node *l=NULL,*r=NULL;
    };
    Node* mem = new Node[10*mxN];
    Node* newnode(const Node& t) {
        *mem=t;
        return mem++;
    }
    double alpha=0.75;
    Node* root = NULL;
    mystack<Node*> insertst;
    BBbst () {}
    Node* search(const T& key) { // returns last node in path to this key, or the node with the key itself
        auto prv=root, at = root;
        while(at) {
            prv=at;
            if(key < at->key) at = at->l;
            else at = at->r;
        }
        return prv;
    }
    bool bad(Node* rt) {
        int total = rt->sz;
        return rt->l->sz>alpha*total or rt->r->sz>alpha*total;
    }
    void insert(const T& key) {
        if(!root) {
            root = newnode({key});
            return;
        }
        mystack<Node*>& st = insertst;
        st.reset();
        // stack<Node*> st;
        st.push(root);
        while(st.top()) {
            auto at = st.top();
            at->sz++;
            if(key<at->key) st.push(at->l);
            else st.push(at->r);
        }
        st.pop(); // null
        auto leaf = st.top();
        if(leaf->key==key) return;
        leaf->l = newnode({key});
        leaf->r = newnode({leaf->key});
        if(leaf->key<key) swap(leaf->l,leaf->r);
        leaf->key=leaf->r->key;
        if(st.size()+1<log2(root->sz)*2.5) return;
        for(auto i=st.size()-1;i>=0;--i) {
            // auto child = st.top(); st.pop();
            if(!bad(st.st[i])) continue;
            rebuild(st.st[i],st.st[i]->sz);
            break;
        }
    }
    template<typename IT> friend Node* build(int i, int j, const vector<Node*>& order, IT& freenode) {
        if(i==j-1) return order[i];
        int mid = (i+j)/2;
        auto at = *(freenode++);
        *at ={order[mid]->key, 0, build(i,mid,order,freenode), build(mid,j,order,freenode)};
        at->sz=at->l->sz+at->r->sz;
        return at;
    }
    friend void rebuild(Node* rt, int sz) {
        cost+=sz;
        // put them in array
        vector<Node*> order,internal={rt};
        order.reserve(sz), internal.reserve(sz-1);
        vector<Node*> st; st.reserve(sz*2-1);
        {
            Node* tmp = rt;
            while(tmp) st.push_back(tmp),tmp=tmp->l;
        }
        // inorder traversal
        while(!st.empty()){
            auto at = st.back();st.pop_back();
            if(!at->l) order.push_back(at);
            else if(at!=rt) internal.push_back(at);
            at = at->r;
            while(at) st.push_back(at),at=at->l;
        }
        assert(order.size()==sz);
        auto it = internal.begin();
        build(0,(int)order.size(),order,it);
    }
    void print(Node * rt=NULL, int d=0) {
        if(rt==NULL) rt = root;
        if(rt->l) print(rt->l,d+3);
        cout << string(d,' ') << rt->key << '\n';
        if(rt->r) print(rt->r,d+3);
    }
};
// std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
int main() {
    BBbst<int> sc;
    for(int i=0;i<300000;++i) {
        sc.insert(i);
        // sc.print();
        // cout << "-----\n";
        // if(i%1000==0) debug(i);
    }
    debug(cost);
    debug("done");

}