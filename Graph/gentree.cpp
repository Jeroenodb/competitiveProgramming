#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x),end(x)
namespace {
template<class T1, class T2> void prin(const pair<T1,T2>& x);
template<class T> void prin(const vector<T>& x);
template<class T> void prin(const T& x) {cout << x;}
template<class H, class... T> void prin(const H& h, const T&... t) {prin(h); prin(' '); prin(t...); }
template<class T1, class T2> void prin(const pair<T1,T2>& x) {prin(x.first,' ',x.second);}
template<class T> void prin(const vector<T>& x) {for(int i=0;i<(int)x.size();++i) prin(i==0?"":" ",x[i]);}
template<class... T> void print(const T&... t) {prin(t..., "\n"); }
#define debug(x) cout << #x << ": "; print(x)
}
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
int main() {
    int n = 1e3;
    print(1);
    print(n);
    for(int i=2;i<=n;++i) {
        int to = 1 + (rand()%(i-1));
        if(rand()%2==0) print(to,i);
        else print(i,to);
    }
    // for(int i=0;i<n*2;++i) {
    //     int a = 1+rand()%n,  b =  1+rand()%n;
    //     if(rand()&2) {
    //         print('Q', a,b);
    //     } else print('C',max(1,a-1),b);
    // }
    // print("DONE");
}