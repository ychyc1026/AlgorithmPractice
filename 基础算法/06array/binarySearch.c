#include<stdio.h>
//递归版

// nums：有序数组，target：查找值，left、right当前搜索区间
int binarySearch(int* nums, int target, int left, int right)
{
    // 递归终止条件：区间空了，找不到
    if(left > right)
    {
        return -1;
    }
    //每次函数调用都要有mid
    int mid = left + (right - left) / 2; // 防溢出
    
    if(nums[mid] == target)
    {
        return mid; // 找到目标，返回下标
    }
    else if(nums[mid] < target)
    {
        // 目标在右半区间，递归搜索 [mid+1, right]
        return binarySearch(nums, target, mid + 1, right);
    }
    else
    {
        // 目标在左半区间，递归搜索 [left, mid-1]
        return binarySearch(nums, target, left, mid - 1);
    }
}
//非递归版
int binarySearch(int* nums, int target,int len) {
    int left = 0;
    int right = len- 1; // 左闭右闭区间 [0, n-1]

    while(left <= right) { // 区间还有元素才循环
        int mid = left + (right - left) / 2; // 防止溢出，等价于 (left+right)/2
        
        if(nums[mid] == target) {
            return mid; // 找到，返回下标
        } else if(nums[mid] < target) {
            left = mid + 1; // 目标在右边，左边界右移
        } else {
            right = mid - 1; // 目标在左边，右边界左移
        }
    }
    return -1; // 找不到目标
}

