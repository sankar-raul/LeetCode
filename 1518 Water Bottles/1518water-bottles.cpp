class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int exchanged = numBottles / numExchange;
        int remainingBottles = numBottles % numExchange + exchanged;
        int canDrink = numBottles + exchanged;
        while (remainingBottles >= numExchange) {
            exchanged = remainingBottles / numExchange;
            remainingBottles = remainingBottles % numExchange + exchanged;
            canDrink += exchanged;
        }
        return canDrink;
    }
};