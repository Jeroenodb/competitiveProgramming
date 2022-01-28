#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <algorithm>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
const int mxN = 1e5+1;
template <class T, int ...Ns> struct BIT {
    T val = 0;
    void upd(T v) { val += v; }
    T query() { return val; }
};
 
template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
    BIT<T,Ns...> bit[N + 1];
    template<typename... Args> void upd(int pos, Args... args) {
        for (; pos <= N; pos += (pos&-pos)) bit[pos].upd(args...);
    }
    template<typename... Args> T sum(int r, Args... args) {
        T res = 0; for (; r; r -= (r&-r)) res += bit[r].query(args...); 
        return res;
    }
    template<typename... Args> T query(int l, int r, Args... args) {
        return sum(r,args...)-sum(l-1,args...);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q; cin >> n >> q;
    BIT<ll, 1001, 1001>* bit = new BIT<ll, 1001, 1001>();
    bitset<1001> forest[1001];
    for(int j=1;j<=n;++j) {
        string s; cin >> s;
        for(int i=0;i<n;++i) {
            if(s[i]=='*') {
                bit->upd(i+1,j, 1);
                forest[i+1][j] = true;
            }
        }
    }
    while(q--) {
        int t; cin >> t;
        if(t==1) {
            int y,x; cin >> y >> x;
            bit->upd(x,y,1-2*forest[x][y]);
            forest[x].flip(y);
        } else {
            int y1,x1,y2,x2; cin >> y1 >> x1>>y2>>x2;
            cout << bit->query(x1,x2,y1,y2) << endl;
        }
    }
}