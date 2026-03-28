#include <iostream>
#include <vector>
using namespace std;
//核心思想：bool动态数组，如果是链表，还要删除杀的人，bool直接标false，报数跳过
//这样坏人都在k——2k-1上，直接判断标flase的位置是不是这这个范围，链表判断一边界难定，二要看数
//取余成环
bool check(int k, int m) {
    vector<bool> alive(2 * k, true);//true是活着
    int remaining = 2 * k;//剩下多少人
    int pos = 0; // 从第0个人开始（第一个好人）

    // 要杀死k个坏人（编号k ~ 2k-1），且不能杀任何好人（0 ~ k-1）
    for (int killed = 0; killed < k; killed++) 
    {
        // 走 m-1 步（因为当前pos是第1个）
        int step = (m - 1) % remaining;//取余成环，万一走的步比人多呢
        //走m-1步
        while (step--) 
        {
            pos = (pos + 1) % (2 * k);
            while (!alive[pos]) //pos装的假说明死了，跳过
                pos = (pos + 1) % (2 * k);
        }

        // 现在pos是要杀的人
        if (pos < k) return false; // 杀了好人，m不合法，坏人是k-
        //杀了人就f
        alive[pos] = false;
        remaining--;

        // 下一个人开始数
        pos = (pos + 1) % (2 * k);
        while (!alive[pos])
            pos = (pos + 1) % (2 * k);
    }
    return true;
}

int main() {
    int k;
    cin >> k;
    int m = 1;
    while (true) {
        m++;//相当于m从2开始，不然m<=1，每个人都杀了
        if (check(k, m)) {
            cout << m << endl;
            break;
        }
    }
    return 0;
}