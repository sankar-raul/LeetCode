class Solution {
public:
    double distance(vector<int>& p1, vector<int>& p2) {
        int a = (p1[0] - p2[0]);
        int b = (p1[1] - p2[1]);
        return sqrt((a*a) + (b*b));
    }
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        map<double, int> freq;
        double d1 = distance(p1, p3);
        double d2 = distance(p2, p4);
        double a = distance(p1, p2);
        double b = distance(p2, p3);
        double c = distance(p3, p4);
        double d = distance(p4, p1);
        freq[d1]++;
        freq[d2]++;
        freq[a]++;
        freq[b]++;
        freq[c]++;
        freq[d]++;
        if (freq.size() > 2) {
            return false;
        }
        const auto start = freq.begin();
        const auto end = prev(freq.end());
        return end->second == 2 && end->first > start->first;
    }
};