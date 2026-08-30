class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> maxpq;
        for (int st : stones) maxpq.push(st);
        while (maxpq.size() > 1) {
            int first = maxpq.top();
            maxpq.pop();
            int second = maxpq.top();
            maxpq.pop();
            maxpq.push(abs(first - second));
        }
        return maxpq.top();
    }
};