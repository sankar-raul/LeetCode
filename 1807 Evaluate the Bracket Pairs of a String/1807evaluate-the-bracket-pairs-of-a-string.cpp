class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> dict;
        for (vector<string>& var : knowledge) {
            dict[var[0]] = var[1];
        }
        bool isIn = false;
        string res, curr;
        for (char ch : s) {
            if (ch == '(') {
                isIn = true;
            } else if (ch == ')') {
                isIn = false;
                auto it = dict.find(curr);
                res += it != dict.end() ? it->second : "?";
                curr.clear();
            } else if (isIn) {
                curr += ch;
            } else {
                res += ch;
            }
        }
        return res;
    }
};