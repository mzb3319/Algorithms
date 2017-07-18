/*
 * 快速排序
 * 方法：在数组中随机选一个元素，与最后一个元素进行交换（这样可以做到随机化），然后以最后一个元素的值 k 作为标准，遍历数组，遍历过程中存储一个额外的指针
 * r 用来指向最后一个比 k 小的元素，r 初始化为比数组首元素索引小 1 （beg-1），对每一个元素，如果 <=k ，则先把 r 增加1，再把 r 所在的值与当前元素的值交换
 * 是原址排序
 */
#include "iostream"
#include "vector"

using namespace std;

//交换数组中的两个元素
void swap(vector<int> &arr,int a,int b)
{
    if(a==b)
        return;
    arr[a]+=arr[b];
    arr[b]=arr[a]-arr[b];
    arr[a]=arr[a]-arr[b];
}

int partition(vector<int> &arr,int beg,int end)
{
    if(beg>=end)
        return beg;

    //用来做随机化处理
    int rp=beg+rand()%(end-beg+1);
    swap(arr,rp,end);

    int r=beg-1;
    for(int i=beg;i<=end;++i)
    {
        if(arr[i]<=arr[end])
        {
            swap(arr,++r,i);
        }
    }
    return r;
}

void quick_sort(vector<int> &arr,int beg,int end)
{
    if(beg>=end)
        return;
    int r=partition(arr,beg,end);
    quick_sort(arr,beg,r-1);
    quick_sort(arr,r+1,end);
}

int main()
{
    vector<int> arr{2,1,4,9,3,5,1,3,5};
    cout<<"arr:"<<endl;
    for(int n:arr)
        cout<<n<<' ';
    cout<<endl<<"sorted arr:"<<endl;
    quick_sort(arr,0,arr.size()-1);
    for(int n:arr)
    {
        cout<<n<<' ';
    }
    cout<<endl;
    return 0;
}