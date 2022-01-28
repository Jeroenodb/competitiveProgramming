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
int cnt[mxN],output[mxN];
template<typename T, typename V> void radixsort(T start, T end, int k, V key) {
    fill(cnt,cnt+k,0);
    for(auto it=start;it!=end;++it) {
        cnt[key(*it)]++;
    }
    for(int i=1;i<k;++i) cnt[i]+=cnt[i-1];
    for(auto it = end;--it!=start;) {
        output[--cnt[key(*it)]]=*it;
    }
    move(output,output+distance(start,end),start);
}
int label[mxN];
vi rec(int n, int k=256) {
    // do some tricky memory shifting
    for(int i=0,j=0;i<n;i+=3,j++) {
        output[j]=label[i];
    }
    for(int i=0,j=0;i<n;i+=3,j+=2) {
        label[j]=label[i+1];
        label[j+1]=label[i+2];
    }
    move(output, output+(n+2)/3,label+2*(n+2)/3);
    // calculate new labels
    vi order(2*n/3);
    iota(all(order),0);
    radixsort()
    

}
vi suffixArray(const string& s) {
    int n=s.size();
    for(int i=0;i<n;++i) {
        label[i]=s[i];
    }    
    rec(n);
}
int main() {
    
}