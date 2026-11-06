class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy_price = 1e9;
        int max_profit = 0;
        for (int& price : prices) {
            if (buy_price >= price) {
                buy_price = price;
            } else {
                max_profit = max(max_profit, price - buy_price);
            }
        }
        return max_profit;
    }
};