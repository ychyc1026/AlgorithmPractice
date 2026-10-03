#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> temp(m+n);
        int i=0;
        int j=0;
        int t=0;
        while(i<m&&j<n){
            if(nums1[i]<=nums2[j])
            temp[t++]=nums1[i++];
            else
            temp[t++]=nums2[j++];
        }
        while(i<m){
            temp[t++]=nums1[i++];
        }
        while(j<n){
            temp[t++]=nums2[j++];
        }
        //将temp赋值给nums1
        nums1=temp;

    }
};
//原地双指针
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m-1, j=n-1, k=m+n-1;
        while(i>=0 && j>=0){
            if(nums1[i]>nums2[j]) nums1[k--]=nums1[i--];
            else nums1[k--]=nums2[j--];
        }
        while(j>=0) nums1[k--]=nums2[j--];
    }
};
