/*
 * 创建二叉搜索树
 * 二叉树的中序遍历、前序遍历、后序遍历（包括递归版本和循环版本）
 * 查询二叉树的最大、最小值、任意值是否在树中
 * 向二叉树中增加一个节点
 * 删除二叉树的节点没有写，看《算法导论》p165吧，需要用到父节点，刚开始没有这个属性，再加太麻烦。。。
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"

using namespace std;

struct bTree
{
    bTree(int a):val(a),left(NULL),right(NULL)
    {}
    int val;
    bTree *left;
    bTree *right;
};

bTree *build_bTree_core(vector<int>&,int,int);

bTree *build_bTree(vector<int> &arr)
{
    sort(arr.begin(),arr.end());
    return build_bTree_core(arr,0,arr.size()-1);
}
bTree *build_bTree_core(vector<int> &arr,int beg,int end)
{
    if(beg>end)
        return NULL;
    int mid=(beg+end)/2;
    bTree *head=new bTree(arr[mid]);
    head->left=build_bTree_core(arr,beg,mid-1);
    head->right=build_bTree_core(arr,mid+1,end);
    return head;
}
void destroy_bTree(bTree *head)
{
    if(!head)
        return;
    destroy_bTree(head->left);
    destroy_bTree(head->right);
    delete head;
}

//中序遍历
void inorder_tree_walk(bTree *head)
{
    if(!head)
        return;
    inorder_tree_walk(head->left);
    cout<<head->val<<' ';
    inorder_tree_walk(head->right);
}
//中序遍历-循环版
void inorder_tree_walk2(bTree *head)
{
    if(!head)
        return;
    vector<bTree*> table;
    while(head!=NULL||!table.empty())
    {
        if(head)
        {
            table.push_back(head);
            head=head->left;
        }
        else
        {
            head=table.back();
            table.pop_back();
            cout<<head->val<<' ';
            head=head->right;
        }
    }
}
//前序遍历
void preorder_tree_walk(bTree *head)
{
    if(!head)
        return;
    cout<<head->val<<' ';
    preorder_tree_walk(head->left);
    preorder_tree_walk(head->right);
}
//前序遍历-循环版
void preorder_tree_walk2(bTree *head)
{
    if(!head)
        return;
    vector<bTree*> table;
    while(head!=NULL||!table.empty())
    {
        cout<<head->val<<' ';
        if(head->left)
        {
            if(head->right)
                table.push_back(head->right);
            head=head->left;
        }
        else
        {
            if(head->right)
            {
                head=head->right;
            }
            else
            {
                if(table.empty())
                    break;
                head=table.back();
                table.pop_back();
            }
        }
    }
}
//后序遍历
void postorder_tree_walk(bTree *head)
{
    if(!head)
        return;
    postorder_tree_walk(head->left);
    postorder_tree_walk(head->right);
    cout<<head->val<<' ';
}
//后序遍历-循环版
void postorder_tree_walk2(bTree *head)
{
    if(!head)
        return;
    vector<bool> status;
    vector<bTree*> table;
    while(head||!table.empty())
    {
        if(head)
        {
            table.push_back(head);
            status.push_back(false);
            head=head->left;
        }
        else
        {
            if(status.back())
            {
                cout<<table.back()->val<<' ';
                table.pop_back();
                status.pop_back();
            }
            else
            {
                head=table.back()->right;
                status.back()=true;
            }
        }
    }

}
//宽度遍历
void bs_tree_walk(bTree *head)
{
    if(!head)
        return;
    deque<bTree*> dq;
    dq.push_back(head);
    while(!dq.empty())
    {
        bTree *tmp=dq.front();
        dq.pop_front();
        cout<<tmp->val<<' ';
        if(tmp->left)
            dq.push_back(tmp->left);
        if(tmp->right)
            dq.push_back(tmp->right);
    }
}

bTree *bTree_search(bTree *head,int k)
{
    if(!head)
        return NULL;
    if(k>head->val)
        return bTree_search(head->right,k);
    else if(k<head->val)
        return bTree_search(head->left,k);
    return head;
}

bTree *max(bTree *head)
{
    if(!head)
        return NULL;
    while(head->right)
        head=head->right;
    return head;
}
bTree *min(bTree *head)
{
    if(!head)
        return NULL;
    while(head->left)
        head=head->left;
    return head;
}
bTree *insert(bTree *head,int k)
{
    bTree *root=head,*tmp=NULL;
    while(head)
    {
        tmp=head;
        if(k>head->val)
            head=head->right;
        else
            head=head->left;
    }
    bTree *node=new bTree(k);
    if(tmp)
    {
        k>tmp->val?tmp->right=node:tmp->left=node;
    }
    else
    {
        root=node;
    }
    return root;
}

int main()
{
    vector<int> arr{2,1,4,5,6,3,9,11,13};
    bTree *tree=build_bTree(arr);
    tree=insert(tree,-1);

    cout<<"中序遍历:";
    inorder_tree_walk2(tree);
    cout<<endl<<"中序遍历:";
    inorder_tree_walk(tree);

    cout<<endl<<"前序遍历:";
    preorder_tree_walk2(tree);
    cout<<endl<<"前序遍历:";
    preorder_tree_walk(tree);

    cout<<endl<<"后序遍历:";
    postorder_tree_walk2(tree);
    cout<<endl<<"后序遍历:";
    postorder_tree_walk(tree);

    cout<<endl<<"宽度遍历:";
    bs_tree_walk(tree);
    cout<<endl;

    auto t=bTree_search(tree,8);
    cout<<"find ";
    t?cout<<t->val<<endl:cout<<"no"<<endl;

    t=max(tree);
    cout<<"max ";
    t?cout<<t->val<<endl:cout<<"err"<<endl;

    t=min(tree);
    cout<<"min ";
    t?cout<<t->val<<endl:cout<<"err"<<endl;

    destroy_bTree(tree);
    return 0;
}
