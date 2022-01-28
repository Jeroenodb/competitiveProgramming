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
const int mxN = 1e5+1;
const double oo = DBL_MAX;
typedef complex<ll> pt;
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
// TODO test splay tree other functions
template<class T> struct splaytree {
    #define l c[b]
    #define r c[b^1]
    #define L c[0]
    #define R c[1]
    struct node {
        T val;
        node *c[2] = {}, *par =NULL;
    };
    node *root=NULL;
    friend ostream& operator<<(ostream& c,node* n) {
        if(n==NULL) 
            return c << "(empty)";
        c << '(';
        if(n->L) c << n->L << ',';
        c << n->val;
        if(n->R) c << ',' << n->R;
        return c << ')';
    }
    void rotate(node* n) {
        // Precondition: n is not the root
        // Rotates n to the place of its parent
        // Corrects the pointers
        assert(n->par);
        assert(n->par!=n);
        assert(n->par->L == n or n->par->R == n);
        node* par = n->par;
        if(par->par) {
            auto gp = par->par;
            if(gp->L==par) {
                gp->L=n;
            } else {
                gp->R=n;
            }
        }
        n->par = par->par;
        bool b= n!=par->L;
        // Fix right child of current node
        par->l = n->r;
        if(n->r) 
            n->r->par = par;
        // Put parent under current node
        n->r = par;
        par->par = n;
    }
    void splay(node* n) {
        if(!n or n==root) return;
        bool finished =false;
        while(!finished) {
            if(!n->par) break;
            if(!n->par->par) {
                finished = true;
                rotate(n);
            } else {
                auto p = n->par, gp = p->par;
                if(gp==root) finished = true;
                // Double rotations
                if((p->L==n) == (gp->L==p)) {
                    rotate(p);
                } else {
                    rotate(n);
                }
                rotate(n);
            }
        }
        root = n;
    }
    node* insert(T val) {
        if(!root) {
            root = new node{val};
            return root;
        }
        return NULL;
        auto p = root;
        while(true) {
            node* tmp;
            if(val < p->val) {
                tmp = p->L;
                if(!tmp) {
                    tmp = p->L = new node{val,NULL,NULL,p};
                    splay(tmp);
                    return tmp;
                }
            } else if(p->val == val) {
                splay(p);
                return NULL;
            } else {
                tmp = p->R;
                if(!tmp) {
                    tmp = p->R = new node{val,NULL,NULL,p};
                    splay(tmp);
                    return tmp;
                }
            }
            p = tmp;
        }
        return NULL;
    }
    node* succ(node* n, bool b) {
        // Successor or Predecessor
        // Breaks amortization?
        if(!n) return n;
        node* p=NULL;
        if(n->r) {
            p = n->r;
            while(p->l) {
                if(p==p->l) {
                    break;
                }
                p = p->l;
            }
        } else {
            p = n->par; 
            auto pp = n;
            while(p and p->r == pp) {
                pp=p;
                p = p->par;
            }
        }
        splay(p);
        return p;
    }
    node* insert(node* c, node* n, bool b) {
        assert(c!=n);
        if(c->r) {
            auto p = c->r;
            while(p->l) 
                p = p->l;
            p->l = n;
            n->par = p;
        } else {
            c->r = n;
            n->par=c;
        }
        // debug(root);
        splay(n);
        return n;
    }
    void erase(node* n) {
        if(!n) return;
        splay(n);
        if(n->L) {
            auto c = n->L;
            root = c;
            c->par = NULL;
            while(c->R) {
                c=c->R;
            }
            splay(c);
            assert(!c->R);
            c->R = n->R;
            if(c->R) {
                c->R->par = c;
            }
        } else {
            root = n->R;
            if(root->R) {
                root->R->par=NULL;
            }
        }
        delete n;
    }
    #undef l
    #undef r
    #undef L
    #undef R
};

namespace voronoi {
    const static int CIRCLE = 1<<30, MASK = ~CIRCLE;
    vector<pt> sites = {{0,0}};

    double sweepline;
    const static double eps=1e-6;
    struct parabola {
        // parabola of the form b*(x-a)^2+c
        int a;
        double b,c;
        bool vertical=false;
        parabola(complex<double> p) {
            a=p.X;
            if(2*p.Y<eps) {
                vertical = true;
                b= 1/eps;
            } else {
                b=1.0/(2*p.Y);
            }         
            c = p.Y/2;
        }
        void draw(double l, double r) {
            const int steps = 20;
            GD_POLYLINE("red",
                for(int i=0;i<=steps;++i) {
                    auto x = l+ (r-l)*i/steps;
                    auto y = call(x)+sweepline;
                    if(abs(y)<2000)
                        GD_POLYPOINT(x,y);
                }
            );

        }
        double call(double x) {
            return b*(x-a)*(x-a)+c;
        }
        double intersect(parabola& o) {
            if(vertical) return a;
            if(o.vertical) return o.a;
            int d = a-o.a;
            double aa = b-o.b, bb = -2*d*b, cc = b*d*d+c-o.c;
            if(aa==0) {
                // assert(bb!=0);
                if(bb==0) return (cc<0?oo:-oo);
                return o.a-cc/bb;
            }
            // double peak = -bb/(2*aa);
            // double value = aa*peak*peak + bb*peak + cc;
            // value>0?1:-1
            auto ans = (-bb+sqrt(bb*bb-4*aa*cc))/(2*aa);
            ans+=o.a;
            return ans;
        }

    };
    
    double breakpoint(pt l, pt r) {
        complex<double> ll = {l.X, l.Y-sweepline}, rr = {r.X, r.Y-sweepline};
        parabola lp(ll), rp(rr);
        auto ans = lp.intersect(rp);
        // GD_LAYER();
        // lp.draw(ans-5,ans);
        // rp.draw(ans,ans+5);
        // GD_PAUSE();
        return ans;
    }
    
    struct arc {
        // parabola in the beachline
        // Has pointers to the site it belongs to, and its neighbor arcs.
        int at=0,prev=0,next=0,circle=0;
        pair<double,double> segment() {

            double left = -oo, right = oo;

            if(prev) {
                left = breakpoint(sites[prev], sites[at]);
            } 
            if(next) {
                right = breakpoint(sites[at], sites[next]);
            }
            return {left,right};
        }
        bool operator<(const arc& o) const {
            // Never use this
            return false;
        }
        bool operator==(const arc& o) const {
            return false;
        }
        
    };
    ostream& operator<<(ostream& c, const arc& a) {
        return c << '[' << a.prev << ' ' << a.at << ' ' << a.next << ']';
    }
    typedef splaytree<arc>::node node;

    int n;

    struct circle {
        complex<double> m;
        double r;
        node* arc=NULL;
        bool valid=true;
        circle() {
            r=0, m = 0;
        }
        circle(pt a, pt b, pt c, node* _arc) {
            arc= _arc;
            pt u = b-a, v = c-a;
            auto ans = pt{v.Y*norm(u)-u.Y*norm(v), -v.X*norm(u)+u.X*norm(v)};
            auto D = 2*cross(u,v);
            if(D==0) {
                m = {0,-oo};
                r = 0;
                valid = false;
            } else {
                m = complex<double>{ans.X, ans.Y}/(double)D;
                r = abs(m);
                m+=complex<double>{a.X,a.Y};
            }
        }
    };
    vector<circle> circles = {};
    struct event {
        int i;
        pair<double,double> getPos() const {
            if(i&CIRCLE) {
                auto& c = circles[i&MASK];
                auto pos = c.m  - complex<double>{0.0,c.r};
                return {pos.Y,pos.X};
            } else {
                return {sites[i].Y, sites[i].X};
            }
        }
        bool operator<(const event& o) const {
            return getPos() < o.getPos();
        }
    };

    splaytree<arc> beachline;
    void drawnode(node* at) {
        if(at==NULL) return;
        auto [left,right] = at->val.segment();
        pt pp = sites[at->val.at];
        left = max(-1000.0,left);
        right = min(2000.0,right);
        parabola({pp.X, pp.Y-sweepline}).draw(left,right);
        if(at->c[0]) {
            drawnode(at->c[0]);
        }
        if(at->c[1]) {
            drawnode(at->c[1]);
        }
    }

    splaytree<arc>::node* getArc(ll x) {
        node* iter = beachline.root;
        // Precision errors, maybe use past calculations
        while(iter) {
            auto& a = iter->val;
            auto [left,right] = a.segment();
            if(left<=x and x < right) {
                return iter;
            } else if(left>x) {
                iter = iter->c[0];
            } else {
                iter = iter->c[1];
            }
        }
        return iter;
    }
    priority_queue<event> pq;
    struct Diagram {
        vector<complex<double>> points;
        vvi adj;
        map<pair<int,int>, int> m;
        void addPoint(complex<double> p) {
            points.push_back(p);
            adj.push_back({});
        }
        void addHalfedge(int a, int b) {
            if(a>b) swap(a,b);
            m[{a,b}] = points.size()-1;
        }
        void closeHalfedge(int a, int b) {
            if(a>b) swap(a,b);
            if(m.count({a,b})) {
                adj[m[{a,b}]].push_back(points.size()-1);
            }
        }
        void draw() {
            for(auto p: points) {
                // cout << p.X << ' ' << p.Y << '\n';
                GD_POINT(p.X,p.Y, "red");
            }
            for(int i=0;i<(int)adj.size();++i) {
                auto p1 = points[i];
                for(int j: adj[i]) {
                    auto p2 = points[j];
                    GD_SEGMENT(p1.X,p1.Y,p2.X,p2.Y);
                }
            }
        }
    } diagram;

    void makeCircle(node* left, node* mid, node* right) {
        if(!left or !mid or !right) 
            return;
        auto &l = left->val, &m = mid->val,  &r = right->val;
        if(l.at == r.at or m.at == r.at or l.at == m.at) 
            return;
        if(m.circle) return;
        auto &ls = sites[l.at], &ms = sites[m.at], &rs = sites[r.at];
        if(ccw(ls,ms,rs)>0) {
            return;
        }
        m.circle = circles.size();
        circles.push_back(circle(sites[l.at],sites[m.at], sites[r.at],mid));
        if(circles.back().r < 1000)
            GD_CIRCLE(circles.back().m.X, circles.back().m.Y, circles.back().r);
        pq.push({(int)(circles.size()-1)|CIRCLE});
    }
    void handleSite(int i) {
        auto right = getArc(sites[i].X);
        GD_POINT(sites[i].X, sites[i].Y,"bold red");
        if(!right) {
            beachline.insert({i});
            return;
        }
        if(right->val.circle) {
            circles[right->val.circle].valid = false;
            right->val.circle = 0;
        }
        auto left = beachline.insert(right,new node{right->val}, 1);
        auto mid  = beachline.insert(right,new node({{i,left->val.at,left->val.at}}),1);
        // Update next and prev pointers
        left->val.next = right->val.prev = i;
        makeCircle(beachline.succ(left,1), left,mid);
        makeCircle(mid,right, beachline.succ(right,0));
    }
    void handleCircle(int i) {
        auto& c = circles[i];
        auto a = c.arc;
        auto left  = beachline.succ(a,1), right = beachline.succ(a,0);
        // update next and prev pointers of arcs
        diagram.addPoint(c.m);
        // Add point to the voronoi diagram structure
        diagram.closeHalfedge(left->val.at, a->val.at );
        diagram.closeHalfedge(a->val.at, right->val.at);
        diagram.addHalfedge(left->val.at, a->val.at);
        diagram.addHalfedge(right->val.at, a->val.at);
        diagram.addHalfedge(left->val.at, right->val.at);
        beachline.erase(a);
        if(left) {
            left->val.next = right?right->val.at: 0;
        }
        if(right) {
            right->val.prev = left?left->val.at:0;
        }
        
        // GD_CIRCLE(c.m.X,c.m.Y,c.r);

        // makeCircles
        if(left->val.circle) {
            circles[left->val.circle].valid = false;
            left->val.circle = 0;
        }
        if(right->val.circle) {
            circles[right->val.circle].valid = false;
            right->val.circle = 0;
        }
        makeCircle(beachline.succ(left,1),left,right);
        makeCircle(left,right,beachline.succ(right,0));
    }
    void solve() {

        n = sites.size();
        for(int i=1;i<n;++i) {
            pq.push({i});
        }
        while(!pq.empty()) {
            GD_LAYER();
            event e = pq.top();pq.pop();
            sweepline = e.getPos().first;
            GD_LINE(0,sweepline,1,sweepline,"green");
            drawnode(beachline.root);
            diagram.draw();
            GD_PAUSE();
            if(e.i&CIRCLE) {
                if(circles[e.i&MASK].valid)
                    handleCircle(e.i&MASK);
            } else {
                handleSite(e.i);
            }
        }
    }
};
int main() {
    GD_INIT("voronoi.html");
    GD_LOG_TO_STDERR(false);
    int n; cin >> n;
    using namespace voronoi;
    for(int i=0;i<n;++i) {
        int x,y; cin >> x >> y;
        sites.push_back({x,y});
        GD_POINT(x,y);
    }
    solve();
    diagram.draw();
}