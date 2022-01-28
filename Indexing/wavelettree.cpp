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

struct RankDS {
    typedef unsigned int uint;
    // Uses 2*n bits for a bitset of size n
    vector<uint>  bits,pref;
    RankDS() {}
    RankDS(vector<bool> input) {
        int n = input.size(), w = (n+31)/32;
        bits.resize(w),pref.resize(w);
        int prf=0,j=-1;
        for(int i=0;i<n;++i) {
            if(i%32==0) {
                pref[++j]=prf;
            }
            if(input[i]) {
                prf++;
                bits[j]|=1U<<(i%32);
            }
        }

    }
    int rank(int i) {
        if(i==-1) return 0;
        int j = i/32,shift = 31-i%32;
        return pref[j]+__builtin_popcount(bits[j]<<shift);
    }
};
template<typename V,typename T> struct WT { // wavelet tree
    // for a string of length n, with alphabet sigma, uses O(n log(sigma)) bits space,
    // which is linear in the input string (each character in the input has to have log(sigma) bits)
    RankDS ra;
    WT *l=NULL, *r=NULL;
    int sz=0;
    V lo,hi;
    friend int size(WT* wt) {
        if(wt) return wt->sz;
        return 0;
    }
    WT(V low, V high, T start, T end) { // both are halfopen intervals
        lo = low,hi = high;
        V mid = lo+(hi-lo)/2;
        sz = end-start;
        vector<bool> goesleft(distance(start,end));
        transform(start,end,goesleft.begin(),[&mid](V x) {return x<mid;});
        ra = RankDS(goesleft);
        if(lo+1==hi) return;
        auto middle = stable_partition(start,end,[&mid](V x){return x<mid;});
        if(middle!=start) l = new WT(lo,mid,start,middle);
        if(middle!=end) r = new WT(mid,hi,middle,end);
    }
    int rank(V val, int i) {
        // determines how times val appears in S[:i]
        if(lo+1==hi) return i+1;
        V mid = lo+(hi-lo)/2;
        if(val<mid) {
            if(!l) return 0;
            return l->rank(val,ra.rank(i)-1);
        } else {
            if(!r) return 0;
            return r->rank(val,i-ra.rank(i));
        }
    }
    V kth(int k, int i, int j) { 
        if(lo+1==hi) return lo;
        int cnt2 = ra.rank(j);
        int cnt = cnt2-ra.rank(i-1);
        if(cnt>=k) {
            // go to left
            return l->kth(k,ra.rank(i)-1,ra.rank(j)-1);
        } else {
            // go to right
            return r->kth(k-cnt,max(0,i-ra.rank(i)), j-ra.rank(j));
        }
    }
    int greater(V val, int i) {
        // determines how times val appears in S[:i]
        if(val<lo) return i+1;
        if(val>=hi-1) return 0;
        int res=0;
        if(l) res+=l->greater(val,ra.rank(i)-1);
        if(r) res+=r->greater(val,i-ra.rank(i));
        return res;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    typedef WT<int,vi::iterator> myWT;
    int n; cin >> n;
    vi a(n); for(auto& i : a) cin >> i;
    myWT wt(1,oo+1,all(a));
    int q; cin >> q;
    while(q--) {
        int i,j,k; cin >> i >> j >> k;
        --i,--j;
        int res = wt.greater(k,j);
        if(i!=0) res-=wt.greater(k,i-1);
        cout << res << '\n';
    }
        
}