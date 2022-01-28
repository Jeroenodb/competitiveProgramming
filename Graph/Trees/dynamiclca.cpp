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
        deleted.push_back(false);
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

struct node {
    vi jmp;
    int d;
    node(int par, int depth) {
        jmp = {par};
        d= depth;

    }
    int getjmp(int i) {
        if(i>(int)jmp.size()-1) return 0;
        return jmp[i];
    }
};
vector<node> nodes;
int jump(int at, int k) {
    for(int i=0;(1<<i)<=k;++i) {
        if((1<<i)&k) {
            at = nodes[at].getjmp(i);
        }
    }
    return at;
}

void add(int par) {
    nodes.push_back(node(par,nodes[par].d+1));
    dsu.add(par);
    auto& n = nodes.back();
    while(n.jmp.back()!=0) {
        int s= n.jmp.size()-1;
        n.jmp.push_back(nodes[n.jmp.back()].getjmp(s));
    }
}
void remove(int id) {
    dsu.remove(id);
}
int lca(int a, int b) {
    if(nodes[a].d>nodes[b].d) swap(a,b);
    b = jump(b,nodes[b].d-nodes[a].d);
    if(a==b) return dsu.find(a);
    for(int i = nodes[a].jmp.size()-1;i>=0;--i ) {
        if(nodes[a].getjmp(i) != nodes[b].getjmp(i)) {
            a = nodes[a].getjmp(i);
            b = nodes[b].getjmp(i);
        }
    }
    return dsu.findparent(a);
}
int main() {
    dsu.add(0);
    nodes = {node(0,0)};
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if(t==1) {
            int par; cin >> par;
            add(par);
        } else if(t==2) {
            int id; cin >> id;
            remove(id);
        } else {
            int a,b; cin >> a >> b;
            cout << lca(a,b) << '\n';
        }
    }

}