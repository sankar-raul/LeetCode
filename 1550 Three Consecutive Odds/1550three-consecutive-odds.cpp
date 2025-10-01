class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int consecutive = 0;
        for (int n : arr) {
            if (n % 2 != 0) {
                ++consecutive;
                if (consecutive == 3) {
                    return true;
            }
            } else {
                consecutive = 0;
            }
        }
        return false;
    }
};