class Solution {
public:
    int n = 0;
    void valid(int idx, int d, string& c_s, string& s, unordered_set<string>& ans) {
        if (s.size() == idx) {
            if (d == 0 && c_s.size() == n) {
                ans.insert(c_s);
            }
            return;
        }
        if (d < 0 || c_s.size() > n) return;
        if (s[idx] == '(' || s[idx] == ')') {
            c_s.push_back(s[idx]);
            valid(idx+1, d + (s[idx] == '(' ? 1 : -1), c_s, s, ans);
            c_s.pop_back();
            valid(idx+1, d, c_s, s, ans);
        } else {
            c_s.push_back(s[idx]);
            valid(idx + 1, d, c_s, s, ans);
            c_s.pop_back();
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> ans;
        int d = 0, rem = 0;
        for (char ch : s) {
            if (ch == '(') {
                d++;
            } else if (ch == ')') {
                d--;
                if (d < 0) {
                    d = 0;
                    rem++;
                }
            }
        }
        n = s.size() - (d + rem);
        string curr_str = "";
        valid(0, 0, curr_str, s, ans);
        return ans.empty() ? vector<string>{""} : vector<string>(ans.begin(), ans.end());
    }
};