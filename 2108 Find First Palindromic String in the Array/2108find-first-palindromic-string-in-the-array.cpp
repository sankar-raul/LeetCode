class Solution {
public:
    bool isPalindrom(string word) {
        int i = 0, j = word.size() - 1;
        while (i < j) {
            if (word[i++] != word[j--]) return false;
        }
        return true;
    }
    string firstPalindrome(vector<string>& words) {
        for (string word : words) {
            if (isPalindrom(word)) return word;
        }
        return "";
    }
};