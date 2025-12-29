// This implementation uses 0-based input vector.
struct SegmentTree {
    int n;
    vector<ll> sumTree;
    vector<ll> maxTree;
    SegmentTree() : n(0) {}
    SegmentTree(int n_) { init(n_); }
    void init(int n_){
        n = n_;
        sumTree.assign(4*n, 0);
        maxTree.assign(4*n, LLONG_MIN);
    }
    // build from array a (0-based)
    void build_sum_max(const vector<ll>& a, int v, int tl, int tr){
        if(tl == tr){
            sumTree[v] = a[tl];
            maxTree[v] = a[tl];
        } else {
            int tm = (tl + tr) >> 1;
            build_sum_max(a, v<<1, tl, tm);
            build_sum_max(a, v<<1|1, tm+1, tr);
            sumTree[v] = sumTree[v<<1] + sumTree[v<<1|1];
            maxTree[v] = max(maxTree[v<<1], maxTree[v<<1|1]);
        }
    }
    // query sum on [l..r]
    ll query_sum(int v, int tl, int tr, int l, int r){
        if(l > r) return 0;
        if(l == tl && r == tr) return sumTree[v];
        int tm = (tl + tr) >> 1;
        return query_sum(v<<1, tl, tm, l, min(r,tm))
             + query_sum(v<<1|1, tm+1, tr, max(l,tm+1), r);
    }
    // query max on [l..r]
    ll query_max(int v, int tl, int tr, int l, int r){
        if(l > r) return LLONG_MIN;
        if(l == tl && r == tr) return maxTree[v];
        int tm = (tl + tr) >> 1;
        return max(query_max(v<<1, tl, tm, l, min(r,tm)),
                   query_max(v<<1|1, tm+1, tr, max(l,tm+1), r));
    }
    // point update: set pos to val
    void update_point(int v, int tl, int tr, int pos, ll val){
        if(tl == tr){
            sumTree[v] = val;
            maxTree[v] = val;
        } else {
            int tm = (tl + tr) >> 1;
            if(pos <= tm) update_point(v<<1, tl, tm, pos, val);
            else update_point(v<<1|1, tm+1, tr, pos, val);
            sumTree[v] = sumTree[v<<1] + sumTree[v<<1|1];
            maxTree[v] = max(maxTree[v<<1], maxTree[v<<1|1]);
        }
    }
};