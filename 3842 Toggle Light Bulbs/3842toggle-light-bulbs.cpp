class Solution {
public:
    vector<int> toggleLightBulbs(vector<int>& bulbs) {
        unordered_map<int, int> freq;
        for (int bulb : bulbs) {
            freq[bulb] ^= 1;
        }
        vector<int> ons;
        for (auto& pair : freq) {
            if (pair.second) ons.push_back(pair.first); 
        }
        sort(ons.begin(), ons.end());
        return ons;
    }
};