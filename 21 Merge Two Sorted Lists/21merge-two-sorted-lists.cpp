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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = !list1 ? list2 : !list2 ? list1 : nullptr;
        ListNode* point = nullptr;
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                if (!point) {
                    point = list1;
                    head = point;
                } else {
                    point->next = list1;
                    point = point->next;
                }
                list1 = list1->next;
            } else {
                if (!point) {
                    point = list2;
                    head = point;
                } else {
                    point->next = list2;
                    point = point->next;
                }
                list2 = list2->next;
            }
        }
        if (list1 && point) {
            point->next = list1;
        }
        if (list2 && point) {
            point->next = list2;
        }
        return head;
    }
};