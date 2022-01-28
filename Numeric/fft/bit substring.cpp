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
const int mxN = 1<<19, oo = 1e9;
typedef complex<double> cd;
void revperm(cd* in, int n, cd* out) {
    int lg = __lg(n);
    for(int i=0;i<n;++i) {
        int to = 0;
        for(int j =0; j<lg;++j) {
            bool set = ((1<<j)&i)!=0;
            to|=set<<(lg-j-1);
        }
        out[to] = in[i];
    }
}

cd w[mxN+1]; // stores e^(j*i/mxN) for each j in [0,n-1]
const double PI = 3.14159265358979323846;
void precomp() {
    w[0] = 1;
    w[mxN] = 1;
    for(int i= 1;i<mxN;++i) {
        w[i] = polar(1.0,2*PI*i/mxN);
    }

}
void fft(cd* in, int n, cd* out, bool reverse=false) {
    int lg = __lg(n);
    assert(1<<lg == n);
    int stride = mxN/n;
    revperm(in,n,out);
    for(int s=1;s<=lg;++s) {
        int pw = 1<<s, mstride = stride*(n>>s);
        for(int j=0;j<n;j+=pw) {
            cd* even = out+j, *odd = out+j+pw/2;
            for(int i=0;i<pw/2;++i) {
                cd& power = w[reverse?mxN-mstride*i:mstride*i];
                auto tmp = power*odd[i];
                odd[i] = even[i] - tmp;
                even[i] = even[i] + tmp;
            }
        }
    }
    if(reverse) for(int i=0;i<n;++i) out[i]/=n;
}
cd a[mxN],b[mxN],c[mxN];
vector<ll> convolution(vi& aa, vi& bb, int k) {
    int n = aa.size(), m = bb.size(), ptwo = 1;
    while(ptwo<(n+m)) ptwo*=2;
    fill(c,c+ptwo,0); fill(b,b+ptwo,0);
    copy(all(aa),c), copy(all(bb),b);
    fft(c,ptwo,a); 
    fft(b,ptwo,c);
    for(int i=0;i<ptwo;++i) 
        c[i] *= a[i];
    fft(c,ptwo,a,true);
    vector<ll> cc(k);
    for(int i=n;i<n+k;++i) {
        cout << (ll)(round(a[i].real())) << ' ';
    }
    return cc;
}
int main() {
    precomp();
    string s; cin >> s;
    int n = s.size();
    s.push_back('1');
    vi aa;
    ll ans0=0;
    for(int i=0,between=1;i<=n;++i,between++) {
        if(s[i]=='1') {
            ans0+=(ll)between*(between-1)/2;
            aa.push_back(between);
            between=0;
        }
    }
    cout << ans0 << ' ';
    auto bb = aa;
    reverse(all(bb));
    convolution(aa,bb,n);
    // cout << cc << '\n';
}