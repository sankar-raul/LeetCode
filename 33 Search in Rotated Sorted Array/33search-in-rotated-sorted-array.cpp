class Solution {
public:
    int search(vector<int>& nums, int target) {
        int i = 0, j = nums.size() - 1;
        int mid;

        while (i <= j) {
            mid = i + (j - i) / 2;

            if (nums[mid] == target) return mid;

            if (nums[mid] >= nums[j]) {
                if (nums[mid] >= nums[i] && nums[i] <= target && target < nums[mid]) {
                    j = mid - 1;
                } else {
                    i = mid + 1;
                }
            } else {
                cout << mid << i << endl;

                if (nums[mid] < target && target <= nums[j]) {
                    i = mid + 1;
                } else {
                    j = mid - 1;
                }
            }

            // cout << mid << endl;
        }

        return -1;
    }
};