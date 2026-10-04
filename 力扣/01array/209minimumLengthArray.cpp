#include<bits/stdc++.h>
using namespace std;
//我的思路
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // 滑动窗口，前面的指针找解，后面的指针优化解
        int front=0;
        int back=0;
        int sum=0;
        int len=0;
        int min=INT_MAX;
        while (front<nums.size ()){           
            if (sum<target){     
                sum+=nums[front++];
            }
            //出来就满足了
            if (len<=min)
                min=len;
            else {
                // 此处 len 符合所求
                len=front-back+1;
                if (len<=min)
                min=len;
               do {
                sum-=nums [back];
                    back++;//自增的时候想好这个值被用到的地方，不要更新后被当成更新前使用
                    len--;
                } while (sum>=target);
                len++;//中间会不会出现更小的情况吗，不会，但是，这个len不是两个指针的差：front-back+1，我只把它当数值了
                //此处 len 符合所求
                if (len<=min)
                min=len;
            }
        }
        return min == INT_MAX ? 0 : min;
 }
};
//学习标准思路
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        //滑动窗口，前面的指针找解，后面的指针优化解
        int front = 0, back = 0;
        int sum = 0;
        int minLen = INT_MAX;
        int n = nums.size();
        while (front < n) {
            sum += nums[front]; // 先纳入当前元素
            // 满足条件，收缩左边界，尝试找更小窗口
            while (sum >= target) {
                int curLen = front - back + 1;
                if(curLen < minLen){
                    minLen = curLen;
                }
                //放在这里，进行操作之后不符合sum >= target，，跳出循环，不影响这个minlen
                sum -= nums[back];
                back++;
            }//出循环的时候，条件不符合，但是中途可能出现的每一个minlen都被比较了
            front++;
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};