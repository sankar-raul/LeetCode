class Solution {
public:
    int maximumLengthSubstring(string s) {
        unordered_map<char, int> freq;
        int j = 0;
        int max_sub = 0;
        for (int i = 0; i < s.size(); ++i) {
            char ch = s[i];
            if (freq[ch] >= 2) {
                while (s[j++] != ch) {
                    freq[s[j-1]]--;
                }
            } else {
                freq[ch]++;
                max_sub = max(max_sub, i - j);
            }
        }
        return max_sub + 1;
    }
};