class Solution {
public:
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        int first = 0, second = 0, target = 0;
        for (int i = 0; i < firstWord.size(); ++i) {
            first = (firstWord[i] - 'a') + (first * 10);
        }
        for (int i = 0; i < secondWord.size(); ++i) {
            second = (secondWord[i] - 'a') + (second * 10);
        }
        for (int i = 0; i < targetWord.size(); ++i) {
            target = (targetWord[i] - 'a') + (target * 10);
        }
        return target == first + second;
    }
};