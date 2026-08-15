class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.size();
        if (n <= 3) {
            return s;
        }
        int mid = n / 2;
        sort(s.begin(), s.begin() + mid);
        for (int i = 0; i < mid; ++i) {
            s[n-i-1] = s[i];
        }
        return s;
    }
};