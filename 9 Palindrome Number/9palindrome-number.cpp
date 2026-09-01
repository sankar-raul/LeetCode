class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int tmp = x;
        long long mirror = 0;
        while (tmp != 0) {
            int digit = tmp % 10;
            mirror = mirror * 10 + digit;
            tmp /= 10;
        }
        return x == mirror;
    }
};