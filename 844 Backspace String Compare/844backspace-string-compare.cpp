class Solution {
public:
    bool backspaceCompare(string s, string t) {
        vector<char> s1;
        vector<char> s2;
        for (char ch : s) {
            if (ch == '#') {
                if (s1.size())
                    s1.pop_back();
            } else {
                s1.push_back(ch);
            }
        }
        for (char ch : t) {
            if (ch == '#') {
                if (s2.size())
                    s2.pop_back();
            } else {
                s2.push_back(ch);
            }
        }
        if (s1.size() != s2.size()) {
            return false;
        }
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) return false;
        }
        return true;
    }
};