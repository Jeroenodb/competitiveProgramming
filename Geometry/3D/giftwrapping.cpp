#include "bits/stdc++.h"
#include "point.h"
#include "geo3deb.h"
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
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
typedef array<int,2> edge;
vector<pt> pts;
void check(int& cand, int nw, edge e) {
    pt u = pts[e[1]] - pts[e[0]];
    pt v = pts[cand]-pts[e[1]];
    pt w = pts[nw]-pts[e[1]];
    if(u*v==zero<ll>) {
        cand = nw;
        return;
    }
    if(u*w==zero<ll>) return;
    pt normal = u*v;
    if((normal|pts[nw]) < (normal|pts[cand]) ) {
        cand = nw;
    }
}
edge can(edge e) {
    if(e[1]>e[0]) swap(e[0],e[1]);
    return e;
}
int main() {
    G_INIT("convexhull.txt");
    using namespace geo3D;
    int n; cin >> n;
    pts.resize(n);
    for(auto& p : pts) {
        do {
            p.x = rnd(-1000,1000);
            p.y = rnd(-1000,1000);
            p.z = rnd(-1000,1000);
        } while (norm(p)>1000*1000);
            
        G_POINT(p);
    }
    sort(all(pts));
    vector<bool> hull(n);
    edge start = {1,0};
    int cand = 0;


    for(int i=0;i<n;++i) {
        check(cand,i,start);

    }
    G_POINT(pts[0],"blue");
    G_POINT(pts[1],"blue");
    G_POINT(pts[cand],"blue");
    G_SEGMENT(pts[0], pts[1]);
    G_SEGMENT(pts[0], pts[cand]);
    G_SEGMENT(pts[cand], pts[1]);
    set<edge> active;
    auto isactive = [&](const edge& e) {
        G_SEGMENT(pts[e[0]], pts[e[1]]);
        return active.count(e) or active.count({e[1],e[0]});
    };
    double area=0, volume=0;
    auto tri = [&](int a, int b, int c) {
        abs(point<(pts[b]-pts[a])*(pts[c]-pts[a]);
    };
    auto erase = [&](const edge& e) {
        active.erase(e);
        active.erase({e[1],e[0]});
    };
    active.insert({0,1});
    active.insert({1,cand});
    active.insert({cand,0});
    while(!active.empty()) {
        auto e = *active.begin();
        active.erase(active.begin());
        cand=0;
        for(int i=0;i<n;++i) {
            check(cand,i,e);
        }

        G_POINT(pts[cand], "blue");
        edge e1 = {cand, e[1]}, e2 = {e[0],cand};
        G_POLYGON(vector<pt>{pts[e[0]], pts[e[1]],pts[cand]});

        if(isactive(e1)) erase(e1);
        else {

            hull[e1[0]] = hull[e1[1]] = true;
            active.insert(e1);
        }
        if(isactive(e2)) erase(e2);
        else {
            hull[e2[0]] = hull[e2[1]] = true;
            active.insert(e2);
        }
        G_PAUSE();
    }

}