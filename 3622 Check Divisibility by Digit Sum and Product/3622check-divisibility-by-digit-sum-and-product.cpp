class Solution {
public:
    bool checkDivisibility(int n) {
        int digitSum = 0, digitProduct = 1;
        int tmp = n;
        while (n != 0) {
            int digit = n % 10;
            digitSum += digit;
            digitProduct *= digit;
            n /= 10;
        }
        int sum = digitSum + digitProduct;
        return !(tmp % sum);
    }
};