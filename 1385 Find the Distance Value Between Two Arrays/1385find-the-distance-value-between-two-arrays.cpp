class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        int i = arr1.size() - 1, j = arr2.size() - 1, count = 0;
        while (i >= 0 && j >= 0) {
            int distance = abs(arr1[i] - arr2[j]);
            if (distance <= d) {
                count++;
                i--;
                continue;
            } else {
                if (arr1[i] > arr2[j]) {
                    i--;
                } else {
                    j--;
                }
            }
        }
        return arr1.size() - count;
    }
};