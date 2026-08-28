class Solution {
public:
    int maxDistinct(string s) {
        vector<int> freq(26);
        int count = 0;
        for (char ch : s) {
            if (!freq[ch - 'a']) {
                count++;
            }
            freq[ch - 'a']++;
        }
        return count;
    }
};