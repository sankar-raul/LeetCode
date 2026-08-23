class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int count = 0;
        vector<char> arr(strs[0].size());
        for (int i = 0; i < strs.size(); ++i) {
            for (int j = 0; j < strs[i].size(); ++j) {
                if (arr[j] == '@') {
                    continue;
                }
                if (strs[i][j] < arr[j]) {
                    count++;
                    arr[j] = '@';
                } else {
                    arr[j] = strs[i][j];
                }
            }
        }
        return count;
    }
};