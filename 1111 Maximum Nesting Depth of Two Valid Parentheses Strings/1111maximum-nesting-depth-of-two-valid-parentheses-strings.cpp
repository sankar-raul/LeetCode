class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int d = 0;
        vector<int> ans;
        for (char ch : seq) {
            if (ch == '(') {
                ans.push_back(++d & 1);
            } else {
                ans.push_back(d-- & 1);
            }
        }
        return ans;
    }
};