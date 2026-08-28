class Solution {
public:
    vector<double> convertTemperature(double celsius) {
        return { 273.15 + celsius, celsius * 1.80 + 32.00 };
    }
};