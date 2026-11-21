class Solution {
public:
    vector<string> assignUmbrella(vector<int>& rain) {
        int alice = 0, bob = 0, n = rain.size();
        vector<string> res;
        for (int i = 0; i < n; ++i) {
            if (i < n - 1 && rain[i] && rain[i+1]) {
                if (alice > bob) {
                    res.push_back("Bob");
                    bob++;
                } else {
                    res.push_back("Alice");
                    alice++;
                }
            } else if (rain[i]) {
                bob++;
                res.push_back("Bob");
            } else {
                res.push_back("None");
            }
        }
        return res;
    }
};