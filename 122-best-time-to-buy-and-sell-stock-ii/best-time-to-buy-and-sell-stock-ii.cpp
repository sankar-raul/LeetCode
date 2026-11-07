class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy_price = prices[0];
        int profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (buy_price >= prices[i]) {
                buy_price = prices[i];
            } else {
                profit += prices[i] - buy_price;
                buy_price = prices[i];
            }
        }
        return profit;
    }
};