class Solution {
public:
    int smallestNumber(int n) {
        int res = 0;
        int i = 1;
        while (n != 0) {
            n /= 2;
            res += i;
            i += i;
        }
        return res;
    }
};