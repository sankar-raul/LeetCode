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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* left = nullptr, *right = head;
        int i = 0, j = 0;
        while (right) {
            right = right->next;
            if (j-i > n-1) {
                i++;
                left = left ? left->next : head;
            }
            j++;
        }
        if (left)
            left->next = left->next->next;
        return left ? head : head->next;
    }
};