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
int main() {
    int s,n; cin >> s >> n;
    vi ws(n), ks(n); for(int& i: ws) cin >> i;
    for(int& i : ks) cin >> i;
    bitset<mxN> dp;
    dp[0] = true;
    for(int j=0;j<n;++j) {
        int w=ws[j], myk = ks[j];
        for(int k=0;k<w;++k) {
            int last = -oo;
            for(int i=k;i<=s;i+=w) {
                if(dp[i]) {
                    last = i;
                }
                dp[i] = last+(ll)w*myk >=i;
            }
        }
    }
}