class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mini = 1e9, sum = 0;
        for (int &num : nums) {
            sum += num;
            mini = min(num, mini);
        }
        return sum - (mini * nums.size());
    }
};