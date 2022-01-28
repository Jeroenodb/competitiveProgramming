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
typedef double F;
void gaussianElim(vector<valarray<F>>& A) {
    int at= 0;
    for(int i=0;i<4;++i) {
        for(int j=at;j<A.size();++j) if(abs(A[j][i])>abs(A[at][i])) 
            swap(A[j],A[at]);
        if(A[at][i]==0) 
            continue;
        for(int j=0;j<4;++j) if(j!=at and A[j][i]!=0) {
            A[j]-=A[at]*(A[j][i]/A[at][i]);
        }
        ++at;
        for(auto v : A) {
            debug(v);
        }
        cout << '\n';
    }
}
int main() {
    vector<valarray<F>> A = {{1,1,0,0,1,0,0,0},{1,0,1,0,0,1,0,0},{0,1,0,1,0,0,1,0},{0,0,1,1,0,0,0,1}};
    gaussianElim(A);
}
