#include "bits/stdc++.h"
#include "point.h"
#include "geo3deb.h"
typedef point<double> pt;
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
    if(norm(u*v)<=0.00001) {
        cand = nw;
        G_POINT(pts[cand],"green");
        G_PAUSE();
        return;
    }
    if(norm(u*w)<=0.00001) {
        G_POINT(pts[nw],"orange");
        G_PAUSE();
        return;
    }
    pt normal = u*v;
    if((normal|pts[nw]) < (normal|pts[cand]) ) {
        cand = nw;
        G_POINT(pts[cand],"green");
        G_PAUSE();
    } else {
        G_POINT(pts[nw],"orange");
        G_PAUSE();
    }

}
edge can(edge e) {
    if(e[1]>e[0]) swap(e[0],e[1]);
    return e;
}
int main() {
    int t; cin >> t;
    while(t--) {
        G_INIT("convexhull.txt");
        using namespace geo3D;
        int n; cin >> n;
        pts.resize(n);
        for(auto& p : pts) {
            read(p);
            G_POINT(p);
        }
        sort(all(pts));
        vector<bool> hull(n);
        edge start = {1,0};
        int cand = 0;


        for(int i=0;i<n;++i) {
            check(cand,i,start);

        }
        set<edge> done, active;
        auto isdone = [&](const edge& e) {
            return done.count(e);
        };
        double area=0, volume=0;
        auto tri = [&](int a, int b, int c) {
            area+=abs((pts[b]-pts[a])*(pts[c]-pts[a]));
            volume+=pts[a]*pts[b]|pts[c];
        };
        tri(1,0,cand);
        done.insert({1,0});
        done.insert({cand,1});
        done.insert({0,cand});
        int id[3] = {0,1,cand};
        for(int i=0;i<3;++i) {
            G_POINT(pts[id[0]],"blue");
            edge e = {id[i],id[(i+1)%3]};
            G_SEGMENT(pts[e[0]], pts[e[1]]);
            active.insert(e);
        }
        G_PAUSE();
        while(!active.empty()) {
            auto e = *active.begin();
            active.erase(active.begin());
            if(isdone(e)) continue;
            done.insert(e);
            cand=0;
            G_SEGMENT(pts[e[0]], pts[e[1]], "blue");
            G_PAUSE();
            for(int i=0;i<n;++i) {
                check(cand,i,e);
            }
            done.insert({e[1],cand});
            done.insert({cand,e[0]});

            G_POINT(pts[cand], "blue");
            tri(e[0],e[1],cand);
            if(cand == e[0] or cand == e[1]) continue;
            edge e1 = {cand, e[1]}, e2 = {e[0],cand};
            G_POLYGON(vector<pt>{pts[e[0]], pts[e[1]],pts[cand]});
            G_SEGMENT(pts[e[0]], pts[cand]);
            G_SEGMENT(pts[cand], pts[e[1]]);
            if(!isdone(e1)) {
                active.insert(e1);
            }
            if(!isdone(e2)) {
                active.insert(e2);
            }
            G_PAUSE();
        }
        cout << area/2 << ' ' << volume/6 << '\n';
    }

}