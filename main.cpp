/*
 * 深度优先搜索
 * 深度优先搜索可以探查有向图中是否存在环，条件是产生后向边
 * 深度优先搜索也可以产生有向无环图的拓扑排序，拓扑排序顺序与节点完成的时间相反
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"
#include "unordered_map"
#include "unordered_set"
#include "map"
#include "bitset"
#include "queue"

using namespace std;

/*
 * -1 -> white
 *  0 -> gray
 *  1 -> black
 */
struct Node
{
    Node(int v):val(v),p(NULL),color(-1),d(INT32_MAX),f(INT32_MAX){}
    int val;
    Node *p;
    int color;
    int d;
    int f;
};

void DFS_visit(unordered_map<Node*,unordered_set<Node*>> &m,Node *curr,int &time)
{
    ++time;
    curr->d=time;
    curr->color=0;
    for(auto it:m[curr])
    {
        if(it->color==-1)
        {
            DFS_visit(m,it,time);
        }
        else if(it->color==0)
        {
            //有后向边，有向图中 产生环
            cout<<"circle"<<endl;
            cout<<curr->val<<"->"<<it->val<<endl;
        }
    }
    curr->color=1;
    curr->f=time;
}

void DFS(unordered_map<Node*,unordered_set<Node*>> &m)
{
    int time=0;
    for(auto it:m)
    {
        if(it.first->color==-1)
        {
            DFS_visit(m,it.first,time);
        }
        else if(it.first->color==0)
        {
            //有后向边，有向图中产生环
            cout<<"circle"<<endl;
            cout<<it.first->val<<endl;
        }
    }
}

//从一个二维数组初始化一个图，二维数组中每一行的第一个元素代表一个节点，后边的元素代表与该节点相连的节点
void init_BFS(vector<vector<int>> &l)
{
    //最终将图保存在m中，可以看成是邻接链表法
    unordered_map<Node*,unordered_set<Node*>> m;

    //先为每个节点构造一个对象
    vector<Node*> table;
    for(int i=0;i<l.size();++i)
    {
        Node *tmp=new Node(l[i][0]);
        table.push_back(tmp);
    }

    for(int i=0;i<l.size();++i)
    {
        for(int j=1;j<l[i].size();++j)
        {
            m[table[i]].insert(table[l[i][j]-1]);
        }
    }
    DFS(m);
}


int main()
{
    /*
     * 1|->2->4
     * 2|->5
     * 3|->5
     * 4|->2
     * 5|->4
     * 6|->6
     */
    vector<vector<int>> l{{1,2,4},{2,5},{3,5},{4,2},{5,4},{6,6}};
    init_BFS(l);
    return 0;
}