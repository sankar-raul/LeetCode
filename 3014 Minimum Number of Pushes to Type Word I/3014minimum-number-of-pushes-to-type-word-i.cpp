class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int press = 0;
        int i = 1;
        while (n > 0) {
            int num = min(n, 8);
            press += num * i;
            n -= num;
            i++;
        }
        return press;
    }
};