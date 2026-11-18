class Solution {
public:
    int lengthOfLastWord(string s) {
        int words = s.find_last_not_of(" ");
        int result = s.find_last_of(" ",words);

        return words-result;
    }
};