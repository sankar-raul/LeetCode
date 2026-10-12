class Solution {
public:
    int m, m2;
    unordered_set<string> p;
    void gen(string &str, int open, int close) {
        if (str.size() == m2) {
            if (open == close) {
                p.insert(str);
            }
            return;
        }
        if (open < m) {
            str.push_back('(');
            gen(str, open + 1, close);
            str.pop_back();
        }
        if (close < open) { 
            str.push_back(')');
            gen(str, open, close + 1);
            str.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        m = n;
        m2 = n * 2;
        string str;
        gen(str, 0, 0);
        return vector<string>(p.begin(), p.end());
    }
};