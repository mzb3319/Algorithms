/*
 * 基数排序
 * 方法：把数字从最低位开始按位排序，基数排序需要基于一种稳定的排序方法
 */
#include "iostream"
#include "vector"

using namespace std;

void counting_sort(vector<string> &arr,int k,int index)
{
    //计数数组
    vector<int> count(k+1,0);
    //存放排序后的数组
    vector<string> tmpArr(arr.size());
    //计数
    for(const string &str:arr)
    {
        char c='0';
        if(index<str.size())
            c=str[str.size()-index-1];
        count[c-'0']++;
    }
    //累加
    for(int i=1;i<count.size();++i)
        count[i]+=count[i-1];
    //对数组进行排序,需要注意的是数组索引从0开始，这里每个元素的计数至少是 1
    for(int i=arr.size()-1;i>=0;--i)
    {
        char c='0';
        if(index<arr[i].size())
            c=arr[i][arr[i].size()-index-1];
        tmpArr[count[c-'0']-1]=arr[i];
        count[c-'0']--;
    }
    for(int i=0;i<arr.size();++i)
        arr[i]=tmpArr[i];
}

void radix_sort(vector<string> &arr)
{
    int index=0;
    for(const string &str:arr)
        if(str.size()>index)
            index=str.size();
    for(int i=0;i<index;++i)
        counting_sort(arr,9,i);
}

int main()
{
    vector<string> arr{"1001","378","576","344","987"};
    cout<<"arr:"<<endl;
    for(auto &str:arr)
        cout<<str<<' ';
    cout<<endl<<"sorted arr:"<<endl;
    radix_sort(arr);
    for(auto &str:arr)
        cout<<str<<' ';
    cout<<endl;

    return 0;
}