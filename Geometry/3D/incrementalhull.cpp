#include "bits/stdc++.h"
#include "point.h"
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
struct conflict {
    vvi adj;
    conflict(int n) {
        adj.assign(n,vi());
        
    }
    bool inside(int i) {
        return adj[i].empty();
    }
};
int main() {
    using namespace geo3D;
    int n; cin >> n;
    vector<pt> pts(n);
    for(auto& p : pts) read(p);
    random_shuffle(all(pts));
    // construct simplex
    auto v = pts[1] - pts[0];
    // find noncollinear point
    bool good = false;
    for(int i=2;i<n;++i) {
        if(v*(pts[i]-pts[0])!=pt{0,0,0}) {
            swap(pts[2], pts[i]);
            good = true;
            break;
        }
    }
    assert(good);
    good=false;
    auto u = pts[2] - pts[0];
    pt normal = u*v;
    auto inproduct = normal|pts[0];
    for(int i=3;i<n;++i) {
        if((pts[i]|normal) != inproduct) {
            good=true;
            swap(pts[i], pts[3]);
            break;
        }
    }
    assert(good);
    conflict g(n, pts);

    for(auto& p: pts) {
        // check if point is inside
        if(g.inside(p)) {
            continue;
        }
    }

}