class Solution {
public:
    bool checkGoodInteger(int n) {
        int sqSum = 0, digitSum = 0;
        while (n != 0) {
            int digit = n % 10;
            sqSum += digit * digit;
            digitSum += digit;
            n /= 10;
        }
        return sqSum - digitSum >= 50;
    }
};