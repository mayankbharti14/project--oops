#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int n;
    vector<int> t;  // segment tree array
    // Build tree from array a in node v covering range [tl..tr]
    void build(vector<int>& a, int v, int tl, int tr) {
        if(tl == tr) {
            t[v] = a[tl]; 
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
        }
    }
    // Query sum in [l..r] from node v covering [tl..tr]
    int query(int v, int tl, int tr, int l, int r) {
        if(l > r) return 0;
        if(l == tl && r == tr) return t[v];
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm))
             + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
    // Update element at pos to new_val in node v covering [tl..tr]
    void update(int v, int tl, int tr, int pos, int new_val) {
        if(tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if(pos <= tm) update(v*2, tl, tm, pos, new_val);
            else update(v*2+1, tm+1, tr, pos, new_val);
            t[v] = t[v*2] + t[v*2+1];
        }
    }
public:
    SegmentTree(vector<int>& a) {
        n = a.size();
        t.assign(4*n, 0);
        build(a, 1, 0, n-1);
    }
    // Public method: get sum of elements in [l..r]
    int rangeSum(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
    // Public method: set a[pos] = val
    void pointUpdate(int pos, int val) {
        update(1, 0, n-1, pos, val);
    }
};
