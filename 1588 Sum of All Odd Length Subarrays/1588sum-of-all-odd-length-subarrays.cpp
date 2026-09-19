class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            arr[i] += arr[i-1]; 
        }
        int combinations = n / 2 + (n & 1) - 1, sum = arr[n - 1];
        int sub = 3;
        while (combinations--) {
            int i = 1;
            sum += arr[sub-1];
            while (i + sub <= n) {
                sum += arr[i + sub - 1] - arr[i-1];
                i++;
            }
            sub += 2;
        }
        return sum;
    }
};