#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
namespace geo3D{
#define TT template<typename T>
TT struct point {
    T x,y,z;
    template<typename R> operator point<R>()
    { return point<R>{x,y,z}; }
    auto operator+(const point& v) const {
        return point{x+v.x,y+v.y,z+v.z};
    }
    auto operator-(const point& v) const {
        return point{x-v.x,y-v.y,z-v.z};
    }
    auto operator*(T c) const { // scalar multiple
        return point{c*x,c*y,c*z};
    }
    auto operator*(const point& v) const { // cross product
        return point{y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x};
    }
    auto operator|(const point& v) const { // in product
        return x*v.x+y*v.y+z*v.z;
    }
    bool operator==(const point& o) const {
        return x==o.x and y==o.y and z == o.z;
    }
    bool operator!=(const point& o) const {
        return !(*this==o);
    }
    bool operator<(const point& o) const {
        if(x!=o.x) return x<o.x;
        if(y!=o.y) return y<o.y;
        return z<o.z;
    }
};
TT const point<T> zero = {0,0,0};
TT auto operator*(T c, const point<T>& p) {
    return point<T>{c*p.x,c*p.y,c*p.z};
}


TT auto norm(const point<T>& p) {return p|p;};
TT auto abs(const point<T>& p) {return sqrt(norm(p));}
TT auto sgn(T a) {return a==0?0:(a>0?1:-1);}
TT auto ccw(const point<T>& p1, const point<T>& p2, const point<T>& p3) {auto u = p2-p1, v = p3-p2; return u*v;}
TT void read(point<T>& p) {
    cin >> p.x >> p.y >> p.z;
}
TT ostream& operator<<(ostream& c, const point<T>& p) {
    return c << p.x << ' ' << p.y << ' ' << p.z;
}
TT istream& operator>>(istream& c, point<T>& p) {
    return c >> p.x >> p.y >> p.z;
}
}
using namespace geo3D;
namespace std {
    TT struct hash<point<T>> {
        std::size_t operator()(const point<T>& p) const noexcept
        {
            return p.x ^ (p.y *5) ^ (p.z*3); // or use boost::hash_combine
        }
    };
}
typedef point<ll> pt;
#undef TT

#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1, oo = 1e9;
unordered_map<pt,int> ptmap;

int get(pt p) {
    if(ptmap.count(p)) return ptmap[p];
    return ptmap[p] = ptmap.size();
}
struct el {
    int at, h;
    bool operator<(const el& o) const {
        return h>o.h;
    }
};
// template<typename T> double area(point<T>* tr) {
//     return 0.5*abs(point<double>(ccw(tr[0],tr[1],tr[2])));
// }
int main() {
    using namespace geo3D;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<pi, int> edgemap;
    int n; cin >> n;
    vector<vector<tuple<int,int,int>>> adj(n);
    vi h(n,-oo), hhi(n), hlo(n);
    vector<array<pt,3>> triangles(n);
    for(int i=0;i<n;++i) {
        pt a,b,c;
        cin >> a >> b >> c;
        hlo[i] = min({a.z,b.z,c.z});
        hhi[i] = max({a.z,b.z,c.z});
        if(i==0) h[0] = a.z;
        int id[3] = {get(a),get(b), get(c)};
        auto& tr = triangles[i] = {a,b,c};

        for(int j=0;j<3;++j) {
            auto d = id[j], e = id[(j+1)%3];
            if(edgemap.count({e,d})) {
                int to = edgemap[{e,d}];
                int h1 = tr[j].z,h2 = tr[(j+1)%3].z;
                if(h1>h2) swap(h1,h2);
                adj[i].emplace_back(to,h1,h2);
                adj[to].emplace_back(i,h1,h2);
            } else {
                edgemap[{d,e}] = i;
            }
        }

    }
    priority_queue<el> pq;
    pq.push({0,h[0]});
    while(!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if(h[c.at]>c.h) continue;
        for(auto [to,h1,h2] : adj[c.at]) {
            if(c.h < h1 )
                continue;
            int newh = min(c.h, h2);
            if(newh>h[to]) {
                h[to] = newh;
                pq.push({to,newh});
            }
        }
    }
    double ans = 0;
    for(int i=0;i<n;++i) {
        // calculate visited area of this triangle
        auto& tr = triangles[i];

        int ch = h[i];
        vector<point<double>> surface;
        for(int j=0;j<3;++j) {
            if(ch>=tr[j].z) surface.push_back(tr[j]);
            if(sgn(tr[j].z-ch)*sgn(tr[(j+1)%3].z-ch)==-1) {
                double mix = (double)(ch-tr[j].z)/(tr[(j+1)%3].z-tr[j].z);
                auto tmp = (1-mix)*point<double>(tr[j])+mix*point<double>(tr[(j+1)%3]);
                surface.push_back(tmp);
            }
        }
        // calculate area of surface
        point<double> sum = zero<double>;
        for(int j=0;j<surface.size();++j) {
            sum = sum+surface[j]*surface[(j+1)%surface.size()];
        }
        ans+=0.5*abs(sum);
    }
    cout << setprecision(10) << ans << '\n';
}