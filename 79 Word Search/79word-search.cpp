class Solution {
public:
    int m, n;
    bool dfs(int i, int j, vector<vector<char>>& board, string& word, int& pos) {
        if (pos + 1 == word.size()) {
            return board[i][j] == word[pos];
        }
        bool posible = false;
        char prev = board[i][j];
        board[i][j] = '\0';
        if (j && board[i][j-1] == word[pos+1] && board[i][j-1] != '\0') {
            pos++;
            posible |= dfs(i, j - 1, board, word, pos);
            pos--;
        }
        if (j + 1 < n && board[i][j+1] == word[pos+1] && board[i][j+1] != '\0') {
            pos++;
            posible |= dfs(i, j + 1, board, word, pos);
            pos--;
        }
        if (i && board[i-1][j] == word[pos+1] && board[i-1][j] != '\0') {
            pos++;
            posible |= dfs(i-1, j, board, word, pos);
            pos--;
        }
        if (i + 1 < m && board[i+1][j] == word[pos+1] && board[i+1][j] != '\0') {
            pos++;
            posible |= dfs(i+1, j, board, word, pos);
            pos--;
        }
        board[i][j] = prev;
        return posible;
    }
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    int pos = 0;
                    if (dfs(i, j, board, word, pos)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};