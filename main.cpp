/*
 * 随机排列一个数组
 * 输入：n个数字的序列
 * 输出：输出随机排列后的数组
 *
 * 方法1:创建一个优先级数组，此优先级数组中的数字随机生成，然后根据此优先级数组对原数组进行排序
 * 方法2:讲原数组中的每一个数字与随机位置的数字进行交换，此方法是原址的，选这个吧
 *
 */

#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <cassert>

using namespace std;


void random_sort(vector<int> &arr)
{
    for(int i=0;i<arr.size();i++)
    {
        int r=random()%arr.size();
        int tmp=arr[i];
        arr[i]=arr[r];
        arr[r]=tmp;
    }
}

bool check(vector<int> &arr)
{
    unordered_map<int,int> table;
    for(int n:arr)
    {
        table[n]++;
    }
    random_sort(arr);
    for(int n:arr)
    {
        table[n]--;
    }
    for(auto i:table)
    {
        if(i.second!=0)
            return false;
    }
    return true;
}

int main()
{
    vector<int> arr{13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    assert(check(arr));

    return 0;
}