#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
typedef complex<int> pt;
#define X real()
#define Y imag()
auto cross(pt u, pt v) {return (ll)u.X*v.Y-(ll)u.Y*v.X;}
void read(pt& p) {
    int a,b; cin >> a >> b;
    p = {a,b};
}
int main() {
    int n; cin >> n;
    vector<pt> poly(n);
    for(auto& p: poly) read(p);
    pt prev = poly.back();
    ll area = 0;
    // check the orientation of the polygon
    for(auto p: poly) {
        area+=cross(p,prev);
        prev = p;
    }
    // flip if necessary
    if(area>0) reverse(all(poly));

    double ans = 0;
    for(int rep=0;rep<2;++rep) {
        prev = poly.back();
        for(pt p: poly) {
            pt cur = p;
            ll w = p.X-prev.X, sgn = -1;
            if(w==0) {
                // Sometimes subtract vertical edge of polygon
                ans-=max(p.Y-prev.Y,0);
            } else {
                if(w<0) {
                    // always have prev left of p.
                    sgn=1;
                    swap(p,prev);
                }
                w = abs(w);
                // Use formula for line segments in a trapezoid, formed by two points and the x axis
                ans+=sgn*(w*prev.Y + 0.5*(p.Y-prev.Y)*(w+1));
            }
            prev = cur;
        }
        // rotate polygon by 90 degrees
        for(pt& p: poly) p*=pt{0,1};
    }
    cout << ans << '\n';
}