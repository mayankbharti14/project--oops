#include <bits/stdc++.h>
using namespace std;

class Fenwick {
    int n;
    vector<int> bit;  // BIT array for prefix sums
public:
    Fenwick(int n) : n(n), bit(n, 0) {}
    // Add 'val' to element at index i
    void update(int i, int val) {
        for(; i < n; i = i | (i+1))
            bit[i] += val;
    }
    // Query prefix sum [0..i]
    int query(int i) {
        int s = 0;
        for(; i >= 0; i = (i & (i+1)) - 1)
            s += bit[i];
        return s;
    }
    // Query sum on [l..r]
    int rangeSum(int l, int r) {
        if(l > r) return 0;
        return query(r) - (l? query(l-1) : 0);
    }
};
