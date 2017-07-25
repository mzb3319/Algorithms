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
#include "map"
#include "bitset"
#include "queue"

using namespace std;

//用来辅助编码,构建编码树
struct node
{
    node()= default;
    node(char a):c(a),left(NULL),right(NULL){}
    node *left;
    node *right;
    char c;
};

//用来创建优先队列
class l
{
public:
    bool operator()(pair<int,node*> &a,pair<int,node*> &b)
    {
        return a.first>b.first;
    }
};

//获取编码树
node* getCode(string &str)
{
    unordered_map<char,int> table;
    //统计字符出现次数
    for(char c:str)
        table[c]++;
    //创建优先队列
    priority_queue<pair<int,node*>,vector<pair<int,node*>>,l> pq;
    for(const auto &it:table)
    {
        node *tmp=new node(it.first);
        pq.push({it.second,tmp});
    }
    //每次从队列中取出前两个对象，将这两个对象合并成一个子树，然后把子树的跟节点添加到队列中，排序的key是子树子节点的统计和
    while(pq.size()>1)
    {
        pair<int,node*> a=pq.top();
        pq.pop();
        pair<int,node*> b=pq.top();
        pq.pop();
        node *tmp=new node;
        tmp->left=a.second;
        tmp->right=b.second;
        pq.push({a.first+b.first,tmp});
    }
    //当队列中只剩下一个节点时，形成一棵完整的编码树
    return pq.top().second;
}
//辅助编码，先从编码树中找到字符对应的编码
//相当于遍历树，遍历到达叶节点时就是要找的字符，遍历的路径就是字符对应的编码
void encode_help(node* head,string &ec,unordered_map<char,string> &table)
{
    if(head==NULL)
        return;
    //到达叶节点，把字符和对应的编码插入到table中
    if(head->left==NULL&&head->right==NULL)
    {
        table.insert({head->c,ec});
        return;
    }
    //先左子节点
    ec.push_back('0');
    encode_help(head->left,ec,table);
    ec.pop_back();
    //后右子节点
    ec.push_back('1');
    encode_help(head->right,ec,table);
    ec.pop_back();
}
//编码函数,将输入的字符串编码成对应的码串，这里为了方便把码串也用字符串表示了
string encode(string &str,node* code)
{
    unordered_map<char,string> table;
    string ec;
    //获取编码树
    encode_help(code,ec,table);
    string ret;
    for(char c:str)
    {
        ret+=table[c];
    }
    return ret;
};
//解码过程,通过每一个字符控制树的遍历过程，0时树向左节点移动，1时树向有节点移动，当到达叶节点时解码出一个字符，将树重新移动到根节点
string decode(string &str,node *code)
{
    string ret;
    node *curr=code;
    for(char c:str)
    {
        if(c=='0')
            curr=curr->left;
        else if(c=='1')
            curr=curr->right;
        if(curr->left==NULL&&curr->right==NULL)
        {
            ret+=curr->c;
            curr=code;
        }
    }
    return ret;
}

int main()
{
    string str=string(5,'f')+string(9,'e')+string(12,'c')+string(13,'b')+string(16,'d')+string(45,'a');
    node* code=getCode(str);
    string ec=encode(str,code);
    cout<<ec<<endl;
    string dc=decode(ec,code);
    cout<<dc<<endl;
    unordered_map<char,int> table;
    for(char c:dc)
        table[c]++;
    for(auto &it:table)
        cout<<it.first<<':'<<it.second<<' ';
    cout<<endl;
    return 0;
}
