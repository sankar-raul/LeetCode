class Solution {
public:
    bool checkString(string s) {
        bool isB = false;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'a') {
                if (isB) {
                    return false;
                }
            } else {
                isB = true;
            }
        }
        return true;
    }
};