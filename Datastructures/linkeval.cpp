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
struct linkeval {
    // max queries on path to root, plus max= update on roots
    vi par,label, sz, tlink;
    vector<bool> root;
    linkeval(int n) {
        par.assign(n,-1);
        tlink.assign(n,-1);
        sz.assign(n,1);
        root.assign(n,true);
        label.assign(n,-oo);
    }
    int eval(int i) {
        // evaluate function on path with path compression
        if(par[i]<0) return label[i];
        label[i] = max(eval(par[i]),label[i]);
        if(par[par[i]]>=0) par[i] = par[par[i]];
        return label[i];
    }
    void unite(int& i, int& j) {
        // link virtual trees with size heuristic
        if(sz[i]<sz[j]) {
            swap(i,j);
            swap(root[i],root[j]);
            swap(par[i],par[j]);
        } else tlink[i]=tlink[j];
        par[j]=i;
        sz[i]+=sz[j];
    }
    int find(int i) {
        eval(i);
        if(par[i]>=0) i=par[i];
        return i;
    }
    void update(int i, int val) {
        i = find(i);
        label[i]= max(label[i],val);
        int j = tlink[i];
        while(j!=-1 and label[j]<label[i]) {
            label[j]=label[i];
            unite(i,j);
            j=tlink[i];
        }
    }
    void link(int i, int j) {
        i=find(i), j= find(j);
        // place j under i
        assert(root[i]);
        assert(root[j]);
        root[j]=false;
        par[i]+=par[j];
        if(par[i]<=2*par[j]) {
            // first case: put all small trees under i
            for(;j!=-1;j=tlink[j]) {
                par[j]=i;
                sz[i]+=sz[j];
            }
        } else {
            // second case: Link all virtual trees of i to i itself
            // Put j as whole subtree below
            for(int small=tlink[i], nw=-1;small!=-1;small=nw) {
                par[small]=i;
                sz[i]+=sz[small];
                nw = tlink[small];
                tlink[small]=-1;
            }
            tlink[i] = j;
            update(i,label[i]);
        }
    }
};
int main() {
    int n=4;
    linkeval le(n);
    le.update(0,2);
    le.update(1,1);
    le.update(2,5);
    le.update(3,0);
    le.link(2,3);
    le.link(1,2);
    le.link(0,1);

    debug(le.eval(1));
    debug(le.eval(2));
}