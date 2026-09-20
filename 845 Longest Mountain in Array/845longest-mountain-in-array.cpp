class Solution {
public:
    int longestMountain(vector<int>& arr) {
        if (arr.size() <= 2) {
            return 0;
        }
        int n = arr.size();
        int left = 0, slop = 0, res = 0;
        int prev = left;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i-1]) {
                left++;
                prev = left;
                slop = 0;
            } else {
                if (arr[i] == arr[i-1]) {
                    prev = left = 0;
                    slop = 0;
                } else {
                    slop += !!prev;
                    res = max(prev + slop, res);
                    left = 0;
                }
            }
        }
        return res == 0 ? 0 : res + 1;
    }
};