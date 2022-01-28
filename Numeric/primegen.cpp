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
const int mxN = 2e5+1, oo = 1e9;
const ll store=(INT_MAX+1LL)/30;
bitset<store> sieve={},ans;
int primes[6161172+3]; int p=0;
void makesieve() {
    for(int i = 2; i < store/2;++i) {
        if(!sieve[i]) {
            primes[p++] = i;
            for(ll j = i*2;j<store;j+=i) {
                sieve[j] = true;
            }
        }
    }
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    auto t0 = chrono::high_resolution_clock::now();
    makesieve();
    auto t1 = chrono::high_resolution_clock::now();
    cout << (t1-t0).count()*1e-9 << '\n';
    cout << p << endl;
    cout << "Done sieving" << endl;
    int t; cin >> t;
    // while(t--) {
    //     int m,n; cin >> m >> n;
    //     ans.reset();
    //     if(m==1) ans[0] = true;
    //     for(int i=0;i<p and primes[i]*primes[i] <= n;++i) {
    //         auto prime = primes[i];
    //         // find smallest multiple bigger than m
    //         // ans = prime*k >= m
    //         for(int j = prime*max(2,(m+prime-1)/prime); j<=n;j+=prime) {
    //             ans[j-m] = true;
    //         }
    //     }
    //     for(int i=0;i<=n-m;++i) {
    //         if(!ans[i]) {
    //             cout << i+m << '\n';
    //         }
    //     }
    //     cout << '\n';
    // }
}