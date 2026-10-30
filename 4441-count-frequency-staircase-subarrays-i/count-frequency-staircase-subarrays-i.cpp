class Solution {
public:
    int countStaircase(vector<int>& nums) {
        int n = nums.size();
        int total = n;

        for (int i = 0; i < n; ++i) {
            unordered_map<int, int> freq;
            vector<int> order;

            int val = 0;

            for (int j = i; j < n; ++j) {
                int x = nums[j];

                if (!freq[x]++) {
                    order.push_back(x);
                    val += (1 ^ order.size());
                } else {
                    int rank = find(order.begin(), order.end(), x) - order.begin() + 1;
                    int oldFreq = freq[x] - 1;

                    val -= (oldFreq ^ rank);
                    val += (freq[x] ^ rank);
                }

                if (freq.size() >= 2 && val == 0) {
                    total++;
                }
            }
        }

        return total;
    }
};