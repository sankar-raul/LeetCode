class Solution {
public:
    string digitSum(string s, int k) {
        string cp = s;
        while (cp.size() > k) {
            string tmp;
            int sum = 0;
            for (int i = 0; i < cp.size(); ++i) {
                sum += cp[i] - '0';
                if ((i + 1) % k == 0) {
                    tmp += to_string(sum);
                    sum = 0;
                }
            }
            if (cp.size() % k != 0) {
                tmp += to_string(sum);
            }
            cp = tmp;
        }
        return cp;
    }
};