# 📝 刷题总结：LeetCode 88\. 合并两个有序数组（个人踩坑完整版）

## 一、题目要求

给定两个升序有序数组 nums1、nums2，将 nums2 合并到 nums1 中，使 nums1 成为一个完整升序有序数组。

关键点：

- **nums1 长度为 m\+n，后 n 位是空位（0），专门用来存合并结果**

- 最终结果必须覆盖到 nums1 中，不能返回新数组

## 二、我的最初代码思路

使用**正向双指针 \+ 临时数组 temp** 归并合并：

1. i、j 分别遍历 nums1、nums2 有效区域

2. 每次把更小的元素放入 temp

3. 剩余元素直接尾部追加

4. 最后把 temp 整体赋值给 nums1

## 三、我出现的 **致命报错**（重点复盘）

### 错误信息

> runtime error: reference binding to null pointer of type 'int' \(stl\_vector\.h\)
> 
> UndefinedBehaviorSanitizer：空指针、越界未定义行为
> 
> 

### 错误根源（我最大的误区）

**空 vector 不能用下标 \[\] 赋值！！！**

我的错误代码：

```Plain Text
vector<int> temp; // 空容器，size=0
temp[t++] = nums1[i++]; // 非法！不存在 temp[0] 空间
```

原理：

- **vector 的 \[\] 运算符只能访问已经存在的元素，不会自动扩容**

- 空 vector 下标访问 = 越界 = 空指针绑定 = 直接 Runtime Error

- 只有 **push\_back** 能自动扩容、新增元素

## 四、我代码中的所有历史错误汇总（完整复盘）

### 错误1：变量未初始化（最初版本）

写了 `int i,j=0;`，导致 i 是随机垃圾值。

改正：必须 `int i=0,j=0,t=0;`

### 错误2：if 不带大括号，逻辑乱飞

最初没有 \{\}，导致 if 只控制第一行，第二行代码必执行，完全乱序。

改正：if\-else 必须成对带范围，保证逻辑完整。

### 错误3：空 vector 使用下标赋值（本次报错核心）

误以为数组和 vector 一样可以直接下标写入，忽略 vector 动态扩容特性。

两种正确写法：

1. **用 push\_back 追加（刷题首选、绝对不报错）**

2. 提前初始化容量`vector<int> temp(m+n)` 再用下标

### 错误4：写法能过样例但属于未定义行为

本地编译器不报错、LeetCode 旧判题机能过，**不代表代码正确**，属于运气通过。UBSan 严格检测直接杀崩。

## 五、修正后可完全 AC 的我的版本（正向归并版）

保留我习惯的“临时数组归并思路”，彻底修复 bug：

```Plain Text
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> temp;
        int i=0;
        int j=0;

        // 双指针正向合并
        while(i<m && j<n){
            if(nums1[i] <= nums2[j])
                temp.push_back(nums1[i++]);
            else
                temp.push_back(nums2[j++]);
        }
        // 剩余元素收尾
        while(i<m) temp.push_back(nums1[i++]);
        while(j<n) temp.push_back(nums2[j++]);

        // 覆盖回nums1
        nums1 = temp;
    }
};
```

## 六、最优解（面试标准答案：原地后向双指针 O\(1\)空间）

正向必须开临时数组（会覆盖未读取数据），**从后往前合并可以原地合并不覆盖**：

```Plain Text
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;

        while(i >= 0 && j >= 0){
            if(nums1[i] > nums2[j])
                nums1[k--] = nums1[i--];
            else
                nums1[k--] = nums2[j--];
        }
        // nums2剩余直接补
        while(j >= 0)
            nums1[k--] = nums2[j--];
    }
};
```

## 七、最终个人总结（思维提升）

- **vector 空容器绝对不能下标写值，只能 push\_back**，这是C\+\+刷题最高频 Runtime 错误

- 正向归并逻辑简单、好写，但空间 O\(n\)，适合初学理解

- 逆向双指针是本题**真正考点**：利用 nums1 后置空位，原地合并

- 能过样例 ≠ 代码正确，一定要规避未定义行为

- 分支语句必须带作用域，防止逻辑穿透

## 八、复杂度对比

- 正向临时数组版：时间 O\(m\+n\)，空间 O\(m\+n\)

- 逆向原地双指针版：时间 O\(m\+n\)，空间 O\(1\)（最优）

> （注：部分内容由豆包工作 AI 生成）
