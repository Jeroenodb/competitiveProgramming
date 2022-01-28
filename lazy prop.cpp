#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <algorithm>
using namespace std;
#define all(x) begin(x),end(x)
typedef long long ll;
const int mxN = 1e5+1;
struct segtree {
    int n, ptwo;
    struct Node {
        // Change here the values you want to propagate, and store
        ll propa = 0, propb=0, sm = 0;
        // Propagation: Do to every element += a*x+b
        int l=-99,r=-99;
        Node () {}
        Node(int val, int i) {
            sm = val;
            l = r = i;
        }
        ll sum() {
            if(!propa and !propb) return sm;
            int sz = r-l+1;
            return sm + (ll)sz*propb + propa*sz*(sz-1)/2;
        }
    };
    vector<Node> d;

    void pull(int i) {
        // Recalculates all values stored in node from children
        assert(d[i].propa==0 and d[i].propb==0);
        Node& lc = d[2*i], &rc = d[2*i+1];
        d[i].sm = lc.sum() + rc.sum();
    }
    void push(int i) {
        // Pushes the propagation values down to the children
        Node& lc = d[2*i], &rc = d[2*i+1];
        if(d[i].propa==0 and d[i].propb==0)
            return;
        lc.propa+=d[i].propa;
        lc.propb+=d[i].propb; 
        rc.propa+=d[i].propa;
        rc.propb+=d[i].propb+d[i].propa*(rc.l-lc.l);
        d[i].propa = d[i].propb = 0;
    }
    segtree(int _n) {
        n = _n;
        ptwo= 1;
        while(ptwo<n) ptwo*=2;
        d.resize(2*ptwo);
        for(int i=ptwo; i<2*ptwo;++i) {
            d[i].l = d[i].r = i-ptwo;
        }
    }
    ll query(int l, int r, int i=1) {
        Node& c = d[i];
        if(c.l < l or r < c.r ) {
            ll res = 0;
            push(i);
            int mid = (c.r+c.l)/2;
            if(l<=mid) {
                res=query(l,min(mid,r),i*2);
            }
            if(r>mid) {
                res+=query(max(mid+1,l),r,i*2+1);
            }
            pull(i);
            return res;
        } else {
            return c.sum();
        }
    }
    void update(int l, int r, ll a, ll b, int i=1) {
        Node& c = d[i];
        if(c.l < l or r < c.r ) {
            push(i);
            int mid = (c.r+c.l)/2;
            if(l<=mid) {
                update(l,min(mid,r),a,b,i*2);
            }
            if(r>mid) {
                if(l>=mid+1) {
                    update(l,r,a,b,i*2+1);
                } else {
                    update(mid+1,r,a,b+a*(mid+1-l),i*2+1);
                }
                
            }
            pull(i);
        } else {
            c.propa+=a;
            c.propb+=b;
        }
    }
    void build() {
        for(int i=ptwo-1;i>0;--i) {
            pull(i);
            d[i].l = d[i*2].l; d[i].r = d[i*2+1].r;
        }
    }

};

int main() {
    
}