/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int i = -1, j = 0, last = -1, maxi = -1, mini = 1e9;
        ListNode* prev = head;
        head = head->next;
        while (head->next) {
            if ((prev->val > head->val && head->next->val > head->val) || (prev->val < head->val && head->next->val < head->val)) {
                if (i != -1) {
                    maxi = j - i;
                } else {
                    i = j;
                }
                mini = last != -1 ? min(mini, j - last) : 1e9;
                last = j;
            }
            prev = head;
            head = head->next;
            j++;
        }
        return {mini == 1e9 ? -1 : mini, maxi};
    }
};