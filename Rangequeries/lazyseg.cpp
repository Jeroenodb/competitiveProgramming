struct segtree {
    struct node {
        ll mx=-oo,lazy=0;
        int id=-1;
        node() {}
    };
    vector<node> seg;
    int n,ptwo;
    segtree(int nn) {
        n=nn,ptwo=1;
        while(ptwo<n) ptwo*=2;
        seg.resize(2*ptwo);
    }
    void puttag(int i, ll val) {
        auto& v = seg[i];
        v.mx+=val;
        v.lazy+=val;
    }

    void pull(int i) {
        auto& v = seg[i];
        v.mx = max(seg[i*2].mx, seg[i*2+1].mx);
        if(seg[i*2].mx>=seg[i*2+1].mx) v.id=seg[i*2].id;
        else v.id = seg[i*2+1].id;
    }
    void push(int i) { // TODO!
        puttag(i*2,seg[i].lazy);
        puttag(i*2+1,seg[i].lazy);
        seg[i].lazy=0;
    }
    ll get(int i, int l, int r, int ql, int qr) {
        if(qr<l or r<ql) return 0;
        if(ql<=l and r<=qr) {
            return seg[i].mx;
        }
        int mid = (l+r)/2;
        push(i);
        auto res = max(get(i*2,l,mid,ql,qr),get(i*2+1,mid+1,r,ql,qr)); // TODO
        pull(i);
        return res;
    }
    void set(int i, int l, int r, int ql, int qr, ll v) {
        if(qr<l or r<ql) return;
        if(ql<=l and r<=qr) {
            puttag(i,v); // correct?
            return;
        }
        int mid = (l+r)/2;
        push(i);
        set(i*2,l,mid,ql,qr,v),set(i*2+1,mid+1,r,ql,qr,v);
        pull(i);
    }
    void set(int l, int r, ll v) {
        set(1,0,ptwo-1,l,r,v);
    }
    node& operator[](int i) {return seg[i+ptwo];}
    void build() {
        for(int i=ptwo-1;i>=1;--i) {
            pull(i);
        }
    }
};
