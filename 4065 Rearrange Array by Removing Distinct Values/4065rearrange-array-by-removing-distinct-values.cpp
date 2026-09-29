class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> res;
        sort(nums.begin(), nums.end());
        while (res.size() != nums.size()) {
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] > 0 && (i + 1 >= nums.size() || nums[i] != nums[i+1])) {
                    res.push_back(nums[i]);
                    nums[i] = -nums[i];
                }
            }
        }
        return res;
    }
};