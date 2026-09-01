class Solution {
public:
    bool isV(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }
    bool isVString(string s) {
        return isV(s[0]) && isV(s[s.size() - 1]);
    }
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        vector<int> psum(words.size());
        psum[0] = isVString(words[0]);
        for (int i = 1; i < words.size(); ++i) {
            psum[i] = psum[i-1] + isVString(words[i]);
        }
        vector<int> ans(queries.size());
        int idx = 0;
        for (auto& q : queries) {
            int right = psum[q[1]];
            int left = q[0] ? psum[q[0] - 1] : 0;
            ans[idx++] = right - left;
        }
        return ans;
    }
};