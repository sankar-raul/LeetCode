class Solution {
public:
    bool checkDistances(string s, vector<int>& distance) {
        unordered_map<char, int> gaps;
        for (int i = 0; i < s.size(); ++i) {
            if (gaps[s[i]]) {
                if (distance[s[i] - 'a'] != i - gaps[s[i]]) return false;
            } else {
                gaps[s[i]] = i + 1;
            }
        }
        return true;
    }
};