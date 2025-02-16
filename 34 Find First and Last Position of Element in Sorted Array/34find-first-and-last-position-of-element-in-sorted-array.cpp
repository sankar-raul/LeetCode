class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, mid;
        vector<int> res = {-1, -1};
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                low = mid;
                high = mid;
                while (low >= 0 && nums[low] == target) {
                    res[0] = low;
                    low--;
                }
                while (high < nums.size() && nums[high] == target) {
                    res[1] = high;
                    high++;
                }
                break;
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return res;
    }
};