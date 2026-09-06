class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hmap;
        for (int i = 0; i < nums.size(); ++i) {
            if (hmap[nums[i]]) return {hmap[nums[i]] - 1, i};
            hmap[target-nums[i]] = i+1;
        }
        return {};
    }
};