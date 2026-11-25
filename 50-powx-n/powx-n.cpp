class Solution {
public:
    double helper(double x, int n) {
        if (n == 1 || n == -1) {
            return x;
        }
        if (n <= 2 && n >= -2) {
            return n ? x * x : 1;
        }
        double sq = helper(x, n / 2);
        return sq * sq * ((n & 1) ? x : 1);
    } 
    double myPow(double x, int n) {
        double res = helper(x, n);
        if (n < 0) return 1.0 / res;
        return res;
    }
};