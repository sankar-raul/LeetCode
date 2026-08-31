class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        vector<int> ans;
        for (int num : nums) {
            int idx = num == -777 ? 0 : abs(num);
            if (nums[idx] < 0) {
                ans.push_back(idx);
            } else {
                nums[idx] = nums[idx] ? -nums[idx] : -777; // -1 for 0
            }
        }
        return ans;
    }
};