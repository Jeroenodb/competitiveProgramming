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
const int mxN = 1e5+1;
const ll oo = 1e18;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
ll floordiv(ll a, ll b) { // floored division
    if (b < 0) a *= -1, b *= -1;
    if (a >= 0) return a / b;
    return -((-a + b - 1) / b);
}
struct line {
    int a,b;
    ll eval (ll x) const {
        return a*x+b;
    }
    bool operator<=(const line& o) const {
        return a<=o.a;
    }
    ll intersect(const line& o) const {
        return floordiv(o.b-b,a-o.a);
    }
};
ostream& operator<<(ostream& c, const line& l) {
    return c << l.a << "x" << showpos << l.b << noshowpos;
}
struct linecontainer {
    // holds upper convex hulls of lines

    tree<line,ll, less_equal<line>> s; 

    bool isect(decltype(s)::iterator x, decltype(s)::iterator y) {
		if (y == s.end()) { x->second = oo; return 0; }
		if (x->first.a == y->first.a) x->second = x->first.b > y->first.b ? oo : -oo;
		else x->second = x->first.intersect(y->first);
		return x->second >= y->second;
	}
    void add(line l) {
        auto [z,succeeded] = s.insert({l,0});
        auto y = z++, x = y;
		while (isect(y, z)) 
            z = s.erase(z);
		if (x != s.begin() && isect(--x, y)) 
            isect(x, y = s.erase(y));
		while ((y = x) != s.begin() && (--x)->second >= y->second) 
            isect(x, s.erase(y));

    }
    ll getmax(ll x) {
        auto iter = s.node_begin();
        ll ans = -oo;
        while(iter!=s.node_end()) {
            if(x <= (*iter)->second) {
                ans = max(ans,(*iter)->first.eval(x));
                iter = iter.get_l_child();
            } else {
                iter = iter.get_r_child();
            }
        }
        return ans;
    }
};

int main() {
    linecontainer l;
    l.add({1,1});
    l.add({-1,1});
    cout << l.s << endl;
    cout << l.getmax(4) << ' ' << l.getmax(2);
}