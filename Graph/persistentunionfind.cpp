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
struct persistentarray {
    struct node {
        int c[2]={};
    };
    node* seg = new node[mxN*20];
    int n,roots[mxN]={},p=1;
    int build(int l, int r) {
        int at = p++, mid = (l+r)/2;
        if(l!=r) {
            seg[at].c[0] = build(l,mid);
            seg[at].c[1] = build(mid+1,r);
        } else {
            seg[at].c[0] = -1;
        }
        return at;
    }
    persistentarray(){}
    persistentarray(int nn) {
        n = nn;
        roots[1] = build(0,n-1);
    }
    int getImp(int l, int r, int i, int j) {
        while(true) {
            if(l==r) return seg[i].c[0];
            int mid = (l+r)/2;
            if(j<=mid) {
                r = mid;
                i = seg[i].c[0];
            } else {
                l = mid+1;
                i = seg[i].c[1];
            }
        }
    }
    int updateImp(int l, int r, int i, int j, int val) {
        if(l==r) {
            int at = p;
            seg[p++].c[0] = val;
            return at;
        }
        int mid = (l+r)/2, at= p;
        seg[p++] = seg[i];
        if(j<=mid) {
            seg[at].c[0] = updateImp(l,mid,seg[i].c[0],j,val);
        } else {
            seg[at].c[1] = updateImp(mid+1,r,seg[i].c[1],j,val);
        }
        return at;
    }
    int get(int v, int i) {
        return getImp(0,n-1,roots[v],i);
    }
    int update(int newroot, int v, int i, int val) {
        roots[newroot] = updateImp(0,n-1,roots[v],i,val);
        return roots[newroot];
    }

};
struct persistentDSU : persistentarray {
    persistentDSU(int nn) : persistentarray(nn) {}
    persistentDSU() {}
    pi find(int v, int a) {
        int par = get(v,a);
        while(par>=0) {
            a = par;
            par = get(v,a);
        }
        return {a,-par};
    }
    void unite(int v, int a, int b, int i) {
        auto pa =  find(v,a);
        auto pb =  find(v,b);
        if(pa.second < pb.second) swap(pa,pb);
        if(pa!=pb) {
            update(i,v, pa.first, -pa.second-pb.second);
            update(i,i, pb.first, pa.first);
        } else {
            roots[i] = roots[v];
        }
    }
} dsu; // can be done with a DFS over the versions tree and a rollback DSU.
int main() {
    int n,q; cin >> n >> q;
    dsu = persistentDSU(n);
    for(int i=0;i<q;++i) {
        int t; cin >> t;
        int k,u,v; cin >> k >> u >> v;
        if(t==0) {
            dsu.unite(k+2, u,v, i+2);
        } else {
            cout << (dsu.find(k+2,u)==dsu.find(k+2,v)) << '\n';
        }
    }
}