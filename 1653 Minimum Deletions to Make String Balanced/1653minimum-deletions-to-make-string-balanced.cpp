class Solution {
public:
    int minimumDeletions(string s) {
        vector<char> stack;
        int delCount = 0;
        for (char ch : s) {
            if (stack.size() && ch == 'a' && stack[stack.size() - 1] == 'b') {
                stack.pop_back();
                delCount++;
            } else {
                stack.push_back(ch);
            }
        }
        return delCount;
    }
};