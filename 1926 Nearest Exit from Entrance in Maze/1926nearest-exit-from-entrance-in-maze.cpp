class Solution {
public:
    int m, n;
    bool has_exit(int i, int j, vector<vector<char>>& maze, queue<pair<int, int>>& q, bool force) {
        // left
        if (!force && !(j && j + 1 < n && i && i + 1 < m)) {
            return true;
        }
        if (j && maze[i][j-1] != '+') {
            q.push({i, j-1});
            maze[i][j-1] = '+';
        }
        // right
        if (j + 1 < n && maze[i][j+1] != '+') {
            q.push({i, j+1});
            maze[i][j+1] = '+';
        }
        // top
        if (i && maze[i-1][j] != '+') {
            q.push({i-1, j});
            maze[i-1][j] = '+';
        }
        // down
        if (i + 1 < m && maze[i+1][j] != '+') {
            q.push({i+1, j});
            maze[i+1][j] = '+';
        }
        return false;
    }
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int steps = 0;
        m = maze.size();
        n = maze[0].size();
        queue<pair<int, int>> q;
        maze[entrance[0]][entrance[1]] = '+';
        has_exit(entrance[0], entrance[1], maze, q, true);
        while (q.size()) {
            int p = q.size();
            steps++;
            while (p--) {
                auto [i, j] = q.front();
                if (has_exit(i, j, maze, q, false)) {
                    return steps;
                }
                q.pop();
            }
        }
        return -1;
    }
};