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
const int mxN = 1e1+1;
const ll oo = 1e18;
ll dist[2][mxN];
template<typename T, int B> struct sqrt_queue {
    vector<T> d;
    vector<pair<T,int>> mn;
    vector<bool> vis;
    sqrt_queue(int n) {
        d.assign(n,oo+1);
        vis.resize(n);
        mn.assign((n+B-1)/B, {oo,-1});
    }
    void decreaseKey(int i, T k) {
        if(vis[i]) return;
        d[i] = min(d[i],k);
        int j = i/B;
        mn[j] = min(mn[j],{d[i],i});
    }
    pair<T,int> pop() {
        pair<T,int> best = {oo,-1};
        for(auto i : mn) best=min(best,i);
        if(best.second==-1) return {-1,-1};
        int j = best.second/B;
        mn[j] = {oo,-1};
        vis[best.second]=true;
        d[best.second]=oo+1;
        for(int i=j*B;i<min((int)d.size(),(j+1)*B);++i) {
            mn[j] = min(mn[j],{d[i],i});
        }
        return best;
    }
};

int main() {
    int n; cin >> n;
    vector<ll> a(n); for(auto& i : a) cin >> i;
    sqrt_queue<ll,300> pq(a[0]);
    pq.decreaseKey(0,0);
    ll ans=0;
    while(true) {
        auto [d,at] = pq.pop();
        if(at==-1) break;
        ans^=d;
        for(auto& i : a) {
            int to = (at+i)%a[0];
            pq.decreaseKey(to,d+i);
        }
    }
    cout << ans << '\n';

}