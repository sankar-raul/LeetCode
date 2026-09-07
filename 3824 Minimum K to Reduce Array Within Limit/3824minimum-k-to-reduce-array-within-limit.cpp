class Solution {
public:
    double nonPositive(vector<int> &nums, int k) {
        double count = 0;
        int req;
        for (int num : nums) {
            req = (num / k) + (num % k ? 1 : 0);
            count += req;
        }
        return count;
    }
    
    int minimumK(vector<int>& nums) {
        int left = 1, right = 1e9;
        int mini = 1e9;
        double mid, count;
        while (left < right) {
            mid = left + (right - left) / 2;
            count = nonPositive(nums, mid);
            if (count <= mid * mid) {
                mini = min(mini, (int)mid);
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return mini;
    }
};