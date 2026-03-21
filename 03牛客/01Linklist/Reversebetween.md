# [链表]反转区间内链表

将一个节点数为 size 链表 m 位置到 n 位置之间的区间反转，要求时间复杂度 O(n)，空间复杂度 O(1)

## 最终思路

链表分成3区间，断链操作中间区间，三指针反转，相连，第一区间链接第二区间新头时连的是循环最后一个prev(经过curr赋值)，第二区间链接第三区间头时连的是curr(经过curr->next赋值)，要考虑空指针情况(有无节点)

## 提交

错误原因：1.没有考虑边界情况，m=1，即从头节点开始作为反转区间2.没有考虑循环出现空指针3.没有考虑有无节点就相连
修复思路：分析m=1的情况，加空指针防护，if讨论

## 最终代码

```cpp

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (head == nullptr || m == n) 
            return head;

        ListNode*temp = head;
        ListNode*temp_prev = nullptr;

        // 循环结束后，temp指向反转区间第一个节点（m对应的节点）
        for(int i=1; i<m; i++) {
            temp_prev = temp;       // temp_prev：反转区间的前驱节点
            temp = temp->next;      // temp：反转区间第一个节点
        }

        // 断链操作
        ListNode*temp01 = temp;       // 反转区间第一个节点（m对应的节点）
        ListNode*temp02 = temp->next; // 反转区间第一个节点的下一个节点
        ListNode*curr = temp;         // 反转起始节点（从区间第一个节点开始）
        ListNode*prev = nullptr;

        // 逐节点反转[m,n]区间
        for(int i=m; i<=n; i++) {
            if(curr == nullptr) break; // 空指针防护
            ListNode*t = curr->next;
            curr->next = prev;
            prev = curr;
            curr = t;
        }

        // 链接：先处理反转区间前驱节点的指向
        if(temp_prev != nullptr) {
            temp_prev->next = prev; // 前驱节点指向反转后的区间首节点
        } else {
            head = prev; // m=1时，没有前驱节点，head更新为反转后的首节点
        }

        // 链接：反转区间原首节点指向反转后的区间后第一个节点
        temp01->next = curr;

        return head;
    }
};
```
