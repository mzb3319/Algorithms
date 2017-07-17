/*
 * 插入排序
 * 输入：n个数的一个序列
 * 输出：输入序列的一个排列
 *
 * 方法：原址排序，每次拿出一个数字，与该数字之前的每一个数字进行比较，如果小于前边的数字，就交换这两个数字
 */
#include <iostream>
#include <vector>

using namespace std;

void insert_sort(vector<int> &arr)
{
    if(arr.empty())
        return;
    for(int i=1;i<arr.size();i++)
    {
        int curr=i;
        int index=i-1;
        while(index>=0&&arr[curr]<arr[index])
        {
            int tmp=arr[curr];
            arr[curr]=arr[index];
            arr[index]=tmp;

            curr=index;
            index--;
        }
    }
}

int main() {
    std::cout << "插入排序" << std::endl;
    vector<int> arr1{2,1,4,-2,4,5,12,55,12,45};

    cout<<"arr1:"<<endl;
    for(int n:arr1)
    {
        cout<<n<<' ';
    }
    cout<<endl;
    insert_sort(arr1);
    cout<<"sorted arr1:"<<endl;
    for(int n:arr1)
    {
        cout<<n<<' ';
    }

    return 0;
}