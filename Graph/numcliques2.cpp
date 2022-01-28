// #pragma GCC optimize "Ofast"
// #pragma GCC optimize "unroll-loops"
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
const int mxn =50;
ll g[mxn];
// bitset<mxn> g2[mxn];
int n;
bool isclique(ll mask) {
    for(int i=0;i<n;++i) {
        if(1LL<<i & mask and (g[i] & mask) != (mask^(1LL<<i))) {
            return false;
        }
    }
    return true;
}

const int store = 1<<23;
int dp[store];
ll solve(ll mask, int cnt) {
    if(mask<store and dp[mask]!=0) {
        return dp[mask];
    }
    if(isclique(mask)) {
        if(mask<store) dp[mask] = 1LL<<cnt;
        return 1LL<<cnt;;
    }
    // pick node with minimum degree
    int best=n, at;
    for(int i=0;i<n;++i) {
        if((1LL<<i & mask)==0) continue;
        int tmp = __builtin_popcountll(mask&g[i]);
        if(tmp<=best) {
            at = i;
            best = tmp;
        } 
    }
    auto ans = solve(mask&g[at], best)+solve(mask^(1LL<<at),cnt-1);
    if(mask<store) {
        dp[mask]=ans;
    }
    return ans;
}
int main() {
    cin >> n;
    vi a(n);
    iota(all(a),0);
    random_shuffle(all(a));
    for(int i=0;i<n;++i) {
        for(int j=0;j<n;++j) {
            char c; cin >> c;
            g[a[i]] |= ((ll)(c=='1'))<<a[j];
            // g2[i][j] = c=='1';
        }
    }
    cout << solve((1LL<<n)-1,n) << '\n';
}