/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* l3 = NULL;
        ListNode* cur = NULL;

        int carryOver = 0;
        while (l1 != NULL || l2 != NULL) {
            if (l1 == NULL) {
                l1 = new ListNode(0);
            }

            if (l2 == NULL) {
                l2 = new ListNode(0);
            }

            if (l3 == NULL) {
                l3 = new ListNode(0);
                cur = l3;
            } else {
                cur->next = new ListNode(0);
                cur = cur->next;
            }

            cur->val = (l1->val + l2->val + carryOver) % 10;
            carryOver = (l1->val + l2->val + carryOver) / 10;

            l1 = l1->next;
            l2 = l2->next;
        }

        if (carryOver > 0) {
            cur->next = new ListNode(0);
            cur = cur->next;

            cur->val = carryOver;
        }

        return l3;
    }
};
