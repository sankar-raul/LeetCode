class Solution {
public:
    bool isMiddleElementUnique(vector<int>& nums) {
        int middle = nums[nums.size() / 2];
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            if (nums[i++] == middle || nums[j--] == middle) return false;
        }
        return true;
    }
};