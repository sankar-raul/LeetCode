class Solution {
public:
    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd) {
        sort(occupiedIntervals.begin(), occupiedIntervals.end());
        vector<vector<int>> merged;
        int left_min = occupiedIntervals[0][0], right_max = occupiedIntervals[0][1];
        int prev = left_min;
        for (int i = 1; i < occupiedIntervals.size(); i++) {
            int left = max(prev, occupiedIntervals[i][0]);
            int right = min(right_max, occupiedIntervals[i][1]);
            int gap = right - left;
            // if (freeStart >= occupiedIntervals[i][0] + 1 && freeEnd < occupiedIntervals[i][0]) {
                
            // }
            if (gap >= -1) { // then its a collision or touch
                prev = left;
                right_max = max(right_max, occupiedIntervals[i][1]);
            } else {
                merged.push_back({left_min, right_max});
                left_min = prev = occupiedIntervals[i][0];
                right_max = occupiedIntervals[i][1];
            }
        }
        merged.push_back({left_min, right_max});
        vector<vector<int>> res;
        for (int i = 0; i < merged.size(); ++i) {
            if (merged[i][1] >= freeStart && merged[i][1] <= freeEnd) {
                if (merged[i][0] < freeStart) {
                    res.push_back({merged[i][0], freeStart-1});
                }
            } else if (merged[i][0] >= freeStart && merged[i][0] <= freeEnd) {
                if (merged[i][1] > freeEnd) {
                    res.push_back({freeEnd+1, merged[i][1]});
                }
            } else if (merged[i][0] <= freeStart && merged[i][1] >= freeEnd) {
                if (merged[i][0] < freeStart) {
                    res.push_back({merged[i][0], freeStart - 1});
                }
                if (merged[i][1] > freeEnd) {
                    res.push_back({freeEnd + 1, merged[i][1]});
                }
            } else {
                res.push_back(merged[i]);
            }
        }
        return res;
    }
};