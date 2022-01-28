#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <algorithm>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
const int mxN = 1e5+1;
#include <complex>
typedef complex<int> pt;
#define X real()
#define Y imag()
auto cross(pt u, pt v) {return (ll)u.X*v.Y-(ll)u.Y*v.X;}
auto sgn(ll a) {return a==0?0:(a>0?1:-1);}
auto ccw(pt p1, pt p2, pt p3) {auto u = p2-p1, v = p3-p2;return cross(u,v);}
auto in(pt p1, pt p2) {return (ll)p1.X*p2.X+(ll)p1.Y*p2.Y;}
auto norm(pt p) {return (ll)p.X*p.X+(ll)p.Y*p.Y;}
void read(pt& p) {
    int a,b; cin >> a >> b;
    p = {a,b};
}
auto convexhull(vector<pt> pts) {
    sort(all(pts),[](pt& a, pt& b) {return a.X < b.X or (a.X==b.X and a.Y<b.Y);});
    vector<pt> hull = {pts[0]};
    int n = pts.size();
    for(int phase = 0;phase <2;++phase) {
        for(int i=1;i<n;++i) {
            auto& p = pts[i];
            while(hull.size()>=2 and ccw(hull[hull.size()-2], hull.back(),p) >= 0) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        if(phase==0) reverse(all(pts));
    }
    assert(hull.front() == hull.back());
    return hull;
}
int main() {
    
}