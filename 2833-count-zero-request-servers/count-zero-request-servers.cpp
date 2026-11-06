
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        vector<pair<int, int>> query_idx;

        for (int i = 0; i < queries.size(); ++i) {
            query_idx.push_back({queries[i], i});
        }

        sort(query_idx.begin(), query_idx.end());

        sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        int i = 0, j = 0;
        int active_servers = 0;

        vector<int> res(queries.size());
        vector<int> busy(n + 1);

        for (auto& [t, idx] : query_idx) {

            while (j < logs.size() && logs[j][1] <= t) {
                int server = logs[j][0];

                if (busy[server]++ == 0) {
                    active_servers++;
                }

                j++;
            }

            while (i < j && logs[i][1] < t - x) {
                int server = logs[i][0];

                if (--busy[server] == 0) {
                    active_servers--;
                }

                i++;
            }

            res[idx] = n - active_servers;
        }

        return res;
    }
};
