class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = min(n, 2);

        for (int i = 0; i < n; i++) {
            for (int j = i + 2; j < n; j++) {

                bool valid = true;

                for (int k = i; k <= j && valid; k++) {
                    for (int l = k + 1; l <= j; l++) {
                        if (gcd(nums[k], nums[l]) != 1) {
                            valid = false;
                            break;
                        }
                    }
                }

                if (!valid) break;

                ans = max(ans, j - i + 1);
            }
        }

        return ans;
    }
};