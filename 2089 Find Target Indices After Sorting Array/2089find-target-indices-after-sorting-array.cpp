class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> res;
        int count = 0, start_idx = 0;
        for (int num : nums) {
            if (num == target) count++;
            if (num < target) start_idx++;
        }
        if (!count) return res;
        for (int i = 0; i < count; ++i) {
            res.push_back(start_idx + i);
        }
        return res;
    }
};