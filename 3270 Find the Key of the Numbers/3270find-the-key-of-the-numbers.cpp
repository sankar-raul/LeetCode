class Solution {
public:
    int generateKey(int num1, int num2, int num3) {
        int mini = 0, i = 4, a, b, c, base = 1;
        while (i--) {
            a = num1 % 10;
            b = num2 % 10;
            c = num3 % 10;
            int num = min({a, b, c});
            mini += num * base;
            num1 /= 10;
            num2 /= 10;
            num3 /= 10;
            base *= 10;
        }
        return mini;
    }
};