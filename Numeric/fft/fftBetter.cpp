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
void revperm(cd* in, int n) {
    int lg = __lg(n);
    for(int i=0,j=0;i<n;++i) {
        if(i<j) swap(in[i],in[j]);
        for(int k=0;k<lg;++k) {
            int pw = 1<<k;
            if(!(pw & j)) {
                j&=(1<<k)-1;
                j|=1<<k;
                break;
            }
        }
    }
}

cd w[mxN+1]; // stores e^(j*i/mxN) for each j in [0,n-1]
const double PI = 3.14159265358979323846;
void precomp() {
    for(int i= 0;i<mxN;++i) {
        w[i] = polar(1.0,2*PI*i/mxN);
    }
}
void fft(cd* in, int n, bool reverse=false) {
    int lg = __lg(n);
    assert(1<<lg == n);
    int stride = mxN/n;
    revperm(in,n);
    for(int s=1;s<=lg;++s) {
        int pw = 1<<s;
        int mstride = stride*(n>>s);
        for(int j=0;j<n;j+=pw) {
            // do FFT merging on out array
            cd* even = in+j, *odd = in+j+pw/2;
            for(int i=0;i<pw/2;++i) {
                cd& power = w[reverse?mxN-mstride*i:mstride*i];
                auto tmp = power*odd[i];
                odd[i] = even[i] - tmp;
                even[i] = even[i] + tmp;
            }
        }
    }
    if(reverse) for(int i=0;i<n;++i) in[i]/=n;
}
int k;

vector<cd> polymul(vector<cd>& a, vector<cd>& b) {
    int n = a.size(), m = b.size(), ptwo = 1;
    while(ptwo<(n+m)) ptwo*=2;
    a.resize(ptwo), b.resize(ptwo);
    fft(a.data(),ptwo); 
    fft(b.data(),ptwo);
    vector<cd> c(ptwo);
    for(int i=0;i<ptwo;++i) 
        c[i] = a[i]*b[i];
    fft(c.data(),ptwo,true);
    for(int i=2;i<=2*k;++i) {
        cout << (ll)(round(a[i].real())) << ' ';
    }
    c.resize(n+m-1);
    return c;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precomp();
    int n,m; cin >> k >> n >> m;
    vi ap(k+1),ba(k+1);
    for(int i=0;i<n;++i) {
        int apple; cin >> apple;
        ap[apple]++;
    }
    for(int i=0;i<m;++i) {
        int banana; cin >> banana;
        ba[banana]++;
    }
    auto comb = convolution(ap,ba);
    // for(int i=2;i<=2*k;++i) {
    //     cout << comb[i] << ' ';
    // }
    
}