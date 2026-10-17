class Solution {
public:
    int digitSum(int num) {
        int sum = 0;
        while (num) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
    int minSwaps(vector<int>& nums) {
        unordered_map<int, int> m;
        int n = nums.size();
        vector<int> after_sort;
        for (int i = 0; i < n; ++i) {
            m[nums[i]] = i;
            after_sort.push_back(nums[i]);
        }
        sort(after_sort.begin(), after_sort.end(), [&](const int& a, const int& b) {
            int s1 = digitSum(a);
            int s2 = digitSum(b);
            bool isA = true;
            if (s1 == s2) {
                isA = a < b;
            } else {
                isA = s1 < s2;
            }
            return isA;
        });
        int swap_count = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] != after_sort[i]) {
                int idx = m[after_sort[i]];
                m[nums[i]] = idx;
                m[nums[idx]] = i;
                swap(nums[i], nums[idx]);
                swap_count++;
            }
        }
        return swap_count;
    }
};