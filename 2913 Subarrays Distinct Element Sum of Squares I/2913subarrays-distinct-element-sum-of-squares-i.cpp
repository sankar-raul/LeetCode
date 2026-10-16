class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int res = 0;
        int seen[101];
        fill(begin(seen), end(seen), -1);
        for (int i = 0; i < nums.size(); ++i) {
            int d = 0;
            for (int j = i; j < nums.size(); ++j) {
                if (seen[nums[j]] != i) {
                    d++;
                    seen[nums[j]] = i;
                }
                res += d * d;
            }
        }
        return res;
    }
};