#include<iostream>
using namespace std;
// 思路：用环形链表模拟约瑟夫环
// 1=好人，2=坏人
struct node 
{
    int val;
    node* next;
    node() : val(0), next(nullptr) {}
};

// 创建环形链表：k个好人 + k个坏人
node* newone(int k)
{
    node* head = new node();
    node* curr = head;
    curr->val = 1;        // 好人

    // 再建 k-1 个好人
    for(int i = 1; i < k; i++)
    {
        curr->next = new node();
        curr = curr->next;
        curr->val = 1;
    }
    // 建 k 个坏人
    for(int i = 0; i < k; i++)
    {
        curr->next = new node();
        curr = curr->next;
        curr->val = 2;
    }
    // 成环
    curr->next = head;
    return head;
}

// 释放整个链表（修复内存泄漏）
void freeList(node* head, int k) {
    if (!head) return;
    node* curr = head;
    for (int i = 0; i < 2*k; ++i) {
        node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

int main()
{
    int k;
    cin >> k;

    int m = 1;  // 从1开始试

    while(1)
    {
        m++;                // 逐个尝试m
        node* curr = newone(k);
        int count = 0;      // 已经杀掉的坏人数量
        bool fail = false;

        // 要杀掉 k 个坏人
        while (count < k)
        {
            // 核心修复：走 m-1 步，第 m 个杀掉
            for (int i = 1; i < m; ++i) {
                curr = curr->next;
            }

            // 现在 curr 就是要杀的人
            if (curr->val == 1) {
                // 杀到好人了，这个 m 不行
                fail = true;
                break;
            }

            // 删除 curr 节点（关键修复：删当前节点，不是删下一个）
            node* temp = curr;
            // 找到前一个节点
            node* pre = curr;
            while (pre->next != curr) {
                pre = pre->next;
            }
            pre->next = curr->next;
            curr = curr->next;  // 下一轮从下一个开始

            delete temp;
            count++;
        }

        freeList(curr, k);  // 释放本轮链表

        if (!fail) {
            // 成功杀光坏人，没杀好人
            cout << m << endl;
            break;
        }
    }

    return 0;
}


