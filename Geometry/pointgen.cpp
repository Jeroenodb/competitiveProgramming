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
    int n = 1e2;
    cout << n << endl;
    set<pair<int,int>> s;
    while(s.size()!=n) {
        int x = rand()%1000, y = rand()%1000;
        if(!s.count({x,y})) {
            s.insert({x,y});
        }
    }
    for(auto p: s) {
        cout << p.first << ' ' << p.second << endl;
    }

}