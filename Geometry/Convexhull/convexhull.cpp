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

auto convexhull(vector<pt>& pts) {
    sort(all(pts),comp);
    vector<pt> hull = {pts[0]}; 
    int n = pts.size();
    for(int phase = 0;phase <2;++phase) {
        int last = hull.size();
        for(int i=1;i<n;++i) {
            auto& p = pts[i];
            while(hull.size()>=2 and (int)hull.size()!=last and ccw(hull[hull.size()-2], hull.back(),p) >= 0) { // change >= to > for multiple collinear points
                hull.pop_back();
            }
            hull.push_back(p);
        }
        if(phase==0) {
            reverse(all(pts));
        }
    }
    assert(hull.front() == hull.back());
    if(hull.size()!=1) hull.pop_back(); // want to keep first point twice?
    return hull;
}
int next(int i, int n) {return i==n-1?0:i+1;}
int prev(int i, int n) {return i==0?n-1:i-1;}
template <class Function>
int extremeVertex(const vector<pt>& poly, Function direction) {
    // returns index of extreme vertex
    // extreme means, that no point is strictly to the right when ordered by direction angle
    int n = poly.size(), left = 0, leftSgn;

    auto vertexCmp = [&poly, direction](int i, int j) {
        return sgn(cross(direction(poly[j]), poly[j] - poly[i])); };

    auto isExtreme = [n, vertexCmp](int i, int& iSgn) {
        return (iSgn = vertexCmp(next(i, n), i)) >= 0 && vertexCmp(i, prev(i, n)) < 0; };

    for (int right = isExtreme(0, leftSgn) ? 1 : n; left + 1 < right;) {
        int middle = (left + right) / 2, middleSgn;
        if (isExtreme(middle, middleSgn)) return middle;
        if (leftSgn != middleSgn ? leftSgn < middleSgn
            : leftSgn == vertexCmp(left, middle)) right = middle;
        else left = middle, leftSgn = middleSgn;
    }
    return left;
}

int inside(const vector<pt>& hull, pt p) {
    // 1 if fully inside, 0 if on the boundary, -1 if outside
    pt b = hull[0];
    if(ccw(b,hull.back(),p)>0 or ccw(b,hull[1],p)<0) 
        return -1;
    int l=1,r=hull.size()-2;
    while(l<r) {
        int mid = (l+r+1)/2;
        if(ccw(b,hull[mid],p)<0) r=mid-1;
        else l = mid;
    }
    if(hull.size()==2) {
        auto v = hull[1]-b;
        ll inp = in(v,p-b);
        return 0<=inp and inp<=norm(v)?0:-1;
    } else return sgn(ccw(hull[l],hull[(l+1)%hull.size()],p));
}
typedef vector<pt> vp;
struct dynhull {
    vector<vp> hulls;
    void add(pt p) {
        vp myhull = {p};
        int i;
        for(i=0;i<(int)hulls.size();++i) {
            if(hulls[i].empty()) break;
            myhull.insert(myhull.end(),all(hulls[i]));
            hulls[i].clear();
        }
        if(i==hulls.size()) hulls.push_back(convexhull(myhull));
        else hulls[i] = convexhull(myhull);
    }
    ll extreme(pt ab) {
        pt perp = ab*pt{0,-1};
        auto direction = [&perp](const pt& p) {return perp;};
        ll res=-1;
        bool found=false;
        for(auto& h: hulls) {
            if(h.empty()) continue;
            if(!found) {
                found=true;
                res = in(ab,h[extremeVertex(h,direction)]);
            } else {
                res = max(res,in(ab,h[extremeVertex(h,direction)]));
            }
        }
        return res;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef LOCAL
    freopen("fencing.in","r",stdin);
    freopen("fencing.out","w",stdout);
    #endif

    int n,q; cin >> n >> q;

    dynhull dh;
    {
    int ptwo=1;
    while(ptwo<n) {
        ptwo*=2;
        dh.hulls.push_back({});
    }
    vp initial(n); for(auto& p: initial) read(p);
    dh.hulls.push_back(convexhull(initial));
    }
    while(q--) {
        int t; cin >> t;
        if(t==1) {
            pt p; read(p);
            dh.add(p);
        } else {
            pt ab; read(ab);
            ll c; cin >> c;
            ll hi = dh.extreme(ab), lo = -dh.extreme(-ab);
            if(lo<=c and c<=hi) {
                cout << "NO\n";
            } else cout << "YES\n";
        }
    }
}