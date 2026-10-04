class Solution {
public:
    int longestValidParentheses(string s) {
        int i = 0, j = s.size() - 1, n = s.size();
        int open[] = {0, 0}, closed[] = {0, 0};
        int maxi = 0;
        while (i < n) {
            open[0] += s[i] == '(';
            open[1] += s[j] == '(';
            closed[0] += s[i++] == ')';
            closed[1] += s[j--] == ')';
            if (open[0] == closed[0]) {
                maxi = max(maxi, open[0] + closed[0]);
            } else if (closed[0] > open[0]) {
                closed[0] = open[0] = 0;
            }
            if (open[1] == closed[1]) {
                maxi = max(maxi, open[1] + closed[1]);
            } else if (open[1] > closed[1]) {
                closed[1] = open[1] = 0;
            }
        }
        return maxi;
    }
};