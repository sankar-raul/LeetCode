class Solution {
public:
    void backtrace(int row, vector<string>& board, vector<bool>& column_taken, vector<bool>& dia_1, vector<bool>& dia_2, vector<vector<string>>& res) {
        int n = column_taken.size();
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
            backtrace(row + 1, board, column_taken, dia_1, dia_2, res);
            board[row][i] = '.';
            column_taken[i] = dia_1[d1] = dia_2[d2] = false;
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));
        vector<bool> dia_1(n*2-1);
        vector<bool> dia_2(n*2-1);
        vector<bool> column_taken(n);
        backtrace(0, board, column_taken, dia_1, dia_2, res);
        return res;
    }
};