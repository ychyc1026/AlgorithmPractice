#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (head == nullptr || m == n) 
            return head;

        ListNode* temp = head;
        ListNode* temp_prev = nullptr;
        for (int i = 1; i < m; i++) {
            temp_prev = temp;
            temp = temp->next;
        }

        ListNode* temp01 = temp;
        ListNode* curr = temp;
        ListNode* prev = nullptr;
        ListNode* t = nullptr;

        for (int i = m; i <= n; i++) {
            if (curr == nullptr) break;
            t = curr->next;
            curr->next = prev;
            prev = curr;
            curr = t;
        }

        if (temp_prev != nullptr) {
            temp_prev->next = prev;
        } else {
            head = prev;
        }

        temp01->next = curr;
        return head;
    }
};