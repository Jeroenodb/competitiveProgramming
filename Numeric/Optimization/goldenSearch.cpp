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

template<typename F> double minimize(double lo, double hi, F f) {
    static const double EPS = 1e-7, r = 2.0/(sqrt(5)+1);
    double x1 = lo*r + hi*(1-r), x2 = lo*(1-r) + hi*r
    double f1 = f(x1), f2 = f(x2);
    while(hi-lo>EPS) {
        if (f1 < f2) { //change to > to find maximum
            hi = x2; x2 = x1; f2 = f1;
            x1 = hi - r*(hi-lo); f1 = f(x1);
        } else {
            lo = x1; x1 = x2; f1 = f2;
            x2 = lo + r*(hi-lo); f2 = f(x2);
        }
    }
    return f((lo+hi)/2);
}

int main() {
    
}