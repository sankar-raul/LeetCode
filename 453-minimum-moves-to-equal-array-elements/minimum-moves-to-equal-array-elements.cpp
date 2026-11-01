class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mini = 1e9;
        for (int &num : nums) {
            mini = min(num, mini);
        }
        int moves = 0;
        for (int &num : nums) {
            moves += num - mini;
        }
        return moves;
    }
};