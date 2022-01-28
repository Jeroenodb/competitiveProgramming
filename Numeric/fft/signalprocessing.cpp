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
    w[1] = 0.9999999999281891767097750958838504902604803331095158019530 +
0.000011984224905069706421521561596988984804731977538386699101149i;
    w[2] = 0.9999999997127567068494139722186417760890894579182852527107 +
0.000023968449808418218729186577165021820094761474895673032759838i;
    w[mxN] = 1;
    for(int i= 3;i<mxN;++i) {
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
int k;
vector<ll> convolution(vi& aa, vi& bb) {
    int n = aa.size(), m = bb.size(), ptwo = 1;
    while(ptwo<(n+m)) ptwo*=2;
    fill(c,c+ptwo,0); fill(b,b+ptwo,0);
    copy(all(aa),c), copy(all(bb),b);
    fft(c,ptwo,a); 
    fft(b,ptwo,c);
    for(int i=0;i<ptwo;++i) 
        c[i] *= a[i];
    fft(c,ptwo,a,true);
    // vector<ll> cc(k);
    for(int i=0;i<n+m-1;++i) {
        cout << (ll)(round(a[i].real())) << ' ';
    }
    return {};
    // return cc;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precomp();
    int n,m; cin >> n >> m;
    vi aa(n); for(auto& i: aa) cin >> i;
    vi bb(m); for(auto& i: bb) cin >> i;
    reverse(all(bb));
    auto comb = convolution(aa,bb);
    // for(int i=2;i<=2*k;++i) {
    //     cout << comb[i] << ' ';
    // }
    
}