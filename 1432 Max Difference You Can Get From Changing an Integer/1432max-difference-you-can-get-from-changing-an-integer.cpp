class Solution {
public:
    int maxDiff(int num) {
        vector<int> digits;
        while (num) {
            digits.push_back(num % 10);
            num /= 10;
        }
        int a = 0, b = 0;
        int x = digits[digits.size() - 1];
        int x1 = x, x2 = x;
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != 9) {
                x1 = digits[i];
                break;
            }
        }
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != 1 && digits[i] != 0) {
                x2 = digits[i];
                break;
            }
        }
        for (int i = digits.size() - 1; i >= 0; --i) {
            a = (a*10) + (digits[i] == x1 ? 9 : digits[i]);
            b = (b*10) + (digits[i] == x2 ? x2 == x : digits[i]);
        }
        return abs(a-b);
    }
};