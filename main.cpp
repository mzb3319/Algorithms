/*
 * 冒泡排序
 * 输入：n个数字
 * 输出：n个数字的有序序列
 * 原址排序
 * 方法:从最后开始两两比较，把较小的数放到前边，重复此过程。相当于确定第i个数时(i从0开始)，从i+1往后的所有数中选一个最小的放到位置i处
 * 递归的调用该过程，就能完成排序的过程
 */

#include <iostream>
#include <vector>

using namespace std;

void bubble_sort(vector<int> &arr)
{
    for(int i=0;i<arr.size();i++)
    {
        for(int j=arr.size()-1;j>i;j--)
        {
            //改变条件为 arr[j]>arr[j-1] 可以变成按将序排列
            if(arr[j]<arr[j-1])
            {
                int tmp=arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=tmp;
            }
        }
    }
}

int main()
{
    vector<int> arr{2,1,-2,0,12,44,54};
    cout<<"arr:"<<endl;
    for(int n:arr)
    {
        cout<<n<<' ';
    }
    cout<<endl<<"sorted arr:"<<endl;
    bubble_sort(arr);
    for(int n:arr)
    {
        cout<<n<<' ';
    }
    cout<<endl;

    return 0;
}