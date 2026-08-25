class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num : nums) freq[num]++;
        for (int i = k; i <= 100 + k; i += k) {
                if (!freq[i]) {
                    return i;
                }
        }
        return 0;
    }
};