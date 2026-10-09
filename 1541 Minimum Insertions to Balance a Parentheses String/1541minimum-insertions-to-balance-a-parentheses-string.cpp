class Solution {
public:
    int minInsertions(string s) {
        int neg_count = 0, res = 0;
        float count = 0;
        for (char ch : s) {
            if (ch == '(') {
                if (fmod(count, 1.0) == 0.5) {
                    res += 1;
                    count += 0.5;
                } else {
                    count++;
                }
                if (neg_count) {
                    res += neg_count / 2;
                    res += neg_count % 2 * 2;
                    neg_count = 0;
                } 
            } else if (count == 0) {
                neg_count++;
            } else {
                count -= 0.5;
            }
        }
        if (neg_count) {
            res += neg_count / 2;
            res += neg_count % 2 * 2;
            neg_count = 0;
        }
        res += count * 2;
        return res;
    }
};