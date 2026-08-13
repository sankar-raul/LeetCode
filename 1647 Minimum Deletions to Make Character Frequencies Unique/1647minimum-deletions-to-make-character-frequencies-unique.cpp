class Solution {
public:
    int minDeletions(string s) {
        unordered_map<char, int> freq;
        for (char ch : s) {
            freq[ch]++;
        }
        vector<pair<char, int>> v(freq.begin(), freq.end());
        sort(v.begin(), v.end(), [](auto& a, auto& b) {
            return a.second > b.second;
        });
        int total = 0;
        int prev_num = INT_MAX;
        for (auto& [ch, count] : v) {
            if (prev_num <= count) {
                if (prev_num == 0) {
                    total += count;
                    continue;
                }
                total += count - (prev_num - 1);
                --prev_num;
            } else {
                prev_num = count;
            }
        }
        return total;
    }
};