struct LCA {
    int mn[20][mxN*2];
    int sz=0;
    void build() {
        for(int i=1;(1<<i)<=sz;++i) {
            for(int j=0;j + (1<<i)<sz;++j) {
                if(d[mn[i-1][j]] < d[mn[i-1][j+ (1<<i)/2]]) {
                    mn[i][j] = mn[i-1][j];
                } else mn[i][j] = mn[i-1][j+(1<<i)/2];
            }
        }
    }
    int query(int a, int b) {
        if(a==b) return a;
        int l = b-a;
        int i=0; while(1<<i <= l) ++i;
        int d1 = d[mn[i][a]], d2 = d[mn[i][b-1<<i]];
        return d1<d2?mn[i][a]:mn[i][b-1<<i];
    }
} lca;