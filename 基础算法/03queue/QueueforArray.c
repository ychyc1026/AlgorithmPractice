#include <stdio.h>
#include <stdlib.h> // 用于 malloc/free、exit
#include <stdbool.h>
#define max_s 100
// 定义循环队列结构体
typedef struct queue{
    int data[max_s];
    int capacity;  // 数组总容量
    int front;    
    int rear;      
}queue;
void init(queue* q)
{
   q->front=0;
   q->rear=0;
   q->capacity=max_s;
}
bool isfull(queue*q)
{
    return (q->rear+1)%q->capacity==q->front;//相差1，挨着
}
bool isempty(queue*q)
{
    return q->front==q->rear;
}
void push(queue*q,int a)
{
    if(isfull(q))
    {
        printf("满了，不能装了\n");
        return;
    }
    q->data[q->rear]=a;
    q->rear=(q->rear+1)%q->capacity;//成环的操作
}
void pop(queue*q)
{
    if(isempty(q))
    {
        printf("空的，不能再出了\n");
        return;
    }
    q->front = (q->front + 1 ) % q->capacity;
}
void printtail(queue* q)
{
    if(isempty(q))
    {
       printf("空的，打印失败"); 
       return;
    }
    int tail = (q->rear - 1 +q->capacity) % max_s;
    printf("%d\n", q->data[tail]);
}
void printhead(queue*q)
{
    if(isempty(q))
    {
       printf("空的，打印失败"); 
       return;
    }
    printf("%d\n",q->data[q->front]);
}

void clean(queue*q)
{
    q->front=0;
    q->rear=0;
}
int getsize(queue*q)
{
    return (q->rear+q->capacity-q->front)%q->capacity;//避免了小减大出现负数的情况
}
int main()
{
    //随便来的测试案例
    struct queue q;
    init(&q);
    push(&q,10);
    printtail(&q);
    push(&q,20);
    printtail(&q);
    push(&q,30);
    printtail(&q);
    pop(&q);
    printhead(&q);
    printf("%d\n",getsize(&q));
    return 0;
}