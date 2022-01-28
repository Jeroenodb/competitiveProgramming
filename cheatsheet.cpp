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

// Geometry
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
// DSU
struct DSU{
    vector<int> sz,parent;
    int components;
    DSU(int n) {
        sz.assign(n,1);
        components = n;
        parent.resize(n);
        iota(all(parent),0);
    }
    void link(int a, int b) {
        components--;
        if(sz[a]<sz[b]) {
            swap(a,b);
        }
        sz[a]+=sz[b];
        parent[b] = a;
    }
    bool unite(int a, int b) {
        int pa = find(a),pb = find(b);
        if(pa!=pb) link(pa,pb);
        return pa!=pb;
    }
    int find(int a) {
        if(a==parent[a]) return a;
        return parent[a] = find(parent[a]);
    }
};
// segment tree 
struct segtree {
    int ptwo;
    vector<ll> seg;
    segtree(){}
    ll& operator[](int i) {
        return seg[i+ptwo];
    }
    segtree(int nn) {
        ptwo=1;
        while(ptwo<nn) 
            ptwo*=2;
        seg.assign(ptwo*2,0);
    }
    auto query(int l, int r) {
        assert(l>=0 and l<ptwo and r >=0 and r<ptwo);
        l+=ptwo; r+=ptwo;
        ll res = -oo;
        while(l and l<=r) {
            if(l%2==1) res = max(res,seg[l++]);
            if(r%2==0) res = max(res,seg[r--]);
            l/=2; r/=2;
        }
        return res;
    }
    void update(int i, ll val) {
        assert(i>=0 and i<ptwo);
        i+=ptwo;
        seg[i] = val;
        for(i/=2;i>=1;i/=2) {
            seg[i] = max(seg[2*i],seg[2*i+1]);
        }
    }
};
// suffix array
vector<int> suffixArray(string& s, int symbols = 28) {

    s.push_back('a'-1);
    int n = s.length();
    vector<int> oldlabel(n);
    for (int i = 0; i < n-1; ++i) {
    oldlabel[i] = s[i] - 'a' + 1;
    }

    vector<int> sufarr(n);
    iota(all(sufarr),0);
    sort(all(sufarr), [&](int a, int b) {return oldlabel[a] < oldlabel[b];});
    int maxk = 0;
    while ((1 << maxk) < n) ++maxk;
    
    // output of radix sort
    int mxCnt = max(symbols+1,n);
    vector<int> output(n),count(mxCnt);
    for (int k = 0; k < maxk; ++k) {
        for(int& i: sufarr) {
            i-=1<<k;
            while(i<0) i+=n;
        }
        //radix sort
        fill(count.begin(),count.end(),0);
        for(int i=0;i<n;++i) {
            count[oldlabel[i]]++;
        }
        for(int i=1;i<mxCnt;++i) {
            count[i]+=count[i-1];
        }
        for(int i=n-1;i>=0;--i) {
            output[--count[oldlabel[sufarr[i]]]] = sufarr[i];
        }
        swap(sufarr,output);
        output[sufarr[0]] = 0;
        int l = 0;
        for (int i = 1; i < n; ++i) {
                int io = sufarr[i]+(1<<k);
                while(io>=n) io-=n;
                int jo = sufarr[i-1]+(1<<k);
                while(jo>=n) jo-=n;
            if (pair<int,int>{oldlabel[sufarr[i]],oldlabel[io]}  > pair<int,int>{oldlabel[sufarr[i - 1]], oldlabel[jo]} ) 
                    l++;
            output[sufarr[i]] = l;
        }
        swap(output,oldlabel);
        // for(int i=0;i<n;++i) {
        //     cout << s.substr(sufarr[i]) << endl;
        // } cout << endl;
     if(l==n-1) break;
 }
    return sufarr;
}
vector<int> kasai(string& s, vector<int>& sa) {
    int n=s.size(),k=0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);

    for(int i=0; i<n; i++) rank[sa[i]]=i;

    for(int i=0; i<n; i++, k?k--:0) {
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}
// fenwick tree
template<typename T> struct fenwick {
    int n;
    vector<T> fen;
    fenwick(){}
    fenwick(int nn) {
        fen.resize(nn+1);
        n = nn;
    }
    auto sum(int i) {
        T ans = 0;
        while(i) {
            ans+=fen[i];
            i&=i-1;
        }
        return ans;
    }
    auto query(int l, int r) {
        return sum(r+1)-sum(l);
    }
    void update(int i, T val) {
        ++i;
        while(i<=n) {
            fen[i]+=val;
            i+= i&(-i);
        }
    }
};
// Fast input output
ios_base::sync_with_stdio(false);
cin.tie(NULL);