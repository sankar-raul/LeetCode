class Solution {
public:
    bool checkIfPangram(string sentence) {
        int alpha[26];
        for (char ch : sentence) {
            alpha[ch - 'a']++;
        }
        for (int word_count : alpha) {
            if (!word_count) {
                return false;
            }
        }
        return true;
    }
};