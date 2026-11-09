class Solution {
public:
    vector<vector<string>> findMismatchedSegments(string s1, string s2) {
        vector<vector<string>> res;
        string _1, _2;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) {
                _1.push_back(s1[i]);
                _2.push_back(s2[i]);
            } else {
                if (_1.size()) res.push_back({_1, _2});
                _1 = _2 = "";
            }
        }
        if (_1.size()) res.push_back({_1, _2});
        return res;
    }
};