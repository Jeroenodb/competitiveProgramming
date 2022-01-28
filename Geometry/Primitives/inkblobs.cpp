#include "bits/stdc++.h"
// #undef LOCAL
#ifdef LOCAL
#include "geodeb.h"
#endif
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef double ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1, oo = 1e9;
typedef complex<double> pt;
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
bool lexo(pt a, pt b) {
    return a.X<b.X or (a.X==b.X and a.Y > b.Y);
}
pt o;
bool polarcomp(const pt& a, const pt& b) {
    bool lex1 = lexo(o,a), lex2 = lexo(o,b);
    if(lex1!=lex2) return lex1<lex2;
    return ccw(o,a,b)>0;
}
struct circle {
    pt p; double r;
    bool inside(pt o) {
        return norm(p-o)<=r*r;
    }
};
const double EPS= 1e-3;
vector<pt> circleintersection(circle a, circle b) {
    bool flip=false;
    if(a.r<b.r) swap(a,b),flip=true;
    auto v = b.p-a.p;
    auto d = abs(v);
    if(d>a.r+b.r-EPS or d+b.r<a.r+EPS) return {};
    auto tmp = (a.r*a.r+norm(v)-b.r*b.r)/(2*a.r*d);
    auto theta = acos(tmp);
    vector<pt> ans = {a.p+polar(a.r/d,theta)*v,a.p+polar(a.r/d,-theta)*v};
    if(flip) swap(ans[0],ans[1]);
    return ans;
}
struct IS {
    int to;
    pt p;
    bool left,vis=false;
};
vector<vector<IS>> g;
vector<pt> cycle;
void dfs(int at, IS& is) {
    if(is.vis) return;
    #ifdef LOCAL
    GD_POINT(is.p.X,is.p.Y,"orange");
    #endif
    is.vis=true;
    cycle.push_back(is.p);
    auto& v = g[is.to];
    for(auto it = v.begin();it!=v.end();++it) {
        if(it->p==is.p) {
            it->vis=true;
            if(next(it)==v.end()) {
                it = v.begin();
            } else it++;
            dfs(is.to,*it);
            break;
        }
    }
}
double area(const vector<pt>& ps) {
    double res=0;
    pt prev = ps.back();
    for(auto& p: ps) {
        res+=(p.X-prev.X)*(p.Y+prev.Y);
        prev = p;
    }
    return res/2;
}
bool solve() {
    #ifdef LOCAL
    GD_LAYER();
    #endif
    int n; cin >> n;
    if(n==0) return false;
    vector<circle> cs(n);
    for(auto& c : cs) {
        read(c.p);
        cin >> c.r;
        #ifdef LOCAL
        GD_CIRCLE(c.p.X,c.p.Y,c.r);
        #endif
    }
    g.assign(n,{});
    for(int i=0;i<n;++i) {
        for(int j=i+1;j<n;++j) {
            auto iss = circleintersection(cs[i],cs[j]);
            auto add = [&](int a, int b,pt p) {
                for(int k=0;k<n;++k) {
                    if(k!=a and k!=b and cs[k].inside(p)) {
                        #ifdef LOCAL
                        GD_POINT(p.X,p.Y,"red");
                        #endif
                        return;
                    }
                }
                #ifdef LOCAL
                GD_POINT(p.X,p.Y,"green");
                #endif
                IS is;
                is.left=true,is.p=p,is.to=b;
                g[a].push_back(is);
                is.left=false,is.to=a;
                g[b].push_back(is);
            };
            if(!iss.empty()) {
                add(i,j,iss[0]);
                add(j,i,iss[1]);
            }
        }
    }
    for(int i=0;i<n;++i) {
        auto& v = g[i];
        o=cs[i].p;
        sort(all(v), [&](const IS& a, const IS& b) {return polarcomp(a.p,b.p);});
    }
    // find comps

    int ans=1;
    /*
    vector<bool> vis(n);
    for(int i=0;i<n;++i) {
        if(!vis[i]) {
            ans--;
            int sz=0;
            queue<int> q; q.push(i);
            vis[i]=true;
            while(!q.empty()) {
                sz++;
                int at = q.front(); q.pop();
                for(int to=0;to<n;++to) {
                    if(!vis[to] and abs(cs[at].p-cs[to].p)<=cs[at].r+cs[to].r) {
                        vis[to]=true;
                        q.push(to);
                    }
                }
            }
            if(sz==1) ans++;
        }
    }
    */
    // walk along cycles
    for(int i=0;i<n;++i) {
        for(auto& j: g[i]) {
            if(!j.vis and !j.left) {
                cycle.clear();
                #ifdef LOCAL
                GD_LAYER();
                #endif
                dfs(i,j);
                if(area(cycle)>0) {
                    #ifdef LOCAL
                    GD_PAUSE() << "GOOD";
                    #endif
                    ans++;
                }
            }
        }
    }
    cout << ans << '\n';
    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    GD_INIT("inkblobs.html");
    GD_LOG_TO_STDERR(false);
    #endif
    while(solve()) {}
}