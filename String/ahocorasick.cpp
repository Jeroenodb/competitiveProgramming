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
typedef unsigned char uchar;

const int sigma = 256, mask = sigma-1, cross = 64;
struct smallmap {
    int* ar = NULL;
    unsigned char sz=0, cap = 0;
    int get(uchar to) {
        if(cap==mask) {
            return ar[to];
        }
        for(int i=0;i<sz;++i) {
            if((ar[i]&mask) == to) {
                return ar[i]>>8;
            }
        }
        return 0;
    }
    void add(uchar to, int id) {
        if(cap!=mask) {
            if(sz==cap) {
                if(cap==cross) {
                    // rebuild whole unordered array, to a normal trie
                    cap = mask;
                    int* cur = new int[sigma];
                    fill(cur,cur+sigma,0);
                    int p[cross];
                    copy(ar,ar+cross,p);
                    delete[] ar;
                    ar = cur;
                    sz=0;
                    for(int i=0;i<cross;++i) {
                        add(p[i]&mask,  p[i]>>8);
                    }
                    add(to,id);
                    return;
                } else {
                    cap*=2;
                    if(!cap) cap = 1;
                    int* cur = new int[cap];
                    if(ar) {
                        copy(ar, ar+cap/2, cur);
                        delete[] ar;
                    }
                    ar=cur;
                }
            }
            ar[sz++] = int(to)|(id<<8);
         } else {
            sz++;
            ar[to] = id;
        }
    }
};

const int mxN = 1e5+1, oo = 1e9;

smallmap trie[mxN]; int p=2;
int fail[mxN];
int longest[mxN];
void addword(const uchar* c) {
    const uchar* beg = c;
    int at = 1;
    while(*c) {
        int tmp;
        if(!(tmp = trie[at].get(*c))) {
            trie[at].add(*c, p);
            at = p++;
        } else {
            at = tmp;
        }
        c++;
    }
    longest[at] = c-beg;
}
queue<int> q;
void makefail(int at, uchar c, int to) {
    while(true) {
        at = fail[at];
        int ans = trie[at].get(c);
        if(ans) {
            fail[to] = ans;
            longest[to] = max(longest[ans], longest[to]);
            break;
        }
    }
    q.push(to);
}
void update(int at) {
    if(trie[at].cap==mask) {
        for(int d=1;d<sigma;++d) {
            int to = trie[at].get(d);
            if(to) {
                makefail(at,d,to);
            }
        }
    } else {
        for(int i=0;i<trie[at].sz;++i) {
            makefail(at,trie[at].ar[i]&mask, trie[at].ar[i]>>8);
        }
    }
}
void construct() {
    // construct fail array
    bool doupdate[sigma]={};
    fail[1] = 1;
    int tmp;
    for(int c = 1;c<sigma;++c) {
        if(!(tmp = trie[1].get(c))) {
            trie[1].add(c,1);
        } else {
            doupdate[c] = true;
            fail[tmp]=1;
        }
    }
    for(int c = 1;c<sigma;++c) {
        if(doupdate[c]) {
            tmp = trie[1].get(c);
            fail[tmp] = 1;
            update(tmp);
        }
    }
    while(!q.empty()) {
        update(q.front()); q.pop();
    }
}
int transition(int at, uchar c) {
    int tmp;
    while( (tmp = trie[at].get(c))==0) {
        at = fail[at];
    } 
    return tmp;
}
uchar buffer[10005];
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int n; cin >> n; getchar();
    bool emptyword = false;
    sizeof(trie);
    for(int i=0;i<n;++i) {
        int j = 0;
        while((buffer[j++] = getchar())!='\n') {

        }
        buffer[--j] = 0;
        if(j==0) {
            emptyword = true;
        }else addword(buffer);
    }
    construct();
    int m; cin >> m; getchar();
    pi ans = emptyword?pi{1,1}:pi{oo,oo};
    for(int line=1;line<=m;++line) {
        int at = 1;
        uchar c;
        int i=0;
        while((c=getchar())!='\n') {
            at = transition(at,c);
            if(longest[at]!=0) {
                ans = min(ans,{line, i+2-longest[at]});
            }
            ++i;
        }
    }
    if(ans!= pi{oo,oo}) {
        cout << ans.first << ' ' << ans.second << '\n';
    } else cout << "Passed\n";
}