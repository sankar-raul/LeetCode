class Solution {
public:
    bool is_pal(int i, int j, string& s) {
        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }
    void backtrace(int idx, int n, string& s, vector<string>& parts, vector<vector<string>>& res) {
        if (idx == n) {
            res.push_back(parts);
            return;
        }
        string str;
        for (int i = idx; i < n; ++i) {
            str.push_back(s[i]);
            if (is_pal(idx, i, s)) {
                parts.push_back(str);
                backtrace(i+1, n, s, parts, res);
                parts.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> parts;
        backtrace(0, s.size(), s, parts, res);
        return res;
    }
};