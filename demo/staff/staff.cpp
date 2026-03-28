#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>  // setw ,手动写对齐的空格数
#include <windows.h>
#include <locale>
using namespace std;
//用多态实现，职工大类为虚函数
//外包，职员，经理，老板（目前只写了两个）
//小公司，数组装信息
//第一个问题，不知道怎么读取文件的信息（按行，字符，全部？读了怎么打印），第二个，显示在程序上对不齐
//文本文件 不支持 “删除中间一行” 这种操作,要修改就全删重写（读到程序中，清楚文件，程序修改再写进去）
//文件读取，清空，i为0，读一个加一个
//原本的逻辑是，运行添加，i++，读取从文件中读，i++，打印s[i]内容，一来i打开文件就清零了，二来添加和读取文件放的地方一样，重复混乱
//loadEmp();读一次就够了，不用每个操作函数都用这个函数，因为函数读的内存
//函数操作的是内存，但每个函数操作完了都写进文件（程序也修改了），完全可以退出时再写进文件，但怕被卡
//最后一关，编码对齐，utf-8和windows GBK编码冲突，cout绑控制台API，程序输出正常，但fstream裸读写，导致中文乱码

// 职工抽象基类
class staff {
public:
    int m_id;
    string m_name;
    int m_salary;
    int m_deptid;

    virtual void showyou() = 0;
    virtual int getDept() = 0; //用于获取岗位类型以便保存
    virtual ~staff() = default;
};

// 外包类
class waibao : public staff 
{
public:
    waibao(int id, string name, int salary, int deptid) 
    {
        m_id = id; m_name = name; m_salary = salary; m_deptid = deptid;
    }
    //sewt(字段数)，left左对齐
    void showyou() 
    {
        cout << "编号：" << setw(5) << left << m_id
             << " 姓名：" << setw(10) << left << m_name
             << " 薪水：" << setw(8) << left << m_salary
             << " 岗位：外包" << endl;
    }
    int getDept() { return 1; }
};

// 职员类
class zhiyuan : public staff 
{
public:
    zhiyuan(int id, string name, int salary, int deptid) 
    {
        m_id = id; m_name = name; m_salary = salary; m_deptid = deptid;
    }
    void showyou() 
    {
        cout << "编号：" << setw(5) << left << m_id
             << " 姓名：" << setw(10) << left << m_name
             << " 薪水：" << setw(8) << left << m_salary
             << " 岗位：普通职员" << endl;
    }
    int getDept() { return 2; }
};
//在类里面干这些事，函数都在一个域，不用传参
class WorkerManager {
public:
    staff* s[100];//公司暂定100人
    int i;

    WorkerManager() {
        i = 0;
        loadEmp();//读文件到程序
    }

    void showMenu() {
        cout << "\n======================" << endl;
        cout << "****职工管理系统****" << endl;
        cout << "1. 添加职工  2. 显示职工" << endl;
        cout << "3. 删除职工  4. 修改职工" << endl;
        cout << "5. 查找职工  6. 排序(未实现)" << endl;
        cout << "7. 清空数据  0. 退出系统" << endl;
        cout << "======================" << endl;
    }

    void savetofile() //程序写进文件
    {
        ofstream ofs("staff_text", ios::trunc);//默认out和trunc可以不写
        for (int j = 0; j < i; j++) 
        {
            // 多存一个 getDept()，不然读回来分不清职位
            ofs << s[j]->m_id << " " 
                << s[j]->m_name << " " 
                << s[j]->m_salary << " " 
                << s[j]->getDept() << endl;
        }
        ofs.close();
    }

    void loadEmp() 
    {
        ifstream ifs("staff_text");
        if (!ifs.is_open()) return;

        int id, sal, type;
        string name;
        // 关键：读取时必须和保存格式严格对应
        while (ifs >> id >> name >> sal >> type) 
        {
            //不止1和2，未来可扩展
            if (type == 1) 
            s[i] = new waibao(id, name, sal, type);
            else 
            s[i] = new zhiyuan(id, name, sal, type);
            i++;
        }
        ifs.close();
    }

    void addEmp() 
    {
        int id, salary, deptid;
        string name;
        cout << "请输入编号: "; 
        cin >> id;
        cout << "请输入姓名: ";
        cin >> name;
        cout << "请输入薪水: "; cin >> salary;
        cout << "请选择岗位(1-外包, 2-职员): "; cin >> deptid;

        if (deptid == 1) 
        s[i] = new waibao(id, name, salary, deptid);
        else 
        s[i] = new zhiyuan(id, name, salary, deptid);
        
        i++;
        savetofile();
        cout << "添加成功！" << endl;
    }

    void showEmp() 
    {
        if (i == 0) 
        { 
            cout << "暂无数据！" << endl; 
            return; 
        }
        printf("%-18s%-18s%-18s%-18s\n", "编号", "姓名", "薪水", "岗位");
        printf("-------------------------------------------------\n");
        for (int n = 0; n < i; n++) 
        {
            s[n]->showyou();
        }
    }

    void delEmp() 
    {
        if (i == 0) 
        return;
        int x1;
        cout << "输入要删除的ID: "; 
        cin >> x1;
        int index = -1;
        for (int j = 0; j < i; j++) 
        {
            if (s[j]->m_id == x1) 
            { 
                index = j; 
                break; 
            }
        }
        if (index != -1) 
        {
            delete s[index];
            for (int j = index; j < i - 1; j++) 
            s[j] = s[j + 1];
            i--;
            savetofile();
            cout << "删除成功！" << endl;
        } 
        else 
        {
            cout << "未找到该ID！" << endl;
        }
    }

    void modEmp() //modify
    {
        if (i == 0) return;
        int x1;
        cout << "输入修改ID: "; 
        cin >> x1;
        for (int j = 0; j < i; j++) 
        {
            if (s[j]->m_id == x1) 
            {
                cout << "输入新姓名: "; 
                cin >> s[j]->m_name;
                cout << "输入新薪水: "; 
                cin >> s[j]->m_salary;
                savetofile();
                return;
            }
        }
        cout << "未找到！" << endl;
    }

    void findEmp() 
    {
        int id; 
        cout << "输入查找ID: "; 
        cin >> id;
        for (int j = 0; j < i; j++) 
        {
            if (s[j]->m_id == id) 
            { 
                s[j]->showyou(); 
                return; 
            }
        }
        cout << "查无此人。" << endl;
    }

    void cleanEmp() 
    {
        for (int j = 0; j < i; j++) 
        { 
            delete s[j]; 
            s[j] = nullptr; 
        }
        i = 0;
        ofstream ofs("staff_text", ios::trunc);
        ofs.close();
        cout << "数据已清空！" << endl;
    }

    ~WorkerManager() 
    { // 析构释放内存
        for (int j = 0; j < i; j++) 
        { 
            delete s[j]; 
        }
    }
};

int main() 
{
    // 强制UTF-8，Windows MinGW 唯一不翻车的中文配置
    // system("chcp 65001 > nul");
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    // setlocale(LC_ALL, "zh_CN.UTF-8");
    //看来依旧没用
    WorkerManager wm;
    int choice;

    while (true) 
    {
        wm.showMenu();
        cout << "选择操作: ";
        if (!(cin >> choice)) 
        break;
        switch (choice) {
            case 1: wm.addEmp(); break;
            case 2: wm.showEmp(); break;
            case 3: wm.delEmp(); break;
            case 4: wm.modEmp(); break;
            case 5: wm.findEmp(); break;
            case 7: wm.cleanEmp(); break;
            case 0: return 0;
            default: break;
        }
    }
    return 0;
}