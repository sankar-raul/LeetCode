class Solution {
public:
    vector<int> scoreValidator(vector<string>& events) {
        int scores = 0, counter = 0;
        for (string e : events) {
            if (e == "W") {
                if (++counter == 10) return {scores, counter};
            } else if (e == "WD" || e == "NB") {
                scores++;
            } else {
                scores += e[0] - '0';
            }
        }
        return {scores, counter};
    }
};