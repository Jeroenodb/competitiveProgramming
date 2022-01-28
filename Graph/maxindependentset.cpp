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
const int mxn=40, mxn2 = mxn/2, masks = 1<<mxn2;
int dp[masks], from[masks];
bitset<masks> isindependent;
bitset<mxn2> gh[2][mxn2],other[mxn];;
bitset<mxn> g[mxn];
void maxk(int& a, int b) {
    a = max(a,b);
}
int main() {
    int n,m; cin >> n >> m;
    int n2 = n/2;
    for(int i=0;i<m;++i) {
        int a,b; cin >> a >> b;
        if(a>b) swap(a,b);
        g[a][b]  = g[b][a] = 1;
        if(a<n2 and b<n2) {
            gh[0][a][b] = gh[0][b][a] = 1;
        } else if(a<n2 and b>=n2) {
            other[b-n2][a] = 1;
        } else {
            gh[1][a-n2][b-n2] = gh[1][b-n2][a-n2] = 1;
        }
    }
    isindependent[0] = true;
    for(int mask=1;mask<1<<n2;++mask) {
        int cnt = 0;
        for(int i=0;i<n2;++i) if(1<<i & mask) cnt++;
        for(int i=0;i<n2;++i) {
            if(mask & 1<<i) {
                if(isindependent[mask^(1<<i)] and (mask&gh[0][i].to_ulong())==0) {
                    isindependent[mask]=true;
                    dp[mask] = cnt;
                    from[mask] = mask;
                }
                break;
            }
        }
    }
    for(int mask = 1; mask<1<<n2;++mask) {
        for(int i=0;i<n2;++i) {
            if((mask & 1<<i) == 0) {
                int o = mask|1<<i;
                if(dp[mask]> dp[o]) {
                    dp[o] = dp[mask];
                    from[o] = from[mask];
                } 
            }
        }
    }
    int whole = (1<<n2) -1;
    n2 = (n+1)/2;
    int ans = dp[whole];
    ll sol = from[whole];
    isindependent.reset();
    isindependent[0] = true;
    for(int mask=1;mask<1<<n2;++mask) {
        for(int i=n2-1;i>=0;--i) {
            if(mask & 1<<i) {
                if(isindependent[mask^(1<<i)] and (mask&gh[1][i].to_ulong())==0) {
                    isindependent[mask] = true;
                    int o = whole;
                    int cnt =0;
                    for(int j=0;j<n2;++j) {
                        if(mask&1<<j) {
                            o&=~other[j].to_ulong();
                            cnt++;
                        }
                    }
                    if(dp[o]+cnt > ans) {
                        ans = dp[o]+cnt;
                        sol = from[o]|ll(mask)<<(n/2);
                    }
                }
                break;
            }
        }
    }
    vi nodes;
    for(int i=0;i<n;++i) {
        if(sol & 1LL<<i) {
            nodes.push_back(i);
        }
    }
    cout << nodes.size() << '\n' << nodes << '\n';
}