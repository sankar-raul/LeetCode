class Solution {
public:
    bool isV(char ch) {
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
    }
    string reverseVowels(string s) {
        int i = 0, j = s.size() - 1, n = s.size();
        while (i <= j) {
            while (i < n && !isV(s[i])) {
                i++;
            }
            while (j >= 0 && !isV(s[j])) {
                j--;
            }
            if (i <= j) {
                swap(s[i], s[j]);
            }
            i++, j--;
        }
        return s;
    }
};