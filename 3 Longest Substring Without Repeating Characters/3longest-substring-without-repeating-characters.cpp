class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int lastSeen[128];
        fill(lastSeen, lastSeen + 128, -1);
        int max_size = 0;
        int left = 0;
        for (int i = 0; i < s.size(); ++i) {
            left = max(left, lastSeen[s[i]] + 1);
            lastSeen[s[i]] = i;
            max_size = max(max_size, i - left + 1);
        }
        return max_size;
    }
};