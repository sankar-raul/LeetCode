class Solution {
public:
    void backtrace(int row, int n, vector<bool>& column_taken, vector<string>& board, vector<bool>& dia_1, vector<bool>& dia_2, vector<vector<string>>& res) {
        if (row == n) {
            res.push_back(board);
            return;
        }
        for (int i = 0; i < n; ++i) {
            int d1 = row - i + n - 1;
            int d2 = row + i;
            if (column_taken[i] || dia_1[d1] || dia_2[d2]) continue;
            column_taken[i] = dia_1[d1] = dia_2[d2] = true;
            board[row][i] = 'Q';
            backtrace(row+1, n, column_taken, board, dia_1, dia_2, res);
            board[row][i] = '.';
            column_taken[i] = dia_1[d1] = dia_2[d2] = false;
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<bool> column_taken(n);
        vector<string> board(n, string(n, '.'));
        vector<bool> dia_1(n*2-1);
        vector<bool> dia_2(n*2-1);
        backtrace(0, n, column_taken, board, dia_1, dia_2, res);
        return res;
    }
};