# LeetCode 1167\. Minimum Cost to Connect Sticks 题解

## 1\. 题意（翻译成人话）

题目：Minimum Cost to Connect Sticks（连接木棍的最小成本）

给定一堆木棍的长度，例如 sticks = \[2,4,3\]，规则如下：

- 每次从所有木棍中选两根，合并成一根新木棍，合并的花费 = 这两根木棍的长度之和；

- 反复执行合并操作，直到最后只剩下一根木棍；

- 求完成合并的总花费最小值。

示例（sticks = \[2,4,3\]）：

1. 合并 2 和 3，花费 2\+3=5，合并后木棍数组变为 \[5,4\]；

2. 合并 5 和 4，花费 5\+4=9，合并后木棍数组变为 \[9\]；

3. 总花费 = 5 \+ 9 = 14。

## 2\. 核心：为什么是哈夫曼树？

将每根木棍看作哈夫曼树的叶子节点，木棍长度即为叶子节点的权值，对应关系如下：

- 每次合并两根木棍 → 哈夫曼树中选择两个权值最小的节点合并；

- 单次合并的花费 → 合并后新节点（父节点）的权值；

- 总最小花费 → 哈夫曼树中所有非叶子节点的权值之和。

因此，本题的核心解法：**小根堆（优先队列）\+ 贪心算法**。

## 3\. 算法步骤（极简）

1. 将所有木棍的长度全部放入小根堆中；

2. 当堆中元素个数 ≥ 2 时，循环执行：
        

    - 取出堆中最小的两根木棍 x 和 y；

    - 将 x \+ y 累加到总花费中；

    - 将合并后的新木棍（长度为 x \+ y）重新放入小根堆；

3. 循环结束后，返回总花费即可。

## 4\. C\+\+ 代码（STL 小根堆）

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        int ans = 0;
        // 定义小根堆（STL 中 priority_queue 默认大根堆，需指定 greater<int>）
        priority_queue<int, vector<int>, greater<int>> q;
        // 将所有木棍放入堆中
        for (int x : sticks) q.push(x);

        // 堆中元素大于1时，持续合并
        while (q.size() > 1) {
            int x = q.top(); q.pop(); // 取出最小元素
            int y = q.top(); q.pop(); // 取出次小元素
            ans += x + y; // 累加花费
            q.push(x + y); // 合并后放回堆
        }
        return ans;
    }
};

```

## 5\. C 语言代码（手写小根堆）

与哈夫曼树构建代码逻辑一致，仅保留权值操作（无需存储节点左右孩子）：

```c
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010 // 堆的最大容量，根据题目需求调整

int heap[MAXN]; // 存储堆的数组（下标从1开始）
int sz = 0;     // 堆的当前大小（元素个数）

// 上浮操作：调整新插入的元素到正确位置（小根堆）
void up(int idx) {
    while (idx > 1) {
        int fa = idx / 2; // 父节点下标
        if (heap[fa] <= heap[idx]) break; // 父节点更小，无需调整
        // 交换父节点和当前节点
        int t = heap[fa]; heap[fa] = heap[idx]; heap[idx] = t;
        idx = fa; // 继续向上调整
    }
}

// 下沉操作：调整节点到正确位置（小根堆）
void down(int idx) {
    while (1) {
        int left = idx * 2, right = idx * 2 + 1; // 左右孩子下标
        int min = idx; // 假设当前节点是最小的
        // 比较左孩子，更新最小节点下标
        if (left <= sz && heap[left] < heap[min]) min = left;
        // 比较右孩子，更新最小节点下标
        if (right <= sz && heap[right] < heap[min]) min = right;
        if (min == idx) break; // 当前节点已是最小，无需调整
        // 交换当前节点和最小孩子节点
        int t = heap[idx]; heap[idx] = heap[min]; heap[min] = t;
        idx = min; // 继续向下调整
    }
}

// 向堆中插入元素
void push(int x) { heap[++sz] = x; up(sz); }

// 从堆中取出最小元素（堆顶）
int pop() { 
    int ret = heap[1]; // 堆顶元素（下标1）
    heap[1] = heap[sz--]; // 用最后一个元素替换堆顶，堆大小减1
    down(1); // 堆顶元素下沉调整
    return ret;
}

// 核心函数：计算连接木棍的最小花费
int connectSticks(int* sticks, int n) {
    sz = 0; // 初始化堆大小
    // 将所有木棍放入堆中
    for (int i = 0; i < n; i++) push(sticks[i]);
    int ans = 0;
    // 堆中元素大于1时，持续合并
    while (sz > 1) {
        int x = pop(); // 取出最小木棍
        int y = pop(); // 取出次小木棍
        ans += x + y;  // 累加花费
        push(x + y);   // 合并后放回堆
    }
    return ans;
}

// 测试示例
int main() {
    int arr[] = {2,4,3};
    printf("%d\n", connectSticks(arr, 3)); // 输出：14
    return 0;
}

```

## 6\. 复杂度分析

- 时间复杂度：O\(n log n\)。每根木棍需要入堆和出堆各一次，每次堆操作的时间复杂度为 O\(log n\)，总共有 n 根木棍，因此总时间复杂度为 O\(n log n\)。

- 空间复杂度：O\(n\)。堆需要存储所有木棍，最坏情况下堆的大小为 n，因此空间复杂度为 O\(n\)。

## 7\. 和哈夫曼树的关系（一句话）

LeetCode 1167 题，本质是“只计算合并代价、不存储树结构”的哈夫曼树构建过程；之前写的“数组转哈夫曼树”代码，去掉节点的左右孩子结构，仅保留权值的入堆、出堆和合并操作，就是本题的完整解法。

> （注：文档部分内容可能由 AI 生成）
