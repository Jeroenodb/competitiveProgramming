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
const int mxN = 5.5e5+1, oo = 1e9;
int par[mxN],d[mxN],jmp[mxN],x[mxN];
void add(int i) {
    int p = par[i];
    d[i]=1+d[p];
    if(d[p] - d[jmp[p]] == d[jmp[p]] - d[jmp[jmp[p]]]) jmp[i] = jmp[jmp[p]];
    else jmp[i] = p;
}
int jump(int a, int k) {
    int D = max(0,d[a]-k);
    while(d[a]>D) {
        if(d[jmp[a]]>=D) a = jmp[a];
        else a = par[a];
    }
    return a;
}
struct persistentq {
    int head=0,len=0;
} pq[mxN];
int p=1;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q; cin >> Q;
    for(int i=1;i<=Q;++i) {
        char c; cin >> c;
        int t; cin >> t,t++;
        auto& q = pq[i];
        if(c=='1') {
            q = pq[t];
            q.len--;
            cout << x[jump(t,q.len)] << '\n';
        } else {
            q.head = p;
            q.len=pq[t].len+1;
            par[q.head]=pq[t].head;
            add(p++);
            cin >> x[q.head];
        }
    }
}