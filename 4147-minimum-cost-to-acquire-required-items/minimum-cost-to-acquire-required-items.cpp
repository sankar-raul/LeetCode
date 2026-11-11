class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long res = 0;
        long long min_need = min(need1, need2);
        long long cost = min(costBoth, cost1 + cost2);
        res += min_need * cost;
        res += need1 > need2 ? (need1 - need2) * (long long)min(costBoth, cost1) : (need2 - need1) * (long long)min(costBoth, cost2);
        return res;
    }
};