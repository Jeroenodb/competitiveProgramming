#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1, oo = 1e9;

long double choose21(int n) {
    long double res=0;
    for(int i=n+2;i<=2*n;++i) {
        res+=log2l(i);
    }
    for(int i=2;i<n;++i) res-=log2l(i);
    return res;
}
int main() {
    for(int n=100000;n<=100000;++n) {
        cout << n << ": " << choose21(n) << '\n';
    }
}