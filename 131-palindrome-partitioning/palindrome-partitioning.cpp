class Solution {
public:
    vector<vector<int8_t>> dp;
    bool is_pal(int i, int j, string& s) {
        if (dp[i][j] != -1) return dp[i][j];
        int l = i, r = j;
        while (l < r) {
            if (s[l] != s[r]) {
                return dp[i][j] = 0;
            }
            l++, r--;
        }
        return dp[i][j] = 1;
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
        int n = s.size();
        dp.resize(n, vector<int8_t>(n, -1));
        vector<vector<string>> res;
        vector<string> parts;
        backtrace(0, s.size(), s, parts, res);
        return res;
    }
};