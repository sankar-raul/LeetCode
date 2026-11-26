class Solution {
public:
    bool canAliceWin(int n) {
        int stone = 10;
        while (stone <= n) {
            n -= stone;
            stone--;
        }
        return stone & 1;
    }
};