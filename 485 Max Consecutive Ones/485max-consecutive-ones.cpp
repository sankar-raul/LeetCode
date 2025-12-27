class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxOnes = nums[0];
        int cons = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            cons = nums[i-1] + nums[i] == 2 ? cons + 1 : nums[i];
            maxOnes = max(cons, maxOnes);
        }
        return max(cons, maxOnes);
    }
};