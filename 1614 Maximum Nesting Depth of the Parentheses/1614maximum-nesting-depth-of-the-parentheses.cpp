class Solution {
public:
    int maxDepth(string s) {
        int maxi = 0, stk = 0;
        for (char ch : s) {
            if (ch == '(') {
                stk++;
                maxi = max(stk, maxi);
            } else if (ch == ')') {
                stk--;
            }
        }
        return maxi;
    }
};