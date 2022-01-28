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
const int mxN = 1e1+1, oo = 1e9;
const int sigma = 27, mask = sigma-1;
const char firstc = 'a'-1;
struct smallmap {
    int ar[sigma]={};
    int& get(char to) {
        return ar[to-firstc];
    }
    void add(char to, int id) {
        ar[to-firstc] = id;
    }
};
string s;
struct node {
    // s[l:r) is the edge above this node
    int l=0,r=0,par=0,suf=-1;
    smallmap mp;
} tree[mxN];
int pp=1;

struct state {
    int id,pos; 
} active = {0,0};

int split(state st) {
    // split edge above tree[id] into s[l:pos) and s[pos:r)
    node& cur = tree[st.id];
    if(cur.r==st.pos) return st.id;
    if(cur.l==st.pos) return cur.par;
    node &nw = tree[pp];
    nw.par = cur.par,nw.l = cur.l, nw.r=st.pos;
    cur.par = pp, cur.l=st.pos,
    tree[nw.par].mp.get(s[nw.l]) = pp;
    nw.mp.add(s[st.pos],st.id);
    return pp++;
} 

state go(state st, int l, int r) {
    // walk down the tree 
    while(l<r) {
        if(st.pos == tree[st.id].r) {
            int to = tree[st.id].mp.get(s[l]);
            if(to) st = {to,tree[to].l+1},l++;
            else return {-1,-1};
        } else {
            if(s[st.pos]!=s[l]) return {-1,-1};
            int dif = tree[st.id].r-st.pos;
            if(r-l<=dif) return {st.id,st.pos+r-l};
            l+=dif, st.pos+=dif;            
        }
    }
    return st;
}
int followlinks(int at) {
    // return suffix link of at, if it doesn't exist, calculates the correct suffix link from the parents suffix link + a walk
    if(at==0) return 0;
    auto& nd = tree[at];
    if(nd.suf!=-1) return nd.suf;
    int to = followlinks(nd.par);
    return nd.suf = split(go(state{to,tree[to].r}, nd.l + (nd.par==0), nd.r));
}
int n;
void ukkadd(int j) {
    while(true) {
        state nwactive = go(active,j,j+1);
        if(nwactive.id!=-1) {
            active=nwactive;
            break;
        }
        auto par = split(active);
        int leaf = pp++;
        tree[leaf] = node{j,n,par};
        tree[par].mp.add(s[j],leaf);
        int suflink = followlinks(par);
        active = {suflink,tree[suflink].r};
        if(!par) break;
    }
}
string t;
void dfs(int at) {
    if(at and tree[at].suf==-1) {
        cout << "*";
    }
    for(char c = firstc;c<firstc+sigma;++c) {
        auto to = tree[at].mp.get(c);
        if(!to) continue;
        int len = tree[to].r-tree[to].l;
        cout << s.substr(tree[to].l, len);
        dfs(to);
        cout << string(len,'-');
    }
}
int main() {
    s= "aababbabaabababac";
    // cin >> s;
    n = s.size();
    for(int i=0;i<n;++i) ukkadd(i);
    dfs(0);
}