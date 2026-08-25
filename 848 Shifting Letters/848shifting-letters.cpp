class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        for (int i = shifts.size() - 2; i >= 0; --i) {
            shifts[i] += shifts[i+1] % 26;
        }
        string ans;
        for (int i = 0; i < s.size(); ++i) {
            int gap = (s[i] - 'a') + shifts[i];
            ans += 'a' + (gap % 26);
        }
        return ans;
    }
};