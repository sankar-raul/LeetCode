class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        int min_idx = 0, max_idx = 0, n = nums.size();
        for (int i = 1; i < n; ++i) {
            min_idx = nums[min_idx] < nums[i] ? min_idx : i;
            max_idx = nums[max_idx] > nums[i] ? max_idx : i;
        }
        int left = min(min_idx, max_idx);
        int right = max(min_idx, max_idx);
        int min_del = min(right + 1, n - left);
        return min(min_del, (left - 0 + 1) + (n - right));
    }
};