class Solution {
public:
   int countPrefixes(vector<string>& words, string s) {
        int count = 0;
        int length = words.size();
        while (length) {
            --length;
            int wl = words[length].length();
            if (wl <= s.length()) {
                bool temp = false;
                for (int i = 0; i < wl; i++) {
                   if (words[length][i] == s[i]) {
                        temp = true;
                        continue;
                   }
                   temp = false;
                   break;
                }
                count += temp ? 1 : 0;
            }
        }
        return count;
    }
};