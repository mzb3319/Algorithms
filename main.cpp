/*
 * 矩阵链乘法问题
 * 矩阵相乘过程中，适当调整计算顺序（通过括号化实现）可以大大降低计算量
 * 此算法中的矩阵通过数组表示，如{1,2,3,4,5}表示矩阵A1,A2,A3,A4,其中数组的维度以此为1X2,2X3,3X4,4X5
 *
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"
#include "unordered_map"

using namespace std;

int matrix_chain_order(vector<int> &matrix,vector<vector<int>> &s)
{
    int n=matrix.size();
    vector<vector<int>> table(n-1,vector<int>(n-1,0));
    for(int i=2;i<=n;++i)//i->矩阵链的长度，比如矩阵链总长度为10，我们先将矩阵两两计算，再三个三个计算，依次类推
    {
        for(int j=0;j<n-i;++j)//当矩阵链长度为i时，从第一个矩阵开始，依次计算长度为i的矩阵链的最小计算量
        {
            int curr=INT32_MAX;
            int k=j;
            for(;k<j+i-1;++k)//当矩阵链长度为i时，第k个矩阵处加括号,k取值从当前矩阵链的第一个到倒数第二个，如(A)(BCD),或(ABC)(D)
            {
                //确定k后，计算当前矩阵链的计算量，计算量是k前后两个子矩阵链的计算量加上两个子链计算完后得到的两个数组相乘的计算量
                int tmp=table[j][k]+table[k+1][j+i-1]+matrix[j]*matrix[k+1]*matrix[j+i];
                if(tmp<curr)
                {
                    curr=tmp;
                    s[j][j+i-1]=k;
                }
            }
            table[j][j+i-1]=curr;
        }
    }
    return table[0].back();
}
void print_optimal_parens(vector<vector<int>> &s,int i,int j)
{
    if(i==j)
        cout<<"A"<<i+1;
    else
    {
        cout<<'(';
        print_optimal_parens(s,i,s[i][j]);
        print_optimal_parens(s,s[i][j]+1,j);
        cout<<')';
    }
}

int main()
{
    vector<int> matrix{30,35,15,5,10,20,25};
    vector<vector<int>> s(matrix.size()-1,vector<int>(matrix.size()-1,0));
    cout<<matrix_chain_order(matrix,s)<<endl;
    print_optimal_parens(s,0,matrix.size()-2);
    return 0;
}
