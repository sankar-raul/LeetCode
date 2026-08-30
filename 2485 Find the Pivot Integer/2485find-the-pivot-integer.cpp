class Solution {
public:
    int pivotInteger(int n) {
        if (n == 1) return 1;
        int nsum = n * (n + 1) / 2;
        int from = n / 2;
        int prev = from * (from + 1) / 2;
        for (int i = from + 1; i < n; ++i) {
            int sum = prev + i;
            if (sum == nsum - sum + i) return i;
            prev = sum;
        }
        return -1;
    }
};