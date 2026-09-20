class Solution {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        long long ans = 0;
        int n = intervals.size();
        vector<int> starts(n);
        vector<int> ends(n);

        for (int i = 0; i < n; ++i) {
            starts[i] = intervals[i][0];
            ends[i] = intervals[i][1];
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        int endPtr = 0;
        for (int i = 0; i < n; ++i) {
            while (endPtr < n && ends[endPtr] < starts[i]) endPtr++;
            ans += i - endPtr;
        }
        return ans;
    }
};