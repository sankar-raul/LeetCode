class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans = 0, freq = 0;
        for (int num : nums) {
            if (!freq) {
                ans = num;
            }
            freq += num == ans ? 1 : -1;
        }
        return ans;
    }
};