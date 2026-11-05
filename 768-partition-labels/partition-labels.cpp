class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> res;
        unordered_map<char, int> mp;
        unordered_set<char> seen;
        for (int i = 0; i < s.size(); ++i) {
            mp[s[i]] = i;
        }
        int left = 0;
        int right = mp[s[0]];
        seen.insert(s[0]);
        for (int i = 1; i < s.size(); ++i) {
            int last_seen = mp[s[i]];
            if (!seen.count(s[i])) {
                seen.insert(s[i]);
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