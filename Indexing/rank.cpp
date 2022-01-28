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
struct RankDS {
    typedef unsigned int uint;
    // Uses 2*n + O(1) bits for a bitset of size n
    vector<uint>  bits,pref;
    RankDS() {}
    RankDS(vector<bool> input) {
        int n = input.size(), w = (n+31)/32;
        bits.resize(w),pref.resize(w);
        int prf=0,j=-1;
        for(int i=0;i<n;++i) {
            if(i%32==0) pref[++j]=prf;
            if(input[i]) {
                prf++;
                bits[j]|=1U<<(i%32);
            }
        }
    }
    int rank(int i) {
        // O(1)
        int j = i/32,shift = 31-i%32;
        return pref[j]+__builtin_popcount(bits[j]<<shift);
    }
};
int main() {
    vector<bool> in = {0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,1,1,0,0,1,0,1};
    debug(in.size());
    RankDS rank(in);
    cout << in << '\n';
    for(int i=0;i<(int)in.size();++i) {
        cout << rank.rank(i) << ' ';
    }
}
