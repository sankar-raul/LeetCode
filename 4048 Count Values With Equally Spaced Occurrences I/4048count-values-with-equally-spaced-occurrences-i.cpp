class Solution {
public:
    int countSpecialIntegers(vector<int>& nums) {
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < nums.size(); ++i) {
            m[nums[i]].push_back(i);
        }
        int count = 0;
        for (auto& [num, arr] : m) {
            if (arr.size() != 3) {
                continue;
            } else {
                count += arr[1] - arr[0] == arr[2] - arr[1];
            }
        }
        return count;
    }
};