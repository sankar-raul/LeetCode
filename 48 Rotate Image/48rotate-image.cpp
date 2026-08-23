class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int k = matrix.size() - 1;
        for (int i = 0; i < matrix.size() / 2; ++i) {
            for (int j = i; j < k - i; ++j) {
                int val = matrix[i][j];
                matrix[i][j] = matrix[k-j][i];
                matrix[k - j][i] = matrix[k - i][k - j];
                matrix[k - i][k - j] = matrix[j][k - i];
                matrix[j][k - i] = val;
            }
        }
    }
};