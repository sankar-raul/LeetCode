class Solution {
public:
    int alternateDigitSum(int n) {
        int nums[10];
        int i = 0;
        while (n) {
            nums[i++] = n % 10;
            n /= 10;
        }
        int sum = 0;
        bool isPlus = true;
        while (i--) {
            sum += isPlus ? nums[i] : -nums[i];
            isPlus = !isPlus;
        }
        return sum;
    }
};