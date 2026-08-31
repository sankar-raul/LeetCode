class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int prev_gap = arr[1] - arr[0];
        for (int i = 2; i < arr.size(); ++i) {
            int gap = arr[i] - arr[i-1];
            if (prev_gap != gap) return false;
        }
        return true;
    }
};