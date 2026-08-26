class Solution {
public:
    char dv(int i, int j, string s) {
        int sum = 0;
        while (i < j) {
            sum += s[i++] - 'a';
        }
        return 'a' + (sum % 26);
    }
    string stringHash(string s, int k) {
        string ans;
        for (int i = 0; i < s.size(); i += k) {
            ans += dv(i, i + k, s);
        }
        return ans;
    }
};