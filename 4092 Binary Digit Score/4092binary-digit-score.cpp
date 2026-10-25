class Solution {
public:
    int calculateScore(int a, int b) {
        int x = 0, y = 0;
        while (a > 0) {
            x += a % 2;
            a /= 2;
        }
        while (b > 0) {
            y += b % 2;
            b /= 2;
        }
        return x >= y ? x * y : y / x;
    }
};