class Solution {
public:
    int countDigits(int num) {
        int count = 0;
        int tmp = num;
        while (tmp != 0) {
            int digit = tmp % 10;
            count += num % digit == 0;
            tmp /= 10;
        }
        return count;
    }
};