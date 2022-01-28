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
const int mxN = 1e5+1;
bitset<mxN> zeroKsubsetsum(vector<pi> ws) {
    bitset<mxN> dp;
    dp[0]=1;
    for(auto [w,k] : ws) {
        bitset<mxN> ndp;
        for(int i=0;i<w;++i) {
            int sm = 0;
            int offset = (k+1)*w;
            for(int j=i;j<mxN;j+=w) {
                if(j-offset>0) sm-=dp[j-offset];
                sm+=dp[j];
                ndp[j] = sm>0;
            }
        }
        swap(dp,ndp);
    }
    return dp;
}


int main() {
    
}