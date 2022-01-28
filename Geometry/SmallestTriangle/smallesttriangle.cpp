#include "bits/stdc++.h"
// #include "geodeb.h"
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1;
const ll oo = 1e18;
typedef complex<int> pt;
typedef vector<pt> vp;
#define X real()
#define Y imag()
auto cross(pt u, pt v) {return (ll)u.X*v.Y-(ll)u.Y*v.X;}
auto sgn(ll a) {return a==0?0:(a>0?1:-1);}
auto ccw(pt p1, pt p2, pt p3) {auto u = p2-p1, v = p3-p2;return cross(u,v);}
auto in(pt p1, pt p2) {return (ll)p1.X*p2.X+(ll)p1.Y*p2.Y;}
auto norm(pt p) {return (ll)p.X*p.X+(ll)p.Y*p.Y;}
bool comp(const pt& a, const pt& b) { return a.X<b.X or (a.X==b.X and a.Y < b.Y);}
auto mag(pt p) {return sqrt(norm(p));}
bool compy(const pt& a, const pt& b) { return a.Y < b.Y;}
void read(pt& p) {
    int a,b; cin >> a >> b;
    p = {a,b};
}
pt pts[mxN];
pt sortedy[mxN];
double best = oo;
array<pt,3> ans;
void consider(const pt& a,const pt& b,const pt& c) {

    auto perimeter = mag(b-a)+mag(c-b)+mag(a-c);
    // GD_LAYER();
    // GD_POINT(a.X,a.Y,"orange");
    // GD_POINT(b.X,b.Y,"orange");
    // GD_POINT(c.X,c.Y,"orange");
    if(perimeter<best) {
        best = perimeter;
        ans = {a,b,c};
        // GD_LAYER();
        // for(auto& p : ans)
        //     GD_POINT(p.X,p.Y,"red");
    }
}
void calc(const vp& base, const vp& top) {
    if(best<0.5) return;
    int n = base.size(), m = top.size();
    for(int i=0,j=0;i<n-1;++i) {
        // consider i as lowest point of the base
        auto& p = base[i];
        auto lo = p.Y-0.5*best, hi = p.Y+0.5*best;
        while(j<m-1 and top[j].Y<lo) ++j; // O(n)

        if(top[j].Y<lo or top[j].Y>hi) continue;
        for(int r=i+1;r<n;++r) {
            // consider r as highest point of base
            auto& q = base[r];
            if((ll)q.Y-p.Y>0.5*best) break;
            for(int k=j;k<m and k>=0;--k) {
                if(top[k].Y<lo) break;
                consider(p,q,top[k]);
            }
            for(int k=j+1;k<m;++k) {
                if(top[k].Y>hi) break;
                consider(p,q,top[k]);
            }
        }
    }
}
void smallesttriangle(const int l,const int r) {
    // halfopen interval
    if(l+1==r) {
        sortedy[l] = pts[l];
        return;
    }
    int mid = (l+r)/2;
    int split = pts[mid].X;
    smallesttriangle(l,mid);
    smallesttriangle(mid,r);
    vp left,right;
    left.reserve(mid-l), right.reserve(r-mid);

    for(int i=l;i<mid;++i) {
        if(i!=l) assert(sortedy[i-1].Y<=sortedy[i].Y);
        if(sortedy[i].X+best*0.5>split) 
            left.push_back(sortedy[i]);
    }
    for(int i=mid;i<r;++i) {
        if(i!=mid) assert(sortedy[i-1].Y<=sortedy[i].Y);
        if(sortedy[i].X-best*0.5<split) 
            right.push_back(sortedy[i]);
    }
    // GD_LAYER();
    // for(int i=l;i<r;++i) {
    //     auto& p = sortedy[i];
    //     GD_POINT(p.X,p.Y);
    // }
    // GD_LINE(split,0,split,1);
    // if(best!=oo) {GD_LINE(split-best*0.5,0,split-best*0.5,1, "red");
    //     GD_LINE(split+best*0.5,0,split+best*0.5,1, "red");
    // }
    // for(auto& p : left) GD_POINT(p.X,p.Y,"green");
    // for(auto& p : right) GD_POINT(p.X,p.Y,"blue");
    calc(left,right);
    calc(right,left);
    merge(sortedy+l, sortedy+mid,sortedy+mid,sortedy+r,pts+l,compy);
    copy(pts+l, pts+r, sortedy+l);
}
double brute(int n) {
    for(int i=0;i<n;++i) {
        for(int j=i+1;j<n;++j) {
            for(int k=j+1;k<n;++k) {
                consider(pts[i],pts[j],pts[k]);
            }
        }
    }
    auto res = best;
    best = oo;
    return res;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // GD_INIT("tri.html");
    // GD_LOG_TO_STDERR(false);
    // freopen("tri.in","r",stdin);
    int n; cin >> n;
    for(int i=0;i<n;++i) {
        read(pts[i]);
    }
    vp original(pts,pts+n);
    // debug(brute(n));
        
    sort(pts,pts+n,comp);
    smallesttriangle(0,n);
    // for(auto& p: ans) GD_POINT(p.X,p.Y,"red bold");
    // GD_PAUSE();
    cout << setprecision(10) << fixed << best << '\n';
    assert(best<oo-1);
    int ids[3]={-1,-1,-1};
    for(int i=0;i<3;++i) {
        ids[i] = find(all(original), ans[i])-original.begin();
        int mx = -1;
        for(int j=0;j<i;++j) if(ans[i] == ans[j]) {
            mx = max(mx,ids[j]);
        }
        ids[i] = find(original.begin()+(mx+1),original.end(), ans[i])-original.begin();
        if(i) cout << ' ';
        assert(0<=ids[i]  and ids[i]<n);
        cout << ids[i]+1;
    } cout << '\n';
}