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
typedef complex<int> pt;
#define X real()
#define Y imag()
auto cross(pt u, pt v) {return (ll)u.X*v.Y-(ll)u.Y*v.X;}
auto sgn(ll a) {return a==0?0:(a>0?1:-1);}
auto ccw(pt p1, pt p2, pt p3) {auto u = p2-p1, v = p3-p2;return cross(u,v);}
auto in(pt p1, pt p2) {return (ll)p1.X*p2.X+(ll)p1.Y*p2.Y;}
auto norm(pt p) {return (ll)p.X*p.X+(ll)p.Y*p.Y;}
bool comp(const pt& a, const pt& b) { return a.X<b.X or (a.X==b.X and a.Y < b.Y);}
void read(pt& p) {
    int a,b; cin >> a >> b;
    p = {a,b};
}
int quadrant(pt p) {
    if(p.X==0 and p.Y==0) return -1;
    if(p.X>=0 and p.Y>0) return 0;
    if(p.X<0 and p.Y>=0) return 1;
    if(p.X<=0 and p.Y<0) return 2;
    return 3;
}
int inpoly(const vector<pt>& poly, pt p) { // requires poly to have poly[0] == poly.back()
    int n = poly.size(), winding = 0, q = quadrant(poly[0]-p);
    for(int i=1;i<n;++i) {
        int nq = quadrant(poly[i]-p);
        if(nq==-1) return -oo;
        if(nq==q) continue;
        if((nq^q)&1) { // only moved one quadrant
            if((q+1)%4==nq) winding++;
            else winding--;
        } else { // moved two quadrants, check in which direction quadrant was entered
            int tmp = sgn(ccw(poly[i],poly[i-1],p));
            if(tmp==0) return -oo; // -oo means "on the boundary"
            winding-=2*tmp;
        }
        q = nq;
    }
    assert(winding%4==0); // we should be back at the start quadrant +/- a full rotation of 4.
    return winding/4; //returns winding number (how many times the polygon is wrapped around the given point)
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(true) {
        int n; cin >> n;
        if(n==0) break;
        vector<pt> pts(n); for(auto& p: pts) read(p);
        pts.push_back(pts[0]);
        int m; cin >> m;
        while(m--) {
            pt p;read(p);
            int rotations = inpoly(pts,p);
            if(rotations==-oo) {
                cout << "on\n";
            } else {
                cout << (rotations?"in":"out") << '\n';
            }
        }
    }
}