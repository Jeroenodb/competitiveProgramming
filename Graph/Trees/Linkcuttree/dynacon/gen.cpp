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
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
bool connected(int a, int b) {
    if(a==b) return true;
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
    return connected;
}
int main() {
    freopen("dynacon.in","w",stdout);
    ofstream fout("dynacon.out");
    int n = 1000, m = 5000;
    cout << n << ' ' << m << '\n';
    for(int j=0;j<m;++j) {
        int type = rnd(0,5),a,b;
        if(type<=2) {
            int rep = 10;
            do {
                a = rnd(1,n-1);
                b = rnd(a+1,n);
            } while(--rep and connected(a,b));
            if(rep<=0) {
                j--;
                continue;
            }
            adj[a].insert(b);
            adj[b].insert(a);
            if(rnd(0,1)==0) swap(a,b);
            cout << "add " ;
        } else if(type==3) {
            int rep = 10;
            do {
                a = rnd(1,n-1);
                b = rnd(a+1,n);
            } while(--rep and !adj[a].count(b));
            if(rep<=0) {
                j--;
                continue;
            }
            adj[a].erase(b);
            adj[b].erase(a);
            if(rnd(0,1)==0) swap(a,b);
            cout << "rem "; 
        } else {
            do {
            a = rnd(1,n);
            b = rnd(1,n);
            } while(a==b);
            cout << "conn ";
            fout << (connected(a,b)?"YES\n":"NO\n");
        }
        cout << a << ' ' << b << '\n';
    }
}