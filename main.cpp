/*
 * 最大子数组问题
 * 输入：n个数字的序列，有正有负
 * 输出：数组中子数组的和最大
 *
 * 方法1:采用分治策略，把数组分成两部分，最大子数组要么在分界点左边，要么在分界点右边，要么跨过分界点
 * 方法2:找规律，遍历一遍数组，遍历的过程中记录已经遍历过的数字的和，和一个最大值，如果和 大于0 则继续遍历，如果和大于已经记录的最大值，则用更新最大值，
 *       如果遍历过程中和 小于0，则说明之前遍历过的数字的和已经不适合加入到最终的结果中，则丢弃之前遍历的所有数字的和，即把和置为0，接着遍历并重复上边的过程
 */

#include <iostream>
#include <vector>

using namespace std;

int findCross(vector<int> &arr,int beg,int end)
{

    int mid=(beg+end)/2;
    int lMax=0,rMax=0;
    int add=0;
    for(int i=mid-1;i>=beg;i--)
    {
        add+=arr[i];
        if(add>lMax)
            lMax=add;
    }
    add=0;
    for(int i=mid+1;i<=end;i++)
    {
        add+=arr[i];
        if(add>rMax)
            rMax=add;
    }
    int ret=arr[mid];
    if(lMax>0)
        ret+=lMax;
    if(rMax>0)
        ret+=rMax;
    return ret;
}

int maxSubarr(vector<int> &arr,int beg,int end)
{
    int mid=(beg+end)/2;
    int left=arr[beg];
    if(beg<mid-1)
        left=maxSubarr(arr,beg,mid-1);
    int right=arr[end];
    if((mid+1)<end)
        right=maxSubarr(arr,mid+1,end);
    int cross=findCross(arr,beg,end);

    int ret=right>left?right:left;
    return ret>cross?ret:cross;
}

int maxSubarr(vector<int> &arr)
{
    int add=0;
    int max=INT32_MIN;
    for(int i=0;i<arr.size();i++)
    {
        add+=arr[i];
        if(add>max)
            max=add;
        if(add<0)
            add=0;
    }
    return max;
}

int main()
{
    vector<int> arr{13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    cout<<maxSubarr(arr,0,arr.size()-1)<<endl;
    cout<<maxSubarr(arr)<<endl;

    return 0;
}