class Solution {
public:
    bool checkOnesSegment(string s) {
        bool seen = false;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == '0') {
                seen = true;
            } else {
                if (seen) return false;
            }

        }
        return true;
    }
};