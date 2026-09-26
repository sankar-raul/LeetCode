class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;
        s += s;
        int n = goal.size(), j = 0;
        for (int i = 0; i < n; ++i) {
            while (s[i+j] == goal[j]) {
                j++;
            }
            if (j >= n) return true;
            j = 0;
        }
        return false;
    }
};