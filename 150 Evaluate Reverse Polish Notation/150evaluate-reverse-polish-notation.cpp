class Solution {
public:
    int toint(string s) {
        int res = 0;
        int minus = s[0] == '-' ? -1 : 1;
        for (char ch : s) {
            if (ch == '-') continue;
            res = res * 10 + (ch - '0');
        }
        return res * minus;
    }
    int evalRPN(vector<string>& tokens) {
        vector<int> cal;
        int res = 0;
        for (string s : tokens) {
            if (s[0] >= '0' && s[0] <= '9' || s.size() > 1) {
                cal.push_back(toint(s));
            } else {
                int a = cal.back();
                cal.pop_back();
                int b = cal.back();
                cal.pop_back();
                switch (s[0]) {
                    case '+':
                        cal.push_back(b+a);
                        break;
                    case '-':
                        cal.push_back(b-a);
                        break;
                    case '*':
                        cal.push_back(b*a);
                        break;
                    default:
                        cal.push_back(b/a);
                }
            }
        }
        return cal.empty() ? toint(tokens[0]) : cal.back();
    }
};