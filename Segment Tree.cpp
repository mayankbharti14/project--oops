#include <bits/stdc++.h>
using namespace std;

/**
 * @class SegmentTree
 * @brief Simple recursive segment tree for range-sum queries and point updates.
 *
 * This holds an integer array internally (stored as sums in `t`) and supports:
 *  - building from an input vector,
 *  - querying the sum on any range [l..r], and
 *  - updating a single element (point assignment).
 *
 * Notes:
 *  - The public API expects 0-based indices for the input array (0..n-1).
 *  - Internally the tree is stored in a 1-based-style array `t` (root at index 1).
 *  - This implementation uses O(n) build time and O(log n) per query/update.
 */
class SegmentTree {
    int n;               ///< logical size (number of elements)
    vector<int> t;       ///< segment tree array (stores segment sums)

    /**
     * @brief Build the segment tree from array `a`.
     *
     * Recursively fills `t[v]` so that node `v` stores the sum of a[tl..tr].
     *
     * @param a Input array (0-based, size == n).
     * @param v Current tree node index in `t` (start with 1 for root).
     * @param tl Left bound of the segment covered by node v (inclusive).
     * @param tr Right bound of the segment covered by node v (inclusive).
     *
     * @pre 0 <= tl <= tr < n
     */
    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    /**
     * @brief Query the sum on interval [l..r] using node v covering [tl..tr].
     *
     * Recursively descends and returns the sum a[l] + ... + a[r].
     *
     * @param v Current node index in `t`.
     * @param tl Left bound of node v's segment.
     * @param tr Right bound of node v's segment.
     * @param l Left bound of the requested query (inclusive).
     * @param r Right bound of the requested query (inclusive).
     * @return Sum of elements on [l..r]. Returns 0 if l > r.
     *
     * @pre 0 <= tl <= tr < n, and tl <= r && l <= tr for meaningful calls.
     */
    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return t[v];
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm))
             + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    /**
     * @brief Update the element at position `pos` to `new_val`.
     *
     * Descends to the leaf for `pos`, sets its value, and recomputes ancestor sums.
     *
     * @param v Current node index in `t`.
     * @param tl Left bound of node v's segment.
     * @param tr Right bound of node v's segment.
     * @param pos Index in the original array to update.
     * @param new_val New value to assign to a[pos].
     *
     * @pre 0 <= pos < n
     */
    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v*2, tl, tm, pos, new_val);
            else update(v*2+1, tm+1, tr, pos, new_val);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

public:
    /**
     * @brief Construct a segment tree from an integer vector.
     *
     * Initializes internal storage and builds the tree (O(n)).
     *
     * @param a Input array (0-based). The tree will represent sums over this array.
     */
    SegmentTree(vector<int>& a) {
        n = static_cast<int>(a.size());
        t.assign(4 * max(1, n), 0); // safe sizing; handle n==0 gracefully
        if (n > 0) build(a, 1, 0, n-1);
    }

    /**
     * @brief Get the sum of elements on the inclusive range [l..r].
     *
     * @param l Left index (0-based).
     * @param r Right index (0-based).
     * @return Sum a[l] + ... + a[r].
     *
     * @pre 0 <= l <= r < n
     * @note Runs in O(log n) time.
     */
    int rangeSum(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

    /**
     * @brief Set a[pos] = val (point assignment).
     *
     * @param pos Index to update (0-based).
     * @param val New value to store at position pos.
     *
     * @pre 0 <= pos < n
     * @note Runs in O(log n) time.
     */
    void pointUpdate(int pos, int val) {
        update(1, 0, n-1, pos, val);
    }
};
