#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Fenwick / Binary Indexed Tree for prefix sums (0-based public API).
 *
 * Internally uses a 1-based `bit` array and standard LSB operations:
 *  - update: idx += idx & -idx  (add LSB)
 *  - query:  idx -= idx & -idx  (drop LSB)
 *
 * Time: O(log n) for update/query, Space: O(n).
 */
class Fenwick {
    int n;                    ///< number of elements (public-visible size)
    vector<long long> bit;    ///< internal 1-based BIT array storing partial sums

public:
    /**
     * @brief Construct a Fenwick tree for n elements (all initialized to 0).
     * @param n Number of elements (logical size, public 0..n-1 indices).
     */
    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    /**
     * @brief Add a value to element at index i (public 0-based index).
     *
     * This performs an **increment** by val: a[i] += val.
     * For an assignment (set a[i] = x) first compute current value
     * via rangeSum(i,i) and call update(i, x - current).
     *
     * @param i Index to update (0-based).
     * @param val Value to add (can be negative to subtract).
     */
    void update(int i, long long val) {
        // convert to 1-based index and add LSB each iteration
        for (int idx = i + 1; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    /**
     * @brief Query prefix sum [0..i] (public 0-based index).
     * @param i Right index of prefix (0-based). If i < 0, returns 0.
     * @return Sum of a[0] + a[1] + ... + a[i]
     */
    long long query(int i) {
        if (i < 0) return 0;
        long long s = 0;
        // convert to 1-based and drop LSB each iteration
        for (int idx = i + 1; idx > 0; idx -= idx & -idx) {
            s += bit[idx];
        }
        return s;
    }

    /**
     * @brief Query sum on range [l..r] (inclusive).
     * @param l Left index (0-based).
     * @param r Right index (0-based).
     * @return Sum of a[l] + ... + a[r], or 0 if l > r.
     */
    long long rangeSum(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }

    /**
     * @brief Return the logical size (n).
     * @return number of elements.
     */
    int size() const { return n; }
};

/*
Example usage:

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    Fenwick fw(a.size());
    // build by adding each element (O(n log n))
    for (int i = 0; i < (int)a.size(); ++i) fw.update(i, a[i]);

    cout << fw.query(2) << "\n";       // prefix sum [0..2] = 6
    cout << fw.rangeSum(1, 3) << "\n"; // sum [1..3] = 2+3+4 = 9

    // point add: a[2] += 7  -> a[2] becomes 10
    fw.update(2, 7);
    cout << fw.rangeSum(1, 3) << "\n"; // now 2+10+4 = 16

    return 0;
}
*/

