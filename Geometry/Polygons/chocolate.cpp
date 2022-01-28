#include "bits/stdc++.h"
#include "geodeb.h"
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
vector<pt> pts;
double area(const vector<pt>& ps) {
    double res=0;
    pt prev = ps.back();
    for(auto& p: ps) {
        res+=(p.X-prev.X)*(p.Y+prev.Y);
        prev = p;
    }
    return res/2;
}
double totalarea;
double calc(double theta) {
    GD_LAYER();
    // intersect line with polygon
    vector<pt> ps(pts);
    int n = ps.size(), to = -1;
    double lo = oo,hi=-oo;
    for(int i=0;i<n;++i) {
        auto& p = ps[i];
        p *=polar(1.0,theta);
        GD_POINT(p.X,p.Y);
        if(p.X<lo) to = i+1;
        lo = min(p.X,lo);
        hi = max(p.X,hi);
    }
    if(to==n) to = 0;
    rotate(ps.begin(),ps.begin()+to,ps.end());
    double length=oo;
    while(hi-lo>1e-3) {
        double mid = 0.5*(lo+hi);
        GD_LAYER();
        GD_LINE(mid,0,mid,1);
        auto prev = ps.back();
        int first=-1;
        vector<pt> half;
        for(int i=0;i<n;++i) {
            auto& p = ps[i];
            double a=p.X,b=prev.X;
            if(a>b) swap(a,b);
            if(a<=mid and b>=mid) {
                // found split
                double mix = (mid-prev.X)/(p.X-prev.X);
                if(first==-1) {
                    first = i;
                    half.push_back(mix*p + (1-mix)*prev);
                } else {
                    half.insert(half.end(), ps.begin()+first,ps.begin()+i);
                    half.push_back(mix*p + (1-mix)*prev);
                    break;
                }
            }
            prev = p;
        }
        GD_POLYGON("black:salmon",
            for(auto& p : half) {
                GD_POLYPOINT(p.X,p.Y);
            }
        );
        if(half.empty()) return 0;
        double halfarea = abs(area(half));
        length = abs(half[0].Y-half.back().Y);
        if(halfarea*2>totalarea) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return length;
}

double solve(double lo, double hi) {
    while(hi-lo>=1e6) {
        double m1 = (lo*2+hi)/3,m2 = (lo+2*hi)/3;
        if(calc(m1)<calc(m2)) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    return calc(lo);
}
int main() {
    GD_INIT("chocolate.html");
    GD_LOG_TO_STDERR(false);
    int n; cin >> n;
    pts.resize(n);
    for(auto& p : pts) read(p);
    if(area(pts)<0) {
        reverse(all(pts));
    }
    totalarea = area(pts);
    // binsearch on angle
    double ans = oo;
    for(int i=0;i<50;++i) {
        double start = i*PI/50;
        ans = min(ans,solve(start,start+PI*0.66));
    }
    cout << fixed << setprecision(4) << ans << '\n';

}