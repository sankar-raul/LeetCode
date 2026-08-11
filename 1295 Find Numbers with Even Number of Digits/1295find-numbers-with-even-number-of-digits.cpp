class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int count = 0;
        for (int num : nums) {
            string s = to_string(num);
            if (s.size() % 2 == 0) {
                count++;
            }
        }
        return count;
    }
};