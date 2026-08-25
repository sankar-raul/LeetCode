class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> stack;
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; --i) {
            while (stack.size() && temperatures[stack[stack.size() - 1]] <= temperatures[i]) {
                stack.pop_back();
            }
            if (stack.size()) {
                ans[i] = stack[stack.size() - 1] - i;
            } else {
                ans[i] = 0;
            }
            stack.push_back(i);
        }
        return ans;
    }
};