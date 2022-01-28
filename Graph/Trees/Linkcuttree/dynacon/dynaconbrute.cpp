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
unordered_set<int> adj[mxN];
bitset<mxN> visited;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin >> n >> m;
    for(int j=0;j<m;++j) {
        string type; cin >> type;
        int a,b; cin >> a >> b,--a,--b;
        if(type=="add") {
            adj[a].insert(b);
            adj[b].insert(a);
        } else if(type=="rem") {
            adj[a].erase(b);
            adj[b].erase(a);
        } else {
            vi st = {a};
            visited[a] = true;
            bool connected = false;
            for(int i=0;i<(int)st.size();++i) {
                for(int to: adj[st[i]]) {
                    if(to==b) {
                        connected = true;
                        break;
                    }
                    if(!visited[to]) {
                        st.push_back(to);
                        visited[to] = true;
                    }
                }
            }
            for(int i: st) {
                visited[i] = false;
            }
            cout << (connected?"YES\n":"NO\n");
        }
    }
}