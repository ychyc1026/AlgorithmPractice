#include <iostream>
using namespace std;

// 定义链表节点结构
struct ListNode {
    int data;
    struct ListNode* next;
};

// 创建新节点
ListNode* createNode(int value) {
    ListNode* newNode = new ListNode;
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

// 头插法：在链表头部插入
void insertAtHead(ListNode*& head, int value) {
    ListNode* newNode = createNode(value);
    newNode->next = head;
    head = newNode;
}

// 尾插法：在链表尾部插入
void insertAtTail(ListNode*& head, int value) {
    ListNode* newNode = createNode(value);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    ListNode* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 按位置插入（位置从0开始）
void insertAtPosition(ListNode*& head, int pos, int value) {
    if (pos < 0) return;
    if (pos == 0) {
        insertAtHead(head, value);
        return;
    }

    ListNode* temp = head;
    for (int i = 0; i < pos - 1 && temp != nullptr; ++i) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    ListNode* newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
}

// 有序插入（假设链表已按升序排列）
void insertSorted(ListNode*& head, int value) {
    if (head == nullptr || head->data >= value) {
        insertAtHead(head, value);
        return;
    }

    ListNode* current = head;
    while (current->next != nullptr && current->next->data < value) {
        current = current->next;
    }

    ListNode* newNode = createNode(value);
    newNode->next = current->next;
    current->next = newNode;
}

// 删除头节点
void deleteHead(ListNode*& head) {
    if (head == nullptr) return;
    ListNode* temp = head;
    head = head->next;
    delete temp;
}

// 删除尾节点
void deleteTail(ListNode*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        deleteHead(head);
        return;
    }

    ListNode* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// 按位置删除（位置从0开始）
void deleteAtPosition(ListNode*& head, int pos) {
    if (head == nullptr || pos < 0) return;
    if (pos == 0) {
        deleteHead(head);
        return;
    }

    ListNode* temp = head;
    for (int i = 0; i < pos - 1 && temp != nullptr; ++i) {
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    ListNode* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
}

// 按值删除第一个匹配项
void deleteByValue(ListNode*& head, int value) {
    if (head == nullptr) return;

    if (head->data == value) {
        deleteHead(head);
        return;
    }

    ListNode* prev = head;
    ListNode* curr = head->next;

    while (curr != nullptr && curr->data != value) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "Value not found!\n";
        return;
    }

    prev->next = curr->next;
    delete curr;
}

// 按值删除所有匹配项
void deleteAllByValue(ListNode*& head, int value) {
    // 先处理头部连续匹配的情况
    while (head != nullptr && head->data == value) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    if (head == nullptr) return;

    ListNode* prev = head;
    ListNode* curr = head->next;

    while (curr != nullptr) {
        if (curr->data == value) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

// 查找值是否存在
bool search(ListNode* head, int value) {
    ListNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

// 获取链表长度
int getLength(ListNode* head) {
    int len = 0;
    ListNode* temp = head;
    while (temp != nullptr) {
        len++;
        temp = temp->next;
    }
    return len;
}

// 打印链表
void printList(ListNode* head) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    ListNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

// 反转链表（迭代法）
ListNode* reverseIterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;   // 保存下一个节点
        curr->next = prev;   // 反转指针
        prev = curr;         // 移动 prev
        curr = next;         // 移动 curr
    }
    return prev; // 新的头节点
}

// 反转链表（递归法）
ListNode* reverseRecursive(ListNode* head) {
    // 基线条件
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* newHead = reverseRecursive(head->next);
    head->next->next = head; // 反转当前连接
    head->next = nullptr;    // 防止环

    return newHead;
}

// 清空链表（释放所有节点）
void clearList(ListNode*& head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// 销毁链表（等同于 clearList，但强调语义）
void destroyList(ListNode*& head) {
    clearList(head);
}

// 主函数：测试用例
int main() {
    ListNode* head = nullptr;

    // 测试插入
    insertAtTail(head, 10);
    insertAtTail(head, 20);
    insertAtHead(head, 5);
    insertAtPosition(head, 2, 15);
    cout << "After insertions: ";
    printList(head);

    // 测试查找
    cout << "Search 15: " << (search(head, 15) ? "Found" : "Not found") << "\n";

    // 测试删除
    deleteByValue(head, 15);
    cout << "After deleting 15: ";
    printList(head);

    insertSorted(head, 12);
    insertSorted(head, 25);
    cout << "After sorted insert (12, 25): ";
    printList(head);

    // 测试反转
    head = reverseIterative(head);
    cout << "After iterative reverse: ";
    printList(head);

    head = reverseRecursive(head);
    cout << "After recursive reverse: ";
    printList(head);

    // 测试长度
    cout << "Length: " << getLength(head) << "\n";

    // 清空
    destroyList(head);
    cout << "After destroy: ";
    printList(head);

    return 0;
}