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
typedef unsigned char uchar;

const int mxN = 2e4+1, oo = 1e9;


int dp[mxN][2][11];
unordered_set<string> dict;
void smax(int& a, int b) {
    if(b<0) return;
    a = max(a,b);
}
int main() {
    int t; cin >> t;
    while(t--) {
        int m,k; cin >> m>> k;
        dict.clear();
        string s; cin >> s;
        int n = s.size();
        for(int i=0;i<=n;++i) {
            for(int j=0;j<=k;++j) {
                dp[i][0][j] = dp[i][1][j] = -oo;
            }
        }
        dp[0][1][0] = 0;
        for(int i=0;i<m;++i) {
            string word;
            cin >> word;
            dict.insert(word);
        }
        for(int i=0;i<=n;++i) {
            for(int l=1;l<=min(i,20);++l) {
                if(dict.count(s.substr(i-l,l))) {
                    for(int j=0;j<=k;++j) {
                        smax(dp[i][1][j], max(dp[i-l][1][j],dp[i-l][0][j])+1);
                    }
                }
            } 
            for(int j=0;j<k;++j) {
                smax(dp[i+1][0][j+1], max(dp[i][0][j+1], dp[i][1][j]));
            }
        }
        int ans = -oo;
        for(int j=0;j<=k;++j) {
            ans = max({ans, dp[n][0][j], dp[n][1][j]});
        }
        cout << ans << '\n';
    }

}