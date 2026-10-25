class Solution {
public:
    pair<int, int> max_pos(int num) {
        vector<int> digits;
        int n = num;
        while (num) {
            digits.push_back(num % 10);
            num /= 10;
        }
        sort(digits.begin(), digits.end());
        for (int i = digits.size() - 1; i >= 0; --i) {
            num = num * 10 + digits[i];
        }
        return {abs(num - n), num};
    }
    long long maximizeSum(vector<int>& nums, int k) {
        struct Item {
            int num;
            int gap;
            int maximum;
        };

        vector<Item> items;
        items.reserve(nums.size());

        for (int num : nums) {
            auto [gap, maximum] = max_pos(num);
            items.push_back({num, gap, maximum});
        }

        sort(items.begin(), items.end(),
             [](const Item& a, const Item& b) {
                 return a.gap > b.gap;
        });
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += items[i].maximum;
        }
        for (int i = k; i < nums.size(); ++i) {
            sum += items[i].num;
        }
        return sum;
    }
};