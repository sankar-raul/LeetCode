class Solution {
public:
    bool canMakeSquare(vector<vector<char>>& grid) {
        bool isposible = false;
        for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int w = 0;
            for (int k = i; k < i+2; ++k) {
                for (int l = j; l < j + 2; ++l) {
                    if (grid[k][l] == 'W') {
                        w++;
                    }
                }
            }
            if (w >= 3 || w <= 1) {
                return true;
            }
        }
        }
        return false;
    }
};