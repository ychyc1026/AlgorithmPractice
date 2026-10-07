#include<bits/stdc++.h>
using namespace std;
//买卖股票的最佳时期


//法1
//双重循环，执行用时679ms，太慢了
//思想：每个卖出日 left，找左边所有天里的最低价
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int right=0;
        int left=0;
        int maxProfit=0;
        int min=prices[0];
        int minadd=0;
        while(left<prices.size()-1){
            right=minadd; //应该是min所在的位置
            left++;
            while(right<=left){
                if(prices[right]<=min){
                    min=prices[right];
                    minadd=right;
                }
                
               right++;
            }
            if(prices[left]-min>maxProfit){
                maxProfit=prices[left]-min;
            }
            
        }
        return maxProfit;
    }
};


//法2
//一次扫描，遇到低价格就更新
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = prices[0];
        int maxProfit = 0;
        int n = prices.size();
        
        for(int i = 1; i < n; i++){
            // 遇到更低的价格，更新买入点
            if(prices[i] < minPrice){
                minPrice = prices[i];
            }
            // 否则计算今天卖出的利润，更新最大值
            else{
                maxProfit = max(maxProfit, prices[i] - minPrice);
            }
        }
        return maxProfit;
    }
};

//问题反思：
/*
1. 数组越界高频原因：循环内先自增下标，再访问数组，最后一轮必然越界；永远遵循「先访问，后自增」
2. 买卖股票问题本质：枚举卖出日，维护左侧最小值，一次遍历即可，不需要双指针嵌套
3. 边界防御：访问 prices[0] 前先判断数组是否为空，避免极端用例崩溃 */
