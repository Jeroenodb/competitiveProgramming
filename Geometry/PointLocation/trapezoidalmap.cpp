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
typedef complex<int> pt;
#define X real()
#define Y imag()
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
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
struct node;
vector<pt> pts;
struct edge {
    int a,b,poly;
    pair<double,double> line() {
        pt d = pts[b]-pts[a];
        if(!d.X) return {-oo,-oo};
        auto m = (double)d.Y/d.X;
        auto c = pts[a].Y-m*pts[a].X;
        return {m,c};
    }
    int ptcomp(pt p) {
        return sgn(ccw(pts[a],pts[b],p));
    }
    bool above(pt p, pt q) {
        if(pts[a]==p) return ccw(pts[a],pts[b],q)>0;
        if(comp(pts[a],p)) {
            return ccw(pts[a],pts[b],p)>0;
        } else return ccw(p,q,pts[a])<0;
    }
};
vector<edge> es;
struct trap {
    int a=-1,b=-1; // points corresponding to left and right boundaries
    int top=-1,bottom=-1; // edges corresponding to bottom and top
    node* leaf=NULL; // leaf of dag
    array<trap*,2> l = {}, r = {};
    int getpolygon() {
        auto p1 = es[top].poly;
        if(p1<0) return -1;
        if((abs(es[top].a-es[top].b)==1)==(es[top].a<es[top].b+1)) return -1;
        return p1;
    }
    void draw(int type = 0) {
        auto [m,c] = es[top].line();
        if(m==-oo) return;
        auto [m2,c2] = es[bottom].line();
        if(m2==-oo) return;
        const string colors[] = {"blue:#00ff0080","blue:#ff000080","bold red:#0000ff80"}; 
        GD_POLYGON(colors[type],
            GD_POLYPOINT(pts[a].X,pts[a].X*m+c);
            GD_POLYPOINT(pts[b].X,pts[b].X*m+c);
            GD_POLYPOINT(pts[b].X,pts[b].X*m2+c2);
            GD_POLYPOINT(pts[a].X,pts[a].X*m2+c2);
        );
        if(type==0) {
            if(l[0]) l[0]->draw(1);
            if(l[1]) l[1]->draw(2);
            if(r[0]) r[0]->draw(1);
            if(r[1]) r[1]->draw(2);
        }
    }
    bool segmentinside(pt p, pt q) {
        if(!comp(p,pts[b]) or !comp(pts[a],q)) return false;
        return !es[top].above(p,q) and es[bottom].above(p,q);
    }
    int sgna() {
        if(es[top].a==a) return 1;
        if(es[bottom].a==a) return -1;
        return 0; 
    }
    int sgnb() {
        if(es[top].b==b) return 1;
        if(es[bottom].b==b) return -1;
        return 0; 
    }
    void fixLeft(trap* tr, int sgn) {
        auto mysgn = sgna();
        if(mysgn!=0 or !sgn) {
            l={tr,NULL};
            return;
        }
        if(sgn>0) l[1]=tr;
        else l[0]=tr;
    }
    void fixRight() {
        // precondition: r pointers are good
        // postcondition: l pointer of right neighbour towards me is set
        if(r[0]) r[0]->fixLeft(this,sgnb());
        if(r[1]) r[1]->fixLeft(this,sgnb());
    }
    vector<node*> walk(int c, int d) { // returns a list of all trapeziums intersecting this segment
        GD_PAUSE();
        GD_LAYER();
        vector<node*> ans;
        trap *at = this;
        bool good=true;
        while(good) {
            good=false;
            ans.push_back(at->leaf);
            at->draw(1);
            for(auto to : at->r) {
                if(to and to->segmentinside(pts[c],pts[d])) {
                    at = to;
                    good=true;
                    break;
                }
            }
        }
        return ans;
    }
};

struct node {
    int split=-1; // indices of two pts or index of one point (x/y) node
    bool xnode=false;
    union {
        trap *trp;
        node *l=NULL;
    };
    node *r=NULL;
    node() {}
    node(trap* tr) : trp(tr) {tr->leaf=this;}
    node* search(pt p, pt q={0,0}, bool seg=false) {
        auto at = this;
        while(at->split!=-1) {
            if(at->xnode) {
                // x split node
                at=comp(p,pts[at->split])?at->l:at->r;
            } else {
                // segment split node
                auto myccw = es[at->split].ptcomp(p);
                if(!myccw and seg) {
                    at = es[at->split].above(p,q)?at->l:at->r;
                } else at=myccw>0?at->l:at->r;
            }
        }
        return at;
    }
    void insert(int e) {
        int a= es[e].a, b= es[e].b;
        auto p = pts[a],q = pts[b];
        auto start = search(p,q,true);
        auto deleted =start->trp->walk(a,b);
        bool easyL=false,easyR=false;
        vector<trap*> newtraps;
        if(start->trp->a!=a) {
            easyL=true;
            // add x node for L
            auto cur=start;
            cur->split=a, cur->xnode=true;
            cur->r = new node(new trap(*cur->trp));
            cur->l = new node(cur->trp); // reuse old trapezium
            auto t1 = cur->l->trp; 
            auto t2 = cur->r->trp;
            t1->b=t2->a=a;
            t1->r[0] = t2, t2->l[0]=t1;
            t1->r[1] = t2->l[1] = NULL;
            newtraps.push_back(t1);
            deleted[0] = cur->r;
        }
        if(deleted.back()->trp->b!=b) {
            easyR=true;
            // Add x node for R
            auto cur = deleted.back();
            cur->split=b, cur->xnode=true;
            cur->r = new node(new trap(*cur->trp));
            cur->l = new node(cur->trp);  // reuse old trapezium
            auto t1 = cur->l->trp, t2 = cur->r->trp;
            t1->b=t2->a=b;
            t1->r[0] = t2, t2->l[0]=t1;
            t1->r[1] = t2->l[1] = NULL;
            newtraps.push_back(t2);
            deleted.back() = cur->l;
        }
        trap* trs[2] = {deleted[0]->trp,new trap(*deleted[0]->trp)};
        newtraps.push_back(trs[1]);
        new node(trs[0]), new node(trs[1]);
        // do first trapezium connections manually
        if(easyL)  trs[1]->l[0]->r[1]=trs[1]; 
        else if(trs[0]->l[0]) {
            auto asgn = trs[0]->sgna();
            if(asgn==1) {
                auto o =trs[0]->l[0];
                auto bsgn = o->sgnb();
                if(bsgn==0) o->r[1]=trs[1];
                else o->r[0]=trs[1];
                trs[0]->l={};
            } else if(asgn==-1) {
                auto o =trs[1]->l[0];
                auto bsgn = o->sgnb();
                if(bsgn==0) {
                    o->r[1]=trs[1];
                    swap(o->r[0],o->r[1]);
                } else o->r[0]=trs[1];
                trs[1]->l={};
            } else {
                swap(trs[1]->l[0],trs[1]->l[1]);
                trs[0]->l[1] = trs[1]->l[1] = NULL;
                trs[0]->l[0]->r[0]=trs[0];
                trs[1]->l[0]->r[0]=trs[1];
            }
        }
        trap* tr=NULL;
        for(auto i : deleted) {
            // add y-nodes and make new trapeziums (In total, 1 new trap)
            tr = i->trp;
            // check on which side line continues
            newtraps.push_back(tr);
            if(es[e].ptcomp(pts[tr->a])>0) {
                trs[0]->b=tr->a;
                new node(trs[0]=tr);
            } else if(trs[0]!=tr){
                trs[1]->b=tr->a;
                new node(trs[1]=tr);
            }

            auto rr = tr->r;
            // do right pointers
            trs[0]->r=trs[1]->r=rr;
            if(es[e].ptcomp(pts[tr->b])>0) trs[1]->r = {rr[1]?rr[1]:rr[0],NULL};
            else if(es[e].ptcomp(pts[tr->b])<0) trs[0]->r = {rr[0],NULL};
            else if(!easyR and !tr->r[0]) {
                auto bsgn = tr->sgna();
                if(bsgn==1) {
                    auto o =tr->r[0];
                    auto asgn = o->sgna();
                    if(asgn==0) o->l[1]=trs[1];
                    else o->l[0]=trs[1];
                    trs[0]->r={};
                } else if(bsgn==-1) {
                    auto o =tr->r[0];
                    auto asgn = o->sgnb();
                    if(asgn==0) {
                        o->l[1]=trs[1];
                        swap(o->l[0],o->l[1]);
                    } else o->l[0]=trs[1];
                    trs[1]->r={};
                } else {
                    swap(trs[1]->r[0],trs[1]->r[1]);
                    trs[0]->r[1] = trs[1]->r[1] = NULL;
                }
            }
            trs[0]->bottom=e, trs[1]->top=e;
            // make new y-node
            i->split=e,i->l=trs[0]->leaf,i->r=trs[1]->leaf;
        }
        // Do last connections manually
        trs[0]->b=trs[1]->b=b;
        for(auto i : newtraps) {
            i->fixRight();
        }
        for(auto i : newtraps) {
            GD_LAYER();
            i->draw();
        }

    }
    string getstr(int cnt) {
        if(split==-1) return "Trap_" + to_string(cnt);
        else if(xnode) return "Xnode_on_" + to_string(split) +"_" +to_string(cnt);
        else return "Ynode_on_" + to_string(split) +"_" +to_string(cnt);
    }
    void traverse() {
        int cnt=0;
        vector<vector<string>> mye;
        unordered_map<node*,string> s;
        stack<node*> st;
        st.push(this);
        s[this]=getstr(cnt++);
        vector<trap*> trapst;
        while(!st.empty()) {
            auto at = st.top(); st.pop();
            if(at->split==-1) {
                trapst.push_back(at->trp);
                continue;
            }
            if(!s.count(at->l)) {
                s[at->l]=at->l->getstr(cnt++);
                st.push(at->l);
            }
            if(!s.count(at->r)) {
                s[at->r]=at->r->getstr(cnt++);
                st.push(at->r);
            }
            mye.push_back({s[at],s[at->l]});
            mye.push_back({s[at],s[at->r]});
        }
        for(auto i : trapst) {
            if(i->r[0]) mye.push_back({s[i->leaf], s[i->r[0]->leaf], "TopRight"});
            if(i->r[1]) mye.push_back({s[i->leaf], s[i->r[1]->leaf], "BottomRight"});
        }
        for(auto i: mye) {
            cout << i << '\n';
        }
    }
};

vi adj[mxN];
void inputsegments() {
    freopen("generalpos.in","r",stdin);
    int n; cin >> n;
    pts.resize(n);
    for(auto& p : pts) read(p);
    int m; cin >> m;
    es.resize(m);
    for(auto& e : es) {
        cin >> e.a >> e.b;
    }
}
vector<vector<pt>> inputpolygons() {
    freopen("onepoly.in","r",stdin);
    int k; cin >> k;
    vector<vector<pt>> res;
    for(int i=0;i<k;++i) {
        int n; cin >> n;
        int beg = pts.size();
        vector<pt> poly;
        for(int j=0;j<n;++j) {
            pt p; read(p);
            poly.push_back(p);
            pts.push_back(p);
            es.push_back({j+beg, beg+(j+1)%n, i});
        }
        res.push_back(poly);
    }
    return res;
}
void draw(const vector<pt>& pol) {
    GD_POLYGON("red:#00ff0080",
        for(auto p : pol) GD_POLYPOINT(p.X,p.Y);
    );
}
const int myinf = 101;
node construct() {
    random_shuffle(all(es));
    // Add bounding box

    int n = pts.size(),m=es.size();
    for(auto& e : es) {
        if(comp(pts[e.b],pts[e.a])) swap(e.a,e.b);
    }
    for(int i:{1,-1}) for(int j:{-1,1})
        pts.push_back({j*myinf,i*myinf});
    es.push_back({n,n+1,-2});
    es.push_back({n+2,n+3,-3});
    trap bounding = {n,n+1,m,m+1};
    node DAG(&bounding); // initialize to be the bounding box
    bounding.leaf = &DAG;
    for(int i=0;i<m;++i) {
        // GD_PAUSE();
        auto& e = es[i];
        GD_SEGMENT(pts[e.a].X,pts[e.a].Y,pts[e.b].X,pts[e.b].Y);
        int x = pts[e.a].X;
        DAG.insert(i);
        // DAG.traverse();
    }
    return DAG;
}
int main() {

    GD_INIT("trapmap.html");
    GD_LOG_TO_STDERR(false);
    auto polys = inputpolygons();
    // inputsegments();


    GD_PAUSE();
    auto DAG = construct();
    for(int j=0;j<100;++j) {
        
        pt p = {rnd(-myinf,myinf),rnd(-myinf,myinf)};
        // pt p={-1,-1}; read(p);
        // pt p= {140,-90};
        GD_LAYER();   
        auto nd = DAG.search(p);
        auto id = nd->trp->getpolygon();
        if(id!=-1) draw(polys[id]);
        nd->trp->draw(1);
        GD_POINT(p.X,p.Y);
    }
}
/*
Tests:
4
0 0
2 1
1 0
3 0
2
0 1
2 3

6
0 0
10 10
5 0
20 -5
-10 -10
30 -10
3
0 1
2 3
4 5
*/