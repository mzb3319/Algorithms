/*
 * 霍夫曼编码(变长编码)
 * 使用贪心算法，先文本中出现次数多的字符给较短的编码，出现次数少的字符用较长的编码，编码过程使用贪心算法
 *
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

struct Node
{
    Node(int v):val(v),p(NULL),color(false),d(INT32_MAX){}
    int val;
    Node *p;
    bool color;
    int d;
};

void BFS(Node* node,unordered_map<Node*,unordered_set<Node*>> &m)
{
    if(node==NULL)
        return;
    deque<Node*> q{node};
    node->color=true;
    node->d=0;

    int d=0;
    while(!q.empty())
    {
        ++d;

        Node *n=q.front();
        q.pop_front();

        for(Node *it:m[n])
        {
            //已经探查过的节点直接跳过
            if(it->color)
                continue;
            it->color=true;
            it->p=n;
            it->d=d;
            q.push_back(it);
        }
    }
}
void printBFS(unordered_map<Node*,unordered_set<Node*>> &m,Node *a,Node *b);

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
    BFS(table[2],m);
    printBFS(m,table[2],table[4]);
}

//输出从一个节点a到节点b的最短路径，上边已经为每个节点的p属性赋值，p属性指向BFS树的父节点，所以只要递归的输出
void printBFS(unordered_map<Node*,unordered_set<Node*>> &m,Node *a,Node *b)
{
    if(a==b)
        cout<<b->val;
    else if(b->p==NULL)
        cout<<"no such path"<<endl;
    else
    {
        printBFS(m,a,b->p);
        cout<<"->"<<b->val;
    }
}

int main()
{
    /*
     * 1|->2->5
     * 2|->1->5->3->4
     * 3|->2->4
     * 4|->2->5->3
     * 5|->4->1->2
     */
    vector<vector<int>> l{{1,2,5},{2,1,5,3,4},{3,2,4},{4,2,5,3},{5,4,1,2}};
    init_BFS(l);
    return 0;
}