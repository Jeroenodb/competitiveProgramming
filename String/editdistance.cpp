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
const int mxN = 1.5e5, oo = 1e9;
int edit(const string& s, const string& t) {
    if(s==t) return 0;
    int m = t.size();
    vi dp(m+1);
    iota(all(dp),0);
    for(int i=1;i<=s.size();++i) {
        int prev = dp[0];
        for(int j=0;j<=m;++j) {
            // edit distance = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]+s[i]!=t[i])
            int cur = dp[j]++;
            if(j and i) dp[j]=min(dp[j],prev+(s[i-1]!=t[j-1]));
            if(j) dp[j]=min(dp[j-1]+1,dp[j]);
            prev = cur;
        }
    }
    return dp[m];
}

struct BKTree {
    struct node {
        string s;
        map<int,int> links;
        node (const string& ss) {
            s=ss;
        }
    };
    vector<node> tree;
    BKTree() {
        tree.reserve(mxN);
    }

    int p = 0;
    void insert(string s) {
        int nw = p;
        if(nw==0) {
            tree.push_back({s});
            p++;
            return;
        }
        int at = 0;
        while(true) {
            int e = edit(tree[at].s,s);
            if(e==0) return;
            auto pp = tree[at].links.insert({e,nw});
            if(pp.second) break;
            at = pp.first->second;
        }
        tree.push_back({s});
        p++;
    }
    vector<pair<int,string>> near(string s, int tol=2) { // searches with a tolerance
        vector<pair<int,string>> res;
        stack<int> st; st.push(0);
        while(!st.empty()) {
            int at = st.top(); st.pop();
            int e = edit(tree[at].s,s);
            if(e<=tol) res.emplace_back(e,tree[at].s);
            auto i1 = tree[at].links.lower_bound(e-tol), i2 = tree[at].links.upper_bound(e+tol);
            while(i1!=i2) {
                st.push(i1->second);
                i1++;
            }
        }
        sort(all(res));
        return res;
    }
};
int main() {
    BKTree tree;
    ifstream fin("wordlist.txt");
    string word;
    int rep =0;
    while(fin >> word) {
        if(rep++%10000==0) cout << rep << ' ';
        tree.insert(word);
    }
    debug("done");
    while(true) {
        cin >> word;
        auto ans = tree.near(word,2);
        for(auto [dist,w]:ans) cout << w << ' ';
        cout << '\n';
    }
    
}