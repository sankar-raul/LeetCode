class Solution {
public:
    int reqH(vector<int>& piles, int k) {
        int hours = 0;
        for (int pile : piles) {
            hours += pile / k + (pile % k != 0);
        }
        return hours;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int mini = 1e9;
        int maxi = 0;
        for (int pile : piles) {
            maxi = max(pile, maxi);
        }
        int left = 1, right = maxi, mid;
        while (left < right) {
            mid = left + (right - left) / 2;
            int time_spent = reqH(piles, mid);
            if (time_spent <= h && mini > mid) {
                mini = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return mini != 1e9 ? mini : maxi;
    }
};