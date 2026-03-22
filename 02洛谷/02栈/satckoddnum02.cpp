#include<iostream>
using namespace std;
//50万数组栈遍历多次，超时了，修改isexit函数
struct stack
{
    int data[1000000];
    int top;
    bool arr[1000000];
};
// 初始化栈
void init(stack* s)
{
    s->top = -1;
}
//
void isexit(stack* s, int a)
{
    if(s->arr[a] != true) {
        return;
    }
    //这样减少了一种遍历的情况
    int pos = -1;
    for (int i = 0; i <= s->top; ++i) {
        if (s->data[i] == a) {
            pos = i;
            break; // 找到位置立即退出，不重复遍历
        }
    }
    if (pos != -1) {
        for (int i = pos; i < s->top; ++i) {
            s->data[i] = s->data[i+1];
        }
        s->top--; // 栈顶减1
        s->arr[a] = false; // 关键6：标记元素已删除
    }
}
//输入后，栈更新后计数,要在调用函数之前
int isodd(stack*s)
{
    int sum=0;
    for(int i=0;i<s->top;i++)
    {
       if((s->data[i]+s->data[i+1])%2==1)
           sum++;
    }
    return sum;
}
// 入栈（先去重，再插入）
void add(stack* s, int a)
{
    isexit(s, a); // 先检查并删除重复元素
    s->data[++(s->top)] = a; // 新元素入栈
    s->arr[a]=true;
    cout<<isodd(s)<<endl;
}
int main()
{
    stack s;
    init(&s);
    int n;
    cin >> n;
    int* a = new int[n];//编译就确定数组的大小
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        add(&s, a[i]); 
    }
    delete[] a;
    return 0;
}