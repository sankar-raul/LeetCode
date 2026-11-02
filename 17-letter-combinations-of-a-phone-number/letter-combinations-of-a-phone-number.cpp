class Solution {
public:
    string keys[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    void comb(string &digits, int idx, vector<string>& res, string &curr_str) {
        if (idx == digits.size()) {
            res.push_back(curr_str);
            return;
        }
        int key = digits[idx] - '0';
        string &letters = keys[key-2];
        for (int i = 0; i < letters.size(); ++i) {
            curr_str.push_back(letters[i]);
            comb(digits, idx+1, res, curr_str);
            curr_str.pop_back();
        }
        return;
    }
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        string curr_str = "";
        comb(digits, 0, res, curr_str);
        return res;
    }
};