#include <stdio.h>
//LeetCode 26 原题标准要求：原地修改原数组，不新建数组；返回去重之后的数组长度。
//考虑数组越界才是难点
int quickslow(int arr[],int len)//或者int *arr
{
    if(len==0) return 0;
    int slow=0;
    int quick=0;
    int len2=0;
    while(quick<len){
        
        while(arr[quick] == arr[slow]){
            quick++;
        }
        // 修复：quick跳出内层循环时，可能已经等于len了，此时不能赋值，说明已经处理完了
        if(quick < len)
            arr[++slow] = arr[quick];
        }

    //更新后的len怎么得？slow就是下标
    return slow+1;

}


int main()
{
    int arr[]={1,1,1,2,3,3,5,5,5,5,5,6,6,7,8,9,10};
    int len=sizeof(arr)/sizeof(arr[0]);
    printf("删除前数组：\n");
    for(int i=0;i<len;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    int len2=quickslow(arr,len);//返回删除后数组长度
    printf("删除后数组：\n");
    //返回新数组？不，返回原数组，不新建数组，不然从算法层面看太简单了
    for(int i=0;i<len2;i++)
    {
        printf("%d ",arr[i]);
    }

    return 0;
}


/*
int quickslow(int arr[], int len)
{
    if(len == 0) return 0;
    int slow = 0; // slow 指向已经确认不重复的最后一个元素
    
    // quick 从 1 开始遍历整个数组
    for(int quick = 1; quick < len; quick++){
        if(arr[quick] != arr[slow]){
            slow++;               // slow 先往前走一步，准备存放新元素
            arr[slow] = arr[quick]; // 把不重复的元素赋给 slow 的位置
        }
        // 如果相等，什么都不做，quick 继续往后找
    }
    // slow 是下标，0~slow 共有 slow+1 个元素
    return slow + 1; 
}
*/