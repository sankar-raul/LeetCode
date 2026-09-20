class Solution {
public:
    int reverseDegree(string s) {
        int rev = 0;
        for (int i = 0; i < s.size(); ++i) {
            int pos = 26 - (s[i] - 'a');
            rev += pos * (i + 1);
        }
        return rev;
    }
};