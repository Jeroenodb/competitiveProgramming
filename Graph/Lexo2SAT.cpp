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
struct SAT {
    // Variable i, 2*i+1 = p_i and 2*i is ~p_i
    int n;  // Number of nodes in the implication graph
    // n/2 is number of variables
    vector<vector<int>> adj, rev;
    vector<int> order,comp;
    bitset<mxN> visited;
    vector<bool> assignment;
    void OR(int a, int b) {
        adj[a^1].push_back(b);
        adj[b^1].push_back(a);
        rev[b].push_back(a^1);
        rev[a].push_back(b^1);
    }
    SAT (int k){
        n=k;
        adj.resize(n);
        rev.resize(n);
    }
    void dfs1(int at) {
        visited[at] = true;
        for (int to : adj[at]) {
            if (!visited[to]) dfs1(to);
        }
        order.push_back(at);
    }
    void dfs2(int at, int c) {
        visited[at] = true;
        comp[at]= c;
        for (int to : rev[at]) {
            if (!visited[to]) dfs2(to,c);
        }
    }
    bool solve() {
        assignment.resize(n/2);
        comp.resize(n);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) dfs1(i);
        }
        visited.reset();
        for (int i = n - 1; i >= 0; --i) {
            int at = order[i];
            if (!visited[at]) {
                dfs2(at,at);
            }
        }
        vvi cadj(n);
        vi deg(n);
        vi label(n,-oo),rank(n);
        for(int i=0;i<n;++i) {
            if(i%2==0) label[comp[i]]= max(label[comp[i]],-i);
            for(int to: adj[i]) if(comp[to]!=comp[i]){
                cadj[comp[i]].push_back(comp[to]);
                deg[comp[to]]++;
            }
        }
        priority_queue<pi> pq;
        for(int i=0;i<n;++i) if(comp[i]==i and deg[i]==0) {
            pq.push({label[i],i});
        }
        int id=0;
        while(!pq.empty()) {
            auto [lab,at]= pq.top(); pq.pop();
            rank[at]=id++;
            for(auto to : cadj[at]) {
                if(--deg[to]==0) pq.push({label[to],to});
            }
        }
        for(int i=0;i<n/2;++i) {
            if(comp[2*i] == comp[2*i+1]) return false;
            assignment[i] = rank[comp[i*2]] > rank[comp[i*2+1]];
        }
        return true;
    }
};
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
vector<bool> brute(int n, vector<pi> clauses) {
    n++;
    vector<bool> smart;
    {
        SAT sat(n*2);
        for(auto [a,b]: clauses) sat.OR(a,b);
        if(!sat.solve()) return {};
        smart = sat.assignment;
    }
    vector<bool> ans(n);
    for(int i=0;i<n;++i) {
        SAT sat(n*2);
        for(auto [a,b]: clauses) sat.OR(a,b);
        sat.OR(i*2,n*2-2);
        sat.OR(i*2,n*2-1);
        ans[i] =  !sat.solve();
        int var =ans[i]+2*i;
        clauses.push_back({var,n*2-1});
        clauses.push_back({var,n*2-2});
    }
    if(ans!=smart) {
        debug(ans);
        debug(smart);
    }
    return ans;
}

void gen() {
    int n = rnd(4,6);
    int m = rnd(7,10);
    vector<pi> clauses(m);
    for(auto& [a,b]: clauses) {
        a= rnd(0,2*n-1), b=rnd(0,2*n-1);
    }
    auto res = brute(n,clauses);
    cout << res << '\n';

}
int main() {
    while(true) gen();
}