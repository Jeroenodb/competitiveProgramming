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
typedef __int128_t Int;
const ll store=1e6;
const auto makesieve() {
    bitset<store> sieve;
    array<int,store> res={};
    for(int i = 2; i < store;++i) {
        if(!sieve[i]) {
            res[i]=i;
            for(ll j = (ll)i*i;j<store;j+=i) {
                if(!sieve[j]) res[j]=i;
                sieve[j] = true;
            }
        }
    }
    return res;
}
const auto fact = makesieve();

using ull = uint64_t;
using uInt = __uint128_t;

ull binpower(ull base, ull e, ull mod) {
    ull result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (uInt)result * base % mod;
        base = (uInt)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(ull n, ull a, ull d, int s) {
    ull x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (uInt)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};
bool isPrime(ull n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    ull d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
ull pollard(ull n,ull start=2) {
    ull x=start,x_fixed=start,d=1;
    auto g = [&](ull a) {
        return (ull)(((Int)x*x+1)%n);
    };
    ull size=2;
    while(d==1) {
        ull cnt=size;
        do {
            x = g(x);
            d = gcd(max(x,x_fixed)-min(x,x_fixed),n);
        } while(d==1 and --cnt);
        size*=2; 
        x_fixed = x;
    }
    if(d==n) return -1;
    return d;
}
void factorrec(ull n, map<ull,int>& m) {
    if(n>=store) {
        if(isPrime(n)) {
            m[n]++;
            return;
        }
        for(int start=2;;++start) {
            auto p = pollard(n,start);
            if(p!=-1) {
                assert(n%p==0);
                factorrec(p,m), factorrec(n/p,m);
                return;
            }
        }
    }
    while(n!=1) {
        auto f = fact[n];
        m[f]++;
        n/=f;
    }
}
vector<pair<ull,int>> factorize(ull n) {
    map<ull,int> cnt;
    // couple rounds of trial division
    for(int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        while(n%i==0) {
            cnt[i]++;
            n/=i;
        }
    }
    factorrec(n,cnt);
    return vector<pair<ull,int>>(all(cnt));
}
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
vector<ull> ds;
void divs(const vector<pair<ull,int>>& fs, int i=0, ull n=1) {
    if(i==fs.size()) {
        ds.push_back(n);
        return;
    }
    divs(fs,i+1,n);
    for(int j=0;j<fs[i].second;++j) {
        n*=fs[i].first;
        divs(fs,i+1,n);
    }
}
int main() {
    int t; cin >> t;
    while(t--) {
        ull n; cin >> n;
        auto fs = factorize(n);
        ds.clear();
        divs(fs);
        ull ans = 0;
        for(auto& d : ds) {

            auto rhs = 1+n/d;
            // find phi
            auto fh = factorize(rhs);
            ull phi = rhs;
            for(auto [p,cnt]: fh) {
                phi/=p;
                phi*=(p-1);
            }
            ans+=phi;
        }
        cout << ans << '\n';
    }
}