class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;
        sort(nums.begin(), nums.end());
        int median = n & 1 ? nums[n / 2] : nums[n/2-1] + (nums[n/2] - nums[n/2-1]) / 2;
        int moves = 0;
        for (int &num : nums) {
            moves += abs(num - median);
        }
        return moves;
    }
};