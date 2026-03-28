#include<iostream>
using namespace std;
struct stack
{
    int data[1000000];
    int top;
};
// 初始化栈
void init(stack* s)
{
    s->top = -1;
}
void isexit(stack* s, int a)
{
    int pos = -1;
    for (int i = 0; i <= s->top; i++) 
    {
        if (s->data[i] == a) 
        {
            pos = i; // 记录重复元素的下标
            break;
        }
    }
    if (pos != -1) {
        for (int i = pos; i < s->top; i++) 
        {
            s->data[i] = s->data[i+1];
        }
        s->top--; // 栈顶减1（删除了一个元素）
    }
}
// 入栈（先去重，再插入）
void add(stack* s, int a)
{
    isexit(s, a); // 先检查并删除重复元素
    s->data[++(s->top)] = a; // 新元素入栈
}
int main()
{
    stack s;
    init(&s);
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        add(&s, a[i]); 
    }
    // 打印最终栈（验证结果）
    for (int i = 0; i <= s.top; i++) 
    {
        cout << s.data[i] <<endl;
    }
    delete[] a;
    return 0;
}