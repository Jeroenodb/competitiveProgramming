#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <algorithm>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
const int mxN = 2e5+1;

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
        int id = n;
        visited.reset();
        for (int i = n - 1; i >= 0; --i) {
            int at = order[i];
            if (!visited[at]) {
                dfs2(at,--id);
            }
        }

        for(int i=0;i<n/2;++i) {
            if(comp[2*i] == comp[2*i+1]) return false;
            assignment[i] = comp[i*2] > comp[i*2+1];
        }
        return true;
    }
};

int main() {
    int n,m; cin >> n >> m;
    SAT sat(m*2);
    for(int i=0;i<n;++i) {
        char c1, c2;
        int a,b; cin >> c1 >> a >> c2 >> b;
        --a;--b;
        sat.OR((c1=='+')+2*a,(c2=='+')+2*b);
    }
    if(!sat.solve()) {
        cout << "IMPOSSIBLE\n";
    } else {
        for(bool i : sat.assignment) cout << (i?"+ ":"- ");
    }
}