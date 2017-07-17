/*
 * 归并排序
 * 输入：n个数字
 * 输出：n个数字的有序序列
 * 非原址排序
 * 方法:把数组分成前后两部分，如果这两部分是排好序的，把这两部分合并成一个数组，合并过程中分别从两部分中依次选择较小的数字，则合并完成后的数组是严格排序的
 * 递归的调用该过程，就能完成排序的过程
 */

#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &arr,int beg1,int end1,int beg2,int end2)
{
    vector<int> larr(arr.begin()+beg1,arr.begin()+end1+1),
                rarr(arr.begin()+beg2,arr.begin()+end2+1);
    larr.push_back(INT32_MAX);
    rarr.push_back(INT32_MAX);
    int index1=0;
    int index2=0;
    for(int i=beg1;i<=end2;i++)
    {
        if(larr[index1]>rarr[index2])
        {
            arr[i]=rarr[index2];
            index2++;
        }
        else
        {
            arr[i]=larr[index1];
            index1++;
        }
    }
}

void merge_sort(vector<int> &arr,int beg,int end)
{
    if(beg>=end)
        return;
    int mid=(beg+end)/2;
    merge_sort(arr,beg,mid);
    merge_sort(arr,mid+1,end);
    merge(arr,beg,mid,mid+1,end);
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
    merge_sort(arr,0,arr.size()-1);
    for(int n:arr)
    {
        cout<<n<<' ';
    }
    cout<<endl;

    return 0;
}