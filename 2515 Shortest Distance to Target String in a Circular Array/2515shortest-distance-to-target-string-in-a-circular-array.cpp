class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        int i = startIndex, j = startIndex;
        int idx = n / 2 + n % 2;
        while (idx--) {
            if (words[i] == target || words[j] == target) {
                return n & 1 ? n / 2 - idx : n / 2 - idx - 1;
            }
            i = (i + 1) % n;
            j = (j - 1 + n) % n;
        }
        if (i == j && words[i] == target || words[j] == target) {
            return n / 2;
        }
        return -1;
    }
};