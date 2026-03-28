#include <stdio.h>
#include <stdlib.h> // 用于 malloc/free、exit
#include <stdbool.h>
typedef struct Node {
    int data;          
    struct Node* next; 
} Node;
typedef struct queue {
    Node* front;       
    Node* rear;        
    int size;          
} queue;
void init(queue* q) {
    if (q == NULL) return;//这行有点意思，判断指向堆内存的指针
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}
bool isfull(queue* q) {
    if (q == NULL) return false;
    return false;
}

bool isempty(queue* q) {
    if (q == NULL) return true;
    return q->front == NULL; // 等价于 q->size == 0
}

void push(queue* q, int a) {
    if (q == NULL) return;
    if (isfull(q)) { // 若设置了容量限制，这里会生效
        printf("满了，不能装了\n");
        return;
    }

    // 创建新节点
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) { // 内存分配失败（真正的“满”），一般不可能
        printf("内存不足，入队失败\n");
        return;
    }
    new_node->data = a;
    new_node->next = NULL;

    // 空队列：头尾都指向新节点
    if (isempty(q)) {
        q->front = new_node;
        q->rear = new_node;
    } else { // 非空队列：队尾节点指向新节点，更新队尾
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++; // 维护元素个数
}

void pop(queue* q) {
    if (q == NULL || isempty(q)) {
        printf("空的，不能再出了\n");
        return;
    }

    // 保存队头节点，用于释放内存
    Node* temp = q->front;
    // 队头指针后移
    q->front = q->front->next;
    // 释放原队头节点
    free(temp);
    q->size--; // 维护元素个数

    // 出队后队列为空，重置队尾
    if (q->front == NULL) {
        q->rear = NULL;
    }
}

void printtail(queue* q) {
    if (q == NULL || isempty(q)) {
        printf("队列为空，无队尾元素！\n");
        return;
    }
    printf("%d\n", q->rear->data);
}

void printhead(queue* q) {
    if (q == NULL || isempty(q)) {
        printf("队列为空，无队头元素！\n");
        return;
    }
    printf("%d\n", q->front->data);
}

void clean(queue* q) {
    if (q == NULL || isempty(q)) return;

    // 逐个释放节点，避免内存泄漏
    Node* temp = q->front;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    // 重置队列状态
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int getsize(queue* q) {
    if (q == NULL) return 0;
    return q->size; // 链表直接维护size，无需计算
}

int main() {
    queue q;
    init(&q);

    push(&q, 10);
    printtail(&q);   // 输出10
    push(&q, 20);
    printtail(&q);   // 输出20
    push(&q, 30);
    printtail(&q);   // 输出30
    pop(&q);
    printhead(&q);   // 输出20
    printf("%d\n", getsize(&q)); // 输出2

    clean(&q);
    printhead(&q);   // 输出：队列为空，无队头元素！
    return 0;
}