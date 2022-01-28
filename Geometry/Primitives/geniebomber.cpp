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
typedef complex<double> pt;
#define X real()
#define Y imag()
auto norm(pt p) {return p.X*p.X+p.Y*p.Y;}
void read(pt& p) {
    double a,b; cin >> a >> b;
    p = {a,b};
}
const double step = 1.0/128;
int main() {
    int n; cin >> n;
    vector<pair<pt,double>> circles(n);
    for(auto& c : circles) {
        read(c.first);
        cin >> c.second;
    }
    ll good = 0,total=0;
    for(double x = step/2;x<1;x+=step) {
        for(double y = step/2;y<1;y+=step) {
            pt c = {x,y};
            for(auto& [p,r]:circles) {
                if(norm(c-p)<r*r) {
                    good++;
                    break;
                }
            }
            total++;
        }
    }
    cout << 100.0*good/total << '\n';
}