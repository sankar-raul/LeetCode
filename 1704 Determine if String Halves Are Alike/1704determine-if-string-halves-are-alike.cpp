class Solution {
    bool isVowel(char ch) {
        ch = tolower(ch);
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }
public:
    bool halvesAreAlike(string s) {
        int arr[] = {0, 0};
        int i = 0, j = s.size() - 1;
        while (i < j) {
            arr[0] += isVowel(s[i++]);
            arr[1] += isVowel(s[j--]);
        }
        return arr[0] == arr[1];
    }
};