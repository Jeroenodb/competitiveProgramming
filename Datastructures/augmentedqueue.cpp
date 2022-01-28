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
const long long MOD = 998244353;
class mint {
public:
    int d;
    mint () {d=0;}
    mint (long long _d) : d(_d%MOD){};
    mint operator*(const mint& o) const {
        return ((ll)d*o.d)%MOD;
    }
    mint operator+(const mint& o) const {
        long long tmp = d+o.d;
        if(tmp>=MOD) tmp-=MOD;
        return tmp;
    }
    mint operator-(const mint& o) const {
        long long tmp = d-o.d;
        if(tmp<0) tmp+=MOD;
        return tmp;
    }
    bool operator==(const mint& o) {
        return d==o.d;
    }
    friend mint& operator+=(mint& a, const mint& o) {
        a.d+=o.d;
        if(a.d>=MOD) a.d-=MOD;
        return a;
    }
};
typedef pair<mint,mint> pmi;
struct st1 {
    stack<pmi> st;

    void add(pmi p) {
        // fill p in previous function
        if(st.empty()) {
            st.push(p);
            return;
        }
        auto q = st.top();
        st.push({q.first*p.first, q.first*p.second+q.second});
    }
    void pop() {
        st.pop();
    }
    bool empty() {
        return st.empty();
    }
    mint f(mint x) {
        if(st.empty()) return x;
        else return st.top().first*x+st.top().second;
    }
};
struct st2 {
    stack<pair<pmi,pmi>> st;

    void add(pmi p) {
        // fill p in previous function
        if(st.empty()) {
            st.push({p,p});
            return;
        }
        auto q = st.top().second;
        st.push({p, {p.first*q.first, p.first*q.second+p.second}});
    }
    void pop() {
        st.pop();
    }
    bool empty() {
        return st.empty();
    }
    mint f(mint x) {
        if(st.empty()) return x;
        auto f = st.top().second;
        return f.first*x+f.second;
    }
};
struct Q {
    st1 s1;
    st2 s2;
    void add(pmi p) {
        s2.add(p);
    }
    void pop() {
        if(s1.empty()) {
            while(!s2.empty()) {
                s1.add(s2.st.top().first);
                s2.pop();
            }
        }
        s1.pop();
    }
    mint f(mint x) {
        return s2.f(s1.f(x));
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> q;
    Q qu;
    while(q--) {
        int t; cin >> t;
        if(t==0) {
            int a,b; cin >> a >> b;
            qu.add({a,b});
        } else if(t==1) {
            qu.pop();
        } else {
            int x; cin >> x;
            cout << qu.f(x).d << '\n';
        }
    }
}