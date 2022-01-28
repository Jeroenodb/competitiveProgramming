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
const long long MOD = 2;
class mint {
public:
    int d;
    mint () {d=0;}
    mint (long long _d) : d(_d%MOD){};
    bool operator==(const mint& o) {
        return d==o.d;
    }
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
    mint& operator-() {
        d = MOD-d;
    }
    mint operator^(long long b) const {
        mint tmp = 1;
        mint power = *this;
        while(b) {
            if(b&1) {
                tmp = tmp*power;
            }
            power = power*power;
            b/=2;
        }
        return tmp;
    }
    mint operator/(const mint& o) {
        return *this * (o^(MOD-2));
    }
};
ostream& operator<<(ostream& c, const mint& o) {
    return c << (o.d>MOD/2?-MOD+o.d:o.d);
}
mint& operator+=(mint& a, const mint& o) {
    a.d+=o.d;
    if(a.d>=MOD) a.d-=MOD;
    return a;
}
vector<mint> BM(vector<mint> x) {
	//ls: (shortest) relation sequence (after filling zeroes) so far
	//cur: current relation sequence
	vector<mint> ls,cur;
	//lf: the position of ls (t')
	//ld: delta of ls (v')
	int lf;
    mint ld;
	for(int i=0;i<int(x.size());++i) {
		mint t=0;
		//evaluate at position i
		for(int j=0;j<int(cur.size());++j)
			t+=x[i-j-1]*cur[j];
		if(t==x[i]) continue; //good so far

		if(!cur.size()) {
            //first non-zero position
			cur.resize(i+1);
			lf=i; ld=t-x[i];
			continue;
		}
		//cur=cur-c/ld*(x[i]-t)
		mint k= -(x[i]-t)/ld;/*1/ld*/;
		vector<mint> c(i-lf-1); //add zeroes in front
		c.push_back(k);
		for(int j=0;j<int(ls.size());++j)
			c.push_back(-ls[j]*k);
		if(c.size()<cur.size()) 
            c.resize(cur.size());
		for(int j=0;j<int(cur.size());++j)
			c[j]+=cur[j];
		//if cur is better than ls, change ls to cur
		if(i-lf+(int)ls.size()>=(int)cur.size())
			ls=cur,lf=i,ld=t-x[i];
		cur=c;
	}

	return cur;
}
int main() {
    vector<mint> v = {1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,0,0,1,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,1,1,0,0,1,0,0,0,1,1};
    auto rec = BM(v);
    cout << v << '\n';
    cout << rec << '\n';
    cout << "a_i = ";
    for(int i=0;i<rec.size();++i) {
        if(rec[i]==0) continue;
        if(i and rec[i].d<=MOD/2) cout << " + ";
        else cout << ' ';
        cout << rec[i] << "*a_{i-" << i+1 << '}';
    }
    cout << '\n';
}