class Solution {
public:
    vector<int> maxProductPair(vector<int>& nums, int target) {
        vector<int> ans = {-1, -1};
        unordered_map<int, int> m;
        int maxi = -1e9;
        for (int i = 0; i < nums.size(); ++i) {
            int idx = m[nums[i]];
            if (idx) {
                idx = idx == -1 ? 0 : idx;
                int mul = nums[idx] * nums[i];
                if (nums[idx] == nums[i]) {
                    //
                } else if (nums[idx] > nums[i]) {
                    if (mul >= maxi) {
                        ans[0] = idx;
                        ans[1] = i;
                        maxi = mul;
                    }
                } else {
                    if (mul >= maxi) {
                        ans[0] = i;
                        ans[1] = idx;
                        maxi = mul;
                    }
                }
            }
            m[target - nums[i]] = i ? i : -1;
        }
        return ans;
    }
};