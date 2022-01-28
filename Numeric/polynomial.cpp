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
typedef vector<double> poly;
poly der(const poly& p) { // derivative
    poly res(p.size()-1);
    for(int i=1;i<p.size();++i) {
        res[i-1]=(i+1)*p[i];
    }
    return res;
}
template<typename T> T eval(const poly& p, T x) {
    T res=0;
    for(auto i = p.rbegin();i!=p.rend();++i) {
        res = res*x + *i;
    }
    return res;
}

int deg(const poly& p) {return p.size()-1;}
vector<double> zeros(const poly& p, double mn = -1e9, double mx = 1e9) {
    if(deg(p)==1) return {-(double)p[0]/p[1]};
    vector<double> res;
    auto extr = zeros(der(p),mn,mx);
    extr.insert(extr.begin(),mn);
    extr.push_back(mx);
    int n = extr.size();
    for(int i=1;i<n;++i) {
        auto l = extr[i-1], r = extr[i];
        auto fl = eval(p,l), fr = eval(p,r);
        if((fl>0)^(fr>0)) {
            for(int rep=0;rep<55;++rep) {
                auto mid = (l+r)/2;
                if((eval(p,mid)>0) == (fl>0)) {
                    l=mid;
                } else r = mid;
            }
            res.push_back((l+r)/2);
        }
    }
    return res;
}
int main() {
    poly p = {1,0,-1,0.001};
    auto v = zeros(p);
    cout << v << '\n';
    for(auto val : v) cout << eval(p,val) << ' ';
    
}