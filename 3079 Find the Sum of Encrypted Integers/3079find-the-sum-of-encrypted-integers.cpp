class Solution {
public:
    int sumOfEncryptedInt(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            int maxi = -1e9, digits = 0;
            while (num) {
                maxi = max(maxi, num % 10);
                digits++;
                num /= 10;
            }
            int n = 0;
            while (digits--) {
                n = n * 10 + maxi;
            }
            sum += n;
        }
        return sum;
    }
};