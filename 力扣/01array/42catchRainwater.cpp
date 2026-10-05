#include<bits/stdc++.h>
using namespace std;
//dp法
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0; // 小于3个位置接不住水
        
        vector<int> left_max(n, 0);
        vector<int> right_max(n, 0);
        
        // 左遍历：预处理每个位置左侧的最大高度
        for (int i = 1; i < n; i++) {
            left_max[i] = max(left_max[i-1], height[i-1]);
        }
        
        // 右遍历：预处理每个位置右侧的最大高度
        for (int i = n-2; i >= 0; i--) {
            right_max[i] = max(right_max[i+1], height[i+1]);
        }
        
        // 累加每个位置的雨水量
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int water = min(left_max[i], right_max[i]) - height[i];
            if (water > 0) sum += water;
        }
        
        return sum;
    }
};
//双指针法，还没理解
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;
        
        int left = 0, right = n-1;
        int leftMax = 0, rightMax = 0;
        int sum = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                // 左边更矮，水位由左边最大值决定
                if (height[left] >= leftMax) {
                    leftMax = height[left]; // 遇到更高的柱子，更新左边界
                } else {
                    sum += leftMax - height[left]; // 低洼处能接住水
                }
                left++;
            } else {
                // 右边更矮，水位由右边最大值决定
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    sum += rightMax - height[right];
                }
                right--;
            }
        }
        return sum;
    }
};
