class Solution {
public:
    void backtrace(int row, int n, vector<bool>& column_taken, vector<bool>& dia_1, vector<bool>& dia_2, int& total) {
        if (row == n) {
            total++;
            return;
        }
        for (int i = 0; i < n; ++i) {
            int d1 = row - i + n - 1;
            int d2 = row + i;
            if (column_taken[i] || dia_1[d1] || dia_2[d2]) continue;
            column_taken[i] = dia_1[d1] = dia_2[d2] = true;
            backtrace(row+1,n,column_taken,dia_1,dia_2,total);
            column_taken[i] = dia_1[d1] = dia_2[d2] = false;
        }
    }
    int totalNQueens(int n) {
        vector<bool> dia_1(n*2-1);
        vector<bool> dia_2(n*2-1);
        vector<bool> column_taken(n);
        int total = 0;
        backtrace(0,n,column_taken,dia_1,dia_2,total);
        return total;
    }
};