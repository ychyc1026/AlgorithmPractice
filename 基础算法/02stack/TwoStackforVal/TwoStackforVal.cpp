//理解：top就是下标，初始化为-1，先移动栈顶再存值，栈顶就一直指着值，不用额外符号来存下标
//双栈法要变读边算
#include<iostream>
#include<string>
using namespace std;
#define MAXSIZE 100
typedef struct {
    double data[MAXSIZE];  // 数字用double
    int top;            
} Stack01;
typedef struct {
    char data[MAXSIZE];  //符号用char
    int top;
    int grade[MAXSIZE];            
} Stack02;
int main()
{
    Stack01 val;//数字
    Stack02 sym;//符号
    val.top=-1;
    sym.top=-1;
    string exp;
    int Top=-1,temp=-1;
    cout<<"请输入一个算术表达式，不用带'='号"<<endl;
    getline(cin, exp);
    for(int i=0;i<exp.size();i++){
    if(exp[i]>='0'&&exp[i]<='9'){
            int num=0;
            for(;i<exp.size()&&exp[i]>='0'&&exp[i]<='9';i++)
                num=num*10+(exp[i]-'0');
                i--;//关键！回退一格，因为循环结束，exp[i]现在是符号位
                val.top++;
            val.data[val.top]=num;            
        }

    else if (exp[i] == '+' || exp[i] == '-'|| exp[i] == '*' || exp[i] == '/' || exp[i] == '(' || exp[i] == ')')
        {
           //先记录一下栈顶指针等级
            if(sym.top>=0)
            Top=sym.grade[sym.top];
            //查一波符号等级
            char lalalal=exp[i]; 

            //双栈法规则：先比较、先算，算完了才能入栈新符号！
            //先拿优先级再判断运算再算再入栈符号

            if(exp[i] == '+' || exp[i] == '-')
            temp=0;
            else if(exp[i] == '*' || exp[i] == '/')
            temp=1;
            else
            temp=2;
            
         //算
        while(Top!=-1&&Top>=temp){
          // 弹符号
        char op = sym.data[sym.top]; sym.top--;

        // 弹两个数
        double b = val.data[val.top]; val.top--;
        double a = val.data[val.top]; val.top--;

        // 计算
        double res;
        if(op == '+') res = a + b;
        else if(op == '-') res = a - b;
        else if(op == '*') res = a * b;
        else if(op == '/') res = a / b;

        // 结果压回去
        val.top++;
        val.data[val.top] = res;

        // 再更新一下旧栈顶（算完后栈顶变了）
        if(sym.top >=0) Top = sym.grade[sym.top];
        else Top = -1;
        }

        //级别处理完，入栈新符号
        sym.top++;
        sym.data[sym.top]=exp[i];
        sym.grade[sym.top]=temp;
            
        }
    else
        cout<<"你这输入的式子多少有点问题"<<endl;
       
    }

    //最后把栈里剩下的符号全部算完
    while(sym.top >= 0){
        char op = sym.data[sym.top]; sym.top--;
        double b = val.data[val.top]; val.top--;
        double a = val.data[val.top]; val.top--;
        double res;
        if(op == '+') res = a + b;
        else if(op == '-') res = a - b;
        else if(op == '*') res = a * b;
        else if(op == '/') res = a / b;
        val.top++;
        val.data[val.top] = res;
    }

    cout << "计算结果：" << val.data[val.top] << endl;

    return 0;
}