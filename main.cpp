/*
 * 最长公共子串
 *
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"
#include "unordered_map"

using namespace std;

int lcs_length(string &a,string &b,vector<vector<int>> &map)
{
    if(a.empty()||b.empty())
        return 0;
    //建表
    vector<vector<int>> table(a.length()+1,vector<int>(b.length()+1,0));
    for(int i=0;i<a.length();++i)
    {
        for(int j=0;j<b.length();++j)
        {
            if(a[i]==b[j])//相等用左上角的值加1
            {
                table[i+1][j+1]=table[i][j]+1;
                map[i][j]=0;
            }
                //否则用左边和上边较大的值
            else if(table[i+1][j]>=table[i][j+1])
            {
                table[i+1][j+1]=table[i+1][j];
                map[i][j]=-1;
            }
            else
            {
                table[i+1][j+1]=table[i][j+1];
                map[i][j]=1;
            }
        }
    }
    return table.back().back();
}

void lcs_print(string &a,vector<vector<int>> &map)
{
    if(map.empty()||map.front().empty())
        return;
    vector<char> print;

    //从右下角开始，如果值为0，则相等，接着向左上方移动
    //如果等于-1，向左边移动，如果等于1，向上移动
    int i=map.size()-1,j=map.front().size()-1;
    while(i>=0&&j>=0)
    {
        if(map[i][j]==0)
        {
            print.push_back(a[i]);
            --i;
            --j;
        }
        else if(map[i][j]==-1)
        {
            --j;
        }
        else
        {
            --i;
        }
    }
    for(auto beg=print.rbegin();beg!=print.rend();++beg)
        cout<<*beg<<' ';
    cout<<endl;
}

int main()
{
    string a="ABCBDAB";
    string b="BDCABA";
    vector<vector<int>> map(a.length(),vector<int>(b.length(),0));
    cout<<lcs_length(a,b,map)<<endl;
    lcs_print(a,map);
    return 0;
}
