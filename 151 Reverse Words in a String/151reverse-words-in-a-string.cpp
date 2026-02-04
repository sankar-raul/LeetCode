class Solution {
public:
    void reverseS(string &s, int start, int end) {
        while (start <= end) {
            swap(s[start++], s[end--]);
        }
    }
    string reverseWords(string s) {
        int start = 0;
        int end = 0;
        bool space = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ' && !space) {
                start = i;
                end = i;
                continue;
            } else if (s[i] != ' ') {
                space = true;
                end = i;
            } else {
                space = true;
                reverseS(s, start, end);
                start = i + 1;
                end = i + 1;
            }
        }
        if (start != end) {
            reverseS(s, start, end);
        }
        bool flag = false;
        string res = "";
        for (int i = s.size()-1; i >= 0; i--) {
            if (s[i] == ' ') {
                flag = true;
            } else {
                if (flag && res != "") {
                    res += ' ';
                }
                flag = false;
                res += s[i]; 
            }
        }
        return res;
    }
};