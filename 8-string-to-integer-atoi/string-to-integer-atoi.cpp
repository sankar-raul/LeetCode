class Solution {
public:
    int myAtoi(string s) {
        long long res = 0;
        bool is_first = true, is_arith = false;
        int color = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                res = res * 10 + (s[i] - '0');
                if (res * color > INT_MAX) return INT_MAX;
                if (res * color < INT_MIN) return INT_MIN;
                is_first = false;
            } else if (s[i] == '+' || s[i] == '-') {
                if (!is_first || is_arith) {
                    break;
                }
                color = s[i] == '-' ? -1 : 1;
                is_arith = true;
            } else if (s[i] == ' ') {
                if (!is_first || is_arith) break;
            } else {
                break;
            }
        }
        return res * color;
    }
};