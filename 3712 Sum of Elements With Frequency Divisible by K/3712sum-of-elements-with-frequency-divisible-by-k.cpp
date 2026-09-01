class Solution {
public:
    int sumDivisibleByK(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int sum = 0;
        for (int num : nums) freq[num]++;
        for (auto& pair : freq) {
            if (pair.second % k == 0) {
                sum += pair.first * pair.second;
            }
        }
        return sum;
    }
};