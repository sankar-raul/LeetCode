class Solution {
public:
    long long sumAndMultiply(int n) {
        long long sum = 0;
        string x = "";
        if (n == 0) return 0;
        while (n != 0) {
            long long rem = n % 10;
            if (rem) {
                sum += rem;
                x += rem + '0';
            }
            n /= 10;
        }
        reverse(x.begin(), x.end());
        return sum * stod(x);
    }
};