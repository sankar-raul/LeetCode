class Solution {
public:
    bool check(vector<int>& nums) {
        int drops = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] >= nums[i-1]) {
                continue;
            } else {
                drops++;
            }
        }
        return drops == 0 || drops <= 1 && nums[0] >= nums[nums.size() - 1];
    }
};