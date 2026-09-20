class Solution {
public:
    vector<int> transformArray(vector<int>& nums) {
        int n = nums.size();
        int i = 0, j = n - 1;
        vector<int> ans(n);
        for (int num : nums) {
            if (num & 1) {
                ans[j--] = 1;
            } else {
                ans[i++] = 0;
            }
        }
        return ans;
    }
};