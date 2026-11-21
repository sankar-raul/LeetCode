class Solution {
public:
    vector<string> assignUmbrella(vector<int>& rain) {
        int alice = 0, bob = 0, n = rain.size();
        vector<string> res(rain.size());
        for (int i = 0; i < n; ++i) {
            if (i < n - 1 && rain[i] && rain[i+1]) {
                if (alice > bob) {
                    res[i] = "Bob";
                    bob++;
                } else {
                    res[i] = "Alice";
                    alice++;
                }
            } else if (rain[i]) {
                bob++;
                res[i] = "Bob";
            } else {
                res[i] = "None";
            }
        }
        return res;
    }
};