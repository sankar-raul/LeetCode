class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int k = strs[0].size();
        for (int i = 1; i < strs.size(); ++i) {
            int m = strs[i].size() < k ? strs[i].size() : k;
            k = -1;
            for (int j = 0; j < m; ++j) {
                if (strs[i-1][j] == strs[i][j]) {
                    k = j+1;
                } else {
                    k = j;
                    break;
                }
                cout << k << endl;
            }
            if (k == -1) return "";
        }
        return k < 0 ? "" : strs[0].substr(0, k);
    }
};