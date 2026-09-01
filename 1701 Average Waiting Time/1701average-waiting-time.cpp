class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        double curr_time = customers[0][0];
        double total_wait = 0;
        for (auto& customer : customers) {
            curr_time = customer[0] > curr_time ? customer[0] + customer[1] : customer[1] + curr_time;
            total_wait += curr_time - customer[0];
        }
        return total_wait / (double)customers.size();
    }
};