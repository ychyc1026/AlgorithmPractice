# [栈]删除存在的数和求相邻两数为奇数的组合数

小蓝有一个栈，他不断地向这个栈的顶端添加数字。小蓝希望栈中不存在相同的数，当他加入了一个之前已经存在的数时，栈中之前存在的那个数会消失（其它原有元素的相对顺序不变），小蓝还想随时知道栈中所有相邻的数中和为奇数的总共有多少组，请你计算出小蓝要求的结果。

## 最终思路

未来思路：数组作栈使每次删除重复数都需要遍历，应该选用链表作栈，经过ai尝试发现链表作栈也不行，需要哈希表，目前没学，所以将数组版解答给出
目前思路：

- 原始问题：判断元素是否存在需要遍历数组（O(n)）+ 删除元素需要移动数组（O(n)）+ 统计奇偶对需要遍历数组（O(n)），三次O(n)叠加导致5e5数据超时；
- 优化1：新增bool数组（下标=元素值），O(1)判断元素是否存在，砍掉“判断存在性”的遍历；
- 优化2：找到重复元素位置后立即break，减少遍历长度；
- 局限性：删除的数组移动、统计奇偶对的遍历仍为O(n)，仅能覆盖70%用例（1e5数据），5e5数据仍超时。

## 提交

30%TLE

## 最终代码

```cpp
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

};
```
