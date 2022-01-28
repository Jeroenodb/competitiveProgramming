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
const int mxN = 3e4+4, oo = 1e9;
int edit(const string& s, const string& t) {
    int ans = 0;
    for(int i=0;i<(int)s.size();++i) {
        ans+=s[i]!=t[i];
    }
    return ans;
}

struct BKTree {
    struct node {
        string *s;
        vector<short> links;
        bool bad=false;
        node (string* ss) {
            s=ss;
            links.assign(s->size()+1,-1);
        }
    };
    vector<node> tree;
    BKTree(int n) { tree.reserve(n);    }

    int p = 0;
    void insert(string* s) {
        int nw = p;
        if(nw==0) {
            tree.push_back({s});
            p++;
            return;
        }
        int at = 0;
        while(true) {
            int e = edit(*tree[at].s,*s);
            if(e==0) {
                tree[at].bad=true;
                return;
            }
            if(tree[at].links[e]==-1) {
                tree[at].links[e] = nw;
                break;
            }
            at = tree[at].links[e];
        }
        tree.push_back({s});
        p++;
    }
    bool near(const string& s, int tol=2) { // searches with a tolerance
        stack<int> st; st.push(0);
        while(!st.empty()) {
            int at = st.top(); st.pop();
            int e = edit(*tree[at].s,s);
            if((e<=tol and e!=0) or (e==0 and tree[at].bad)) return true;
            for(int i=max(0,e-tol);i<=min((int)s.size(),e+tol);++i) {
                auto& to = tree[at].links[i];
                if(to!=-1)st.push(to);
            }
        }
        return false;
    }
};
void solve() {
    int n,k; cin >> n >> k;
    BKTree tree(n);
    struct word {
        string s;
        int i;
    };
    vector<word> words(n);
    
    for(int i=0;i<n;++i) {
        auto& w = words[i];
        cin >> w.s;
        w.i=i;
    }
    random_shuffle(all(words));
    for(auto& w : words) tree.insert(&w.s);
    vector<bool> ans(n);
    for(auto& w: words) {
        ans[w.i] = tree.near(w.s);
    }
    for(auto i: ans) {
        cout << i;
    } cout << '\n';
    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) {
        solve();
    }
}