class Solution {
public:
    int mirrorDistance(int n) {
        string mirror = "";
        int tmp = n;
        while (n != 0) {
            mirror += '0' + n % 10;
            n /= 10;
        }
        return abs(tmp - stoi(mirror));
    }
};