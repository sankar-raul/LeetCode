class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b){
            return a[0] < b[0];
        });
        vector<vector<int>> res;
        int left = intervals[0][0];
        int right = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            int point_a = max(left, intervals[i][0]);
            int point_b = min(right, intervals[i][1]);
            int overlap = point_b - point_a;
            if (overlap >= 0) { // its overlap
                right = max(right, intervals[i][1]);
            } else {
                res.push_back({left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        res.push_back({left, right});
        return res;
    }
};