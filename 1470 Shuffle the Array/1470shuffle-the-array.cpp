class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> suf(n*2);
        for (int i = 0; i < n; ++i) {
            suf[i+i] = nums[i];
            suf[i+i+1] = nums[n+i];
        }
        return suf;
    }
};