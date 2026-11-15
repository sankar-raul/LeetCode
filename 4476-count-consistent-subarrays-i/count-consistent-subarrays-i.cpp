class Solution {
public:
    int countConsistent(vector<int>& nums) {
        int count = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            int _and = -1, mini = 101;
            for (int j = i; j < n; ++j) {
                mini = min(mini, nums[j]);
                _and &= nums[j];
                if (mini == _and) count++;
            }
        }
        return count;
    }
};