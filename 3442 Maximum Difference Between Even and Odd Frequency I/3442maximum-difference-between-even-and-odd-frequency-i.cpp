class Solution {
public:
    int maxDifference(string s) {
        int max_odd = 0, min_even = 1e9;
        unordered_map<char, int> freq;
        for (char ch : s) {
            freq[ch]++;
        }
        for (auto &pair : freq) {
            int fr = pair.second;
            if (fr % 2 != 0) {
                max_odd = max(max_odd, fr);
            } else {
                min_even = min(min_even, fr);
            }
        }
        cout << max_odd << min_even << '\n';
        return max_odd - min_even;
    }
};