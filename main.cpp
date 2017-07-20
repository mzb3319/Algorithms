/*
 * 钢条切割问题
 * 包含自顶向下和自底向上方法
 * 自顶向下方法带备忘，每次求出一个具体的解后就存起来，后边在遇到相同的问题直接查表
 * 自底向上方法需要找到填表的规律，基本分析思路是每次从钢条左边切下一段，这一段的长度是 j，j<给定价格中的最大长度 && j<当前迭代求解的钢条总长度
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"
#include "unordered_map"

using namespace std;

int mem_cut_rod(vector<int> &price,int n,unordered_map<int,int> &table)
{
    if(n<=0)
        return 0;
    auto f=table.find(n);
    if(f!=table.end())
        return f->second;
    int ret=0;
    for(int i=1;i<=price.size()&&i<=n;i++)
    {
        ret=max(price[i-1]+mem_cut_rod(price,n-i,table),ret);
    }
    return ret;
}
int bottom_up_cut_rod(vector<int> &price,int n)
{
    vector<int> table{0};
    for(int i=1;i<=n;i++)
    {
        table.push_back(0);
        int ret=INT32_MIN;
        for(int j=1;j<=price.size()&&j<=i;++j)
        {
            ret=max(ret,price[j-1]+table[i-j]);
        }
        table.back()=ret;
    }
    return table.back();
}

int main()
{
    vector<int> price{1,5,8,9,10,17,17,20,24,30};
    unordered_map<int,int> table;
    cout<<mem_cut_rod(price,12,table)<<endl;
    cout<<bottom_up_cut_rod(price,12)<<endl;
    return 0;
}