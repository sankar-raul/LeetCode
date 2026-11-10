class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        vector<int> res;
        sort(nums.begin(), nums.end(), [](const int& a, const int& b){
            return a > b;
        });
        int sum = 0, res_sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
        }
        int i = 0;
        while (res_sum <= sum - res_sum) {
            res_sum += nums[i];
            res.push_back(nums[i++]);
        }
        return res;
    }
};