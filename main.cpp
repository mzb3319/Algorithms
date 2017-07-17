#include <iostream>
#include <vector>

using namespace std;

inline int LEFT(int i)
{
    return (i<<1)+1;
}
inline int RIGHT(int i)
{
    return (i+1)<<1;
}
inline int PARENT(int i)
{
    return (i-1)>>1;
}

void swap(vector<int> &arr,int a,int b)
{
    int tmp=arr[a];
    arr[a]=arr[b];
    arr[b]=tmp;
}

//维护堆的性质
void max_heapify(vector<int> &arr,int i)
{
    int l=LEFT(i);
    int r=RIGHT(i);

    int max=i;
    if(l<arr.size()&&arr[l]>arr[i])
        max=l;
    if(r<arr.size()&&arr[r]>arr[max])
        max=r;
    if(max!=i)
    {
        swap(arr,i,max);
        max_heapify(arr,max);
    }
}

//创建堆
void build_max_heap(vector<int> &arr)
{
    int len=arr.size();
    for(int i=(len>>1)-1;i>=0;i--)
    {
        max_heapify(arr,i);
    }
}

//堆排序算法，通过缩小堆的大小构建排序算法
vector<int> heap_sort(vector<int> &arr)
{
    build_max_heap(arr);
    vector<int> ret;
    for(int i=arr.size()-1;i>=0;--i)
    {
        swap(arr,i,0);
        ret.push_back(arr[i]);
        arr.pop_back();
        max_heapify(arr,0);
    }
    return ret;
}

//优先队列
//返回队列中的最大值
int heap_maximum(vector<int> &arr)
{
    return arr.front();
}
//删除最大元素并返回该值
int heap_extract_max(vector<int> &arr)
{
    int ret=arr.front();
    arr.front()=arr.back();
    arr.pop_back();
    max_heapify(arr,0);
    return ret;
}
//提升关键字 i 的数值到 k
void heap_increase_key(vector<int> &arr,int i,int k)
{
    if(arr[i]>=k)
        return;
    arr[i]=k;
    while(i>0&&arr[PARENT(i)]<arr[i])
    {
        swap(arr,i,PARENT(i));
        i=PARENT(i);
    }
}
//插入一个新节点到堆中
void max_heap_insert(vector<int> &arr,int key)
{
    arr.push_back(INT32_MIN);
    int i=arr.size()-1;
    heap_increase_key(arr,i,key);
}

int main()
{
    vector<int> arr{1,2,3,4,5,6,7};
    build_max_heap(arr);
    cout<<"build heap:"<<endl;
    for(int n:arr)
        cout<<n<<' ';
    cout<<endl<<"heap sort:"<<endl;
    arr=heap_sort(arr);
    for(int n:arr)
        cout<<n<<' ';
    cout<<endl<<"返回最大值:";
    build_max_heap(arr);
    cout<<heap_maximum(arr);
    cout<<endl<<"返回最大值并从堆中删除最大值:";
    cout<<heap_extract_max(arr)<<endl;
    for(int n:arr)
        cout<<n<<' ';
    cout<<endl<<"插入一个新值到堆中:";
    max_heap_insert(arr,99);
    for(int n:arr)
        cout<<n<<' ';
    cout<<endl<<"heap sort:"<<endl;
    arr=heap_sort(arr);
    for(int n:arr)
        cout<<n<<' ';
}
