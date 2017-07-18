/*
 * 求最大值最小值；通过快排完成选择问题
 */
#include "iostream"
#include "vector"

using namespace std;

struct mm
{
    int max;
    int min;
};
mm max_min(vector<int> &arr)
{
    int index=arr.size();
    if(!index)
        return {};
    if(index==1)
        return {arr.front(),arr.front()};
    mm ret;
    if(index&1)
    {
        ret.max=ret.min=arr[0];
        index=2;
    }
    else
    {
        arr[0]>arr[1]?ret.max=arr[0],ret.min=arr[1]:ret.max=arr[1],ret.min=arr[0];
        index=3;
    }
    for(;index<arr.size();index+=2)
    {
        int max,min;
        arr[index]>arr[index-1]?max=arr[index],min=arr[index-1]:max=arr[index-1],min=arr[index];
        if(ret.max<max)
            ret.max=max;
        if(ret.min>min)
            ret.min=min;
    }
    return ret;
}

void swap(vector<int> &arr,int a,int b)
{
    int tmp=arr[a];
    arr[a]=arr[b];
    arr[b]=tmp;
}

int partition(vector<int> &arr,int beg,int end)
{
    if(beg>end)
        return beg==end?beg:-1;
    int ri=beg+rand()%(end-beg+1);
    swap(arr,ri,end);
    int r=beg-1;
    for(int i=beg;i<=end;++i)
    {
        if(arr[i]<=arr[end])
            swap(arr,i,++r);
    }
    return r;
}

bool select(vector<int> &arr,int beg,int end,int k)
{
    if(beg>end)
        return false;
    int r=partition(arr,beg,end);
    if(r==-1)
        return false;
    if(arr[r]>k)
        return select(arr,beg,r-1,k);
    else if(arr[r]<k)
        return select(arr,r+1,end,k);
    return true;
}
int main()
{
    vector<int> arr{1,2,6,5,-1,4,-7,2,44,1,99};
    auto r=max_min(arr);
    cout<<r.max<<" "<<r.min<<endl;
    vector<int> find{7,6,5,4,3,2,1};
    cout<<select(find,0,find.size()-1,7)<<endl;
    return 0;
}