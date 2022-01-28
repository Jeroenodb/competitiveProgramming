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
int main() {
    string s; cin >> s;
    int n=s.size();
    string t; t.reserve(n);
    int cnt[256]={};
    vi rank(n);
    for(int i=0;i<n;++i) {
        rank[i] = cnt[s[i]]++;
    }
    for(int i=1;i<256;++i) cnt[i]+=cnt[i-1];
    int i=0;
    while(s[i]!='#') {
        t.push_back(s[i]);
        i = cnt[s[i]-1]+rank[i];
    }
    reverse(all(t));
    cout << t << '\n';
}