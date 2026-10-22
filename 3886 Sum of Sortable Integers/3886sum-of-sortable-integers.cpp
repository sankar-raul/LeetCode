class Solution {
public:
    void cal_lps(int j, int k, vector<int> &nums, vector<int>& lps) {
        int i = 1, len = 0, n = k - j + 1;
        // vector<int> lps(n);
        lps[0] = 0;
        while (i < n) {
            if (nums[i+j] == nums[len+j]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
        // return lps;
    }
    bool can_sort(int i, int j, vector<int>& nums, vector<int>& sorted, vector<int>& lps) {
        if (j == i) {
            return nums[i] == sorted[j];
        };
        vector<int> bucket(sorted.begin() + i, sorted.begin() + j + 1);
        bucket.reserve(bucket.size() * 2);
        bucket.insert(bucket.end(), bucket.begin(), bucket.end());
        int k = 0, l = 0, n = bucket.size(), m = j - i + 1;
        cal_lps(i, j, nums, lps);
        // cout << "i, j " << i << " " << j << endl;
        // for (int num : bucket) {
        //     cout << num << endl;
        // }
        while (k < n) {
            if (bucket[k] == nums[i+l]) {
                k++;
                l++;
                if (l == m) return true;
            } else if (l) {
                l = lps[l-1];
            } else {
                k++;
            }
        }
        return false;
    }
    bool is_posible(int k, vector<int>& nums, vector<int>& sorted) {
        for (int i = 0; i < nums.size(); i += k) {
            vector<int> lps(k);
            if (!can_sort(i, i + k - 1, nums, sorted, lps)) {
                return false;
            }
        }
        return true;
    }
    int sortableIntegers(vector<int>& nums) {
        vector<int> sorted(nums.begin(), nums.end());
        sort(sorted.begin(), sorted.end());
        // vector<int> lps = cal_lps(nums);
        int n = nums.size();
        int loop = sqrt(n);
        vector<bool> mem(n + 1);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            if (n % i == 0) {
                int i2 = n / i;
                if (!mem[i]) {
                    mem[i] = true;
                    if (is_posible(i, nums, sorted)) {
                        res += i;
                        // cout << i << endl;
                    }
                }
                if (!mem[i2]) {
                    mem[i2] = true;
                    if (is_posible(i2, nums, sorted)) {
                        res += i2;
                        // cout << i2 << endl;
                    }
                }
            }
        }
        return res;
    }
};