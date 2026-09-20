class Solution {
public:
    int countSpecialIntegers(vector<int>& nums) {
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < nums.size(); ++i) {
            int num = nums[i];
            if (m[num].size() == 3) {
                int gap = m[num][1] - m[num][0]; // gap
                if (m[num][2] - m[num][1] == gap) {
                    m[num][0] = m[num][1];
                    m[num][1] = m[num][2];
                    m[num][2] = i;
                } else {
                    m[num].push_back(0);
                }
            } else if (m[num].size() < 3) {
                m[nums[i]].push_back(i); 
            }
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