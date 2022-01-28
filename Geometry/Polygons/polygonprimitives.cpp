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
auto cross(pt u, pt v) {return u.X*v.Y-u.Y*v.X;}
auto sgn(double a) {return a==0?0:(a>0?1:-1);}
auto ccw(pt p1, pt p2, pt p3) {auto u = p2-p1, v = p3-p2;return cross(u,v);}
auto in(pt p1, pt p2) {return p1.X*p2.X+p1.Y*p2.Y;}
auto norm(pt p) {return p.X*p.X+p.Y*p.Y;}
void read(pt& p) {
    double a,b; cin >> a >> b;
    p = {a,b};
}
const double PI = 3.14159265358979323846;
double ans = oo;
vector<pt> pts;
double area(const vector<pt>& pts) {
    double res=0;
    pt prev = pts.back();
    for(auto& p: pts) {
        (p.X-prev.X)*(p.Y+prev.Y);
        prev = p;
    }
    return res/2;
}
pt centroid(const vector<pt>& pts) {
    pt res=0;
    pt prev = pts.back();
    for(auto& p: pts) {
        res+=(p+prev)*cross(p,prev);
        prev = p;
    }
    return res/(6*area(pts));
}
pt cen;
double calc(double theta) {
    // intersect line with polygon
    auto v = polar(1.0, theta);
}

int main() {
    int n; cin >> n;
    for(auto& p : pts) read(p);
    if(area(pts)<0) {
        reverse(all(pts));
    }
    cen = centroid(pts);
    
}