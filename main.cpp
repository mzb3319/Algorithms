/*
 * 计数排序
 * 方法：假设数组中的元素都是在 0-k 之间，那么创建一个大小为 k 的数组 count 用来计数原数组中元素出现的个数。
 * 非原址排序，需要额外的空间
 */
#include "iostream"
#include "vector"

using namespace std;

void counting_sort(vector<int> &arr,int k)
{
    //计数数组
    vector<int> count(k+1,0);
    //存放排序后的数组
    vector<int> tmpArr(arr.size());
    //计数
    for(int n:arr)
        count[n]++;
    //累加
    for(int i=1;i<count.size();++i)
        count[i]+=count[i-1];
    //对数组进行排序,需要注意的是数组索引从0开始，这里每个元素的计数至少是 1
    for(int i=arr.size()-1;i>=0;--i)
    {
        tmpArr[count[arr[i]]-1]=arr[i];
        count[arr[i]]--;
    }
    for(int i=0;i<arr.size();++i)
        arr[i]=tmpArr[i];
}

int main()
{
    vector<int> arr{9,8,7,6,5,3,3,4,1,8,9,4,4,3,2,1,0};
    cout<<"arr:"<<endl;
    for(int n:arr)
        cout<<n<<' ';
    cout<<endl<<"sorted arr:"<<endl;
    counting_sort(arr,9);
    for(int n:arr)
        cout<<n<<' ';
    cout<<endl;

    return 0;
}