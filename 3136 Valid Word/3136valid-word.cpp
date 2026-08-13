class Solution {
public:
    bool isValid(string word) {
        if (word.size() < 3)
            return false;
        bool isV = false;
        bool isCon = false;
        for (char ch : word) {
            ch = tolower(ch);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                isV = true;
            } else if (ch >= 'a' && ch <= 'z') {
                isCon = true;
            } else if (ch >= '0' && ch <= '9') {
                continue;
            } else {
                return false;
            }
        }
        return isV && isCon;
    }
};