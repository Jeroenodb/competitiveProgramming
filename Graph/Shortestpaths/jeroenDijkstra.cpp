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
const int B=300;
template<typename T> struct sqrt_queue {
    vector<T> d;
    vector<pair<T,int>> mn;
    sqrt_queue(int n) {
        d.assign(n,oo);
        mn.assign((n+B-1)/B, {oo,-1});
    }
    void decreaseKey(int i, int k) {
        d[i] = min(d[i],k);
        int j = i/B;
        mn[j] = min(mn[j],{d[i],i});
    }
    int pop() {
        pair<T,int> best = {oo,-1};
        for(auto i : mn) best=min(best,mn);
        int j = best.second/B;
        mn[j] = {oo,-1};
        d[i]=oo;
        for(int i=j*B;i<min(d.size(),(j+1)*B);++i) {
            mn[j] = min(mn[j],{d[i],i});
        }
        return best.second;
    }
};
int main() {
    
}