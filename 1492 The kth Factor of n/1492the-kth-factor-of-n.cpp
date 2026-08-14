class Solution {
public:
    int kthFactor(int n, int k) {
        if (k == 1) {
            return 1;
        }
        int factor_idx = 1;
        for (int i = 2; i < n / 2 + 1; ++i) {
            if (n % i == 0) {
                if (++factor_idx == k) {
                    return i;
                }
            }
        }
        factor_idx++;
        if (factor_idx == k) {
            return n;
        }
        return -1;
    }
};