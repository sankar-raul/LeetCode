class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> res;
        vector<int> mp(26);
        for (int i = 0; i < s.size(); ++i) {
            mp[s[i] - 'a'] = i;
        }
        int left = 0;
        int right = mp[s[0] - 'a'];
        mp[s[0] - 'a'] = -1;
        for (int i = 1; i < s.size(); ++i) {
            int last_seen = mp[s[i] - 'a'];
            if (last_seen != -1) {
                mp[s[i] - 'a'] = -1;
                int p_a = i;
                int p_b = min(right, last_seen);
                int overlap = p_b - p_a;
                if (overlap >= 0) {
                    right = max(right, last_seen);
                } else {
                    res.push_back(right - left + 1);
                    left = i;
                    right = last_seen;
                }
            }
        }
        res.push_back(right - left + 1);
        return res;
    }
};