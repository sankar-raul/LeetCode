class Solution {
public:
    bool digitCount(string num) {
        unordered_map<int, int> freq;
        for (char ch : num) {
            freq[int(ch - '0')]++;
        }
        for (int i = 0; i < num.size(); i++) {
            if (freq[i] != int(num[i] - '0')) {
                return false;
            }
        }
        return true;
    }
};