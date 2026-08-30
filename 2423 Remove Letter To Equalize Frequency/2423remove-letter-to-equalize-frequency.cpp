class Solution {
public:
    bool equalFrequency(string word) {
        unordered_map<char, int> freq;
        unordered_map<int, int> count_freq;

        for (char ch : word)
            freq[ch]++;

        for (auto& p : freq)
            count_freq[p.second]++;

        if (freq.size() == 1)
            return true;

        int min_occ = INT_MAX;
        int max_occ = 0;

        for (auto& p : count_freq) {
            min_occ = min(min_occ, p.first);
            max_occ = max(max_occ, p.first);
        }

        // All characters have the same frequency.
        if (count_freq.size() == 1)
            return min_occ == 1;

        // Two different frequencies.
        if (count_freq.size() == 2) {
            int low = min_occ;
            int high = max_occ;

            // Remove the only character having frequency 1.
            if (low == 1 && count_freq[low] == 1)
                return true;

            // Reduce the only character having the higher frequency.
            if (high == low + 1 && count_freq[high] == 1)
                return true;
        }

        return false;
    }
};