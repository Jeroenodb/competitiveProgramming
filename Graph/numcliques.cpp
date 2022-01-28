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
const int mxn=50, mxn2 = mxn/2, masks = 1<<mxn2;
int dp[masks>>2];
bitset<masks/4> isclique;
int other[mxn];
int gh[2][mxn2],n,n2;
ll ans = 0;
// implement iteratively, it will be faster
void solve(int i,int mask, int reach) {
    if(i==n2) {
        ans+=dp[reach];
        return;
    }
    if((mask&gh[1][i]) == mask) {
        solve(i+1, mask|(1<<i), reach&other[i]);
    }
    solve(i+1,mask,reach);
}
int main() {
    cin >> n;
    n2 = min(n/2,23);
    vi a(n); iota(all(a),0);
    random_shuffle(all(a));
    for(int ii=0;ii<n;++ii) {
        for(int jj=0;jj<n;++jj) {
            int i = a[ii], j = a[jj];
            char c; cin >> c;
            bool edge = i!=j and c=='1';
            if(!edge) continue;
            if(i<n2 and j<n2)
                gh[0][i]|=1<<j;
            else if(i>=n2 and j<n2)
                other[i-n2]|=1<<j;
            else if(i>=n2 and j>=n2)
                gh[1][i-n2]|= 1<<(j-n2);
        }
    }
    isclique[0] = true;
    dp[0] = 1;
    for(int mask=1;mask<1<<n2;++mask) {
        for(int i=0;;++i) {
            if(mask & 1<<i) {
                if(isclique[mask^(1<<i)] and (mask&gh[0][i])==(mask^(1<<i))) {
                    isclique[mask]=true;
                    dp[mask] = 1;
                }
                break;
            }
        }
    }
    for(int i=0;i<n2;++i) {
        for(int mask = 1; mask<1<<n2;++mask) {
            if(mask & 1<<i) {
                dp[mask] += dp[mask^(1<<i)];
            }
        }
    }
    int whole = (1<<n2)-1;
    // find cliques
    n2=n-n2;
    solve(0,0,whole);

    cout << ans << '\n';
}