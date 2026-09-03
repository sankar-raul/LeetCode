class Solution {
public:
    vector<int> circularGameLosers(int n, int k) {
        vector<int> lookup(n);
        int pass = 0;
        int turn = 1;
        while (!lookup[pass]) {
            lookup[pass] = 1;
            pass = (pass + (k*turn++)) % n;
        }
        vector<int> losers;
        for (int i = 0; i < n; ++i) {
            if (!lookup[i]) {
                losers.push_back(i+1);
            }
        }
        return losers;
    }
};