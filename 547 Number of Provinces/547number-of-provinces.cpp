class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int count = 0;
        vector<vector<int>> adj(n);
        vector<bool> seen(n);
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isConnected[i][j]) {
                    adj[i].push_back(j);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (seen[i]) continue;
            q.push(i);
            seen[i] = true;
            count++;
            while (q.size()) {
                vector<int>& li = adj[q.front()];
                q.pop();
                for (int num : li) {
                    if (seen[num]) continue;
                    q.push(num);
                    seen[num] = true;
                }
            }
        }
        return count;
    }
};