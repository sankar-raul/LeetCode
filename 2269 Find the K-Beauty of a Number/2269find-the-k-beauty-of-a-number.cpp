class Solution {
public:
    int divisorSubstrings(int num, int k) {
        int subnum = 0, i = 0, j = 0, count = 0;
        int tmp = num;
        while (num != 0) {
            int n = num % 10;
            if (j - i >= k) {
                count += subnum && tmp % subnum == 0;
                subnum /= 10;
                subnum = (n * pow(10, j-i-1)) + subnum;
                i++;
            } else {
                subnum = (n * pow(10, j-i)) + subnum;
            }
            num /= 10;
            j++;
        }
        cout << count << endl;
        count += subnum && tmp % subnum == 0;
        return count;
    }
};