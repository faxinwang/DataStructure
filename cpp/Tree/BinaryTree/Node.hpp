#ifndef _Node_
#define _Node_

NamespaceBegin

#include "../../Queue/Queue.hpp"
#include "../../util/require.hpp"
#define stature(rt) ((rt)? rt->height : 0)
//计算结点的高度, 叶子结点的高度定义为1, 空结点的高度定义为0


/**
 *  二叉树结点结构体, 封装与结点有关的属性和操作
 * 
 * 成员变量:
 * data : 保存数据
 * height: 该结点在树中的高度
 * LC : 左孩子指针
 * RC : 右孩子指针
 * parent: 父结点指针
 * 
 * 
 * 方法:
 * Size() : 返回以该结点为子树的结点的个数
 * NextNode(): 返回中序遍历顺序的下一个结点
 * PrevNode(): 返回中序遍历顺序的上一个结点
 * LeftMostNode() : 返回以当前结点为根的子树的最左边的那个结点
 * RightMostNode(): 返回以当前结点为根的子树的最右边的那个结点
 * UpdateHeight() : 更新当前结点的高度
 * UpdateHeightAbove(): 更新当前结点及其所有祖先结点的高度
 * InsertLeftChild()  : 将元素作为该结点的左孩子插入
 * InsertRightChild() : 将元素作为该结点的右孩子插入
 * RemoveLeftChild()  : 删除左孩子(子树)
 * RemoveRightChild() : 删除右孩子(子树)
 * Detach() : 与父结点分离
 * isLC() : 判断该结点是否是其父亲的左孩子
 * isRC() : 判断该结点是否是其父亲的右孩子
 * 
 * static方法:
 * RotateAt() : 在某个结点处旋转子树
 * BuildFromPreInOrder() : 根据先序序列和中序序列构建二叉树
 * BuildFromPostInOrder(): 根据后序序列和中序序列构建二叉树
 */


template<typename T>
class Node
{
public: //成员变量
    T data;
    int height;
    Node *LC;
    Node *RC;
    Node *parent;

private: //私有静态方法
    
    //删除该结点及其所有子结点
    static void Clear(Node*& rt)
    {
        if(rt)
        {
            if(rt->LC) Clear(rt->LC);
            if(rt->RC) Clear(rt->RC);
            delete rt;
            rt=0;
        }
    }


     /**旋转以参数rt为根结点的子树
     * 1.用临时变量保存左子树.
     * 2.让左孩子指针指向右子树
     * 3.让右孩子指针指向左子树(临时变量)
     * 4.递归旋转左右子树
     */
    static void RotateAt(Node<T>* rt, bool applyToChild=true)
    {
        if(rt)
        {
            std::swap(rt->LC, rt->RC);
            if(applyToChild)
            {
                Queue<Node<T>*> Q;
                if(rt->LC) Q.push(rt->LC);
                if(rt->RC) Q.push(rt->RC);
                while(!Q.empty())
                {
                    rt = Q.pop();
                    std::swap(rt->LC, rt->RC);
                    if(rt->LC) Q.push(rt->LC);
                    if(rt->RC) Q.push(rt->RC);
                }
            }
        }
    }


public: //公有静态方法


     /**根据前序和中序序列恢复二叉树
     * 1.前序序列的第0个元素即为根结点
     * 2.通过根结点寻找中序序列中根结点的位置t
     * 3.用前序序列的子序列[1,1+t]和中序序列的子序列[0,t-1]递归构建左子树
     * 4.用前序序列的子序列[2+t]
     * 
     * 前序序列:[root, [left child sequence], [right child sequence]]
     *           0,    1                  t,  1+t                n-1
     * 中序序列:[[left child sequence], root, [right child sequence]]
     *           0                 t-1 ,  t,  1+t                n-1
     * 左子树长度: t
     * 右子树长度: n-1-t
     */
    static Node<T>* BuildFromPreInOrder(const T* pre,const  T* in, int n, Node<T>* parent=NULL)
    {
        if(n <= 0) return 0;
        Node<T>* root = new Node<T>(pre[0], parent);
        int t = 0;
        while(pre[0] != in[t] && t < n) ++t;
        root->LC = BuildFromPreInOrder(pre+1, in, t, root);
        root->RC = BuildFromPreInOrder(pre+1+t, in+1+t, n-1-t, root);
        root->UpdateHeight();
        return root;
    }

    /**根据中序和后序序列恢复二叉树
     * 1.后序序列的最后一个元素即为根结点
     * 2.通过根结点寻找中序序列中根结点的位置t
     * 3.用后序序列的子序列[0,t-1]和中序序列的子序列[0,t-1]递归构建左子树
     * 4.用后序序列的子序列[t,n-2]和中序序列的子序列[t+1,n-1]递归构建右子树
     * 
     * 后序序列:[[left child sequence], [right child sequence], root]
     *          0                  t-1, t                  n-2,  n-1
     * 中序序列:[[left child sequence], root, [right child sequence]]
     *          0                  t-1,  t ,  t+1                n-1
     * 
     * 左子树长度:t
     * 右子树长度:n-1-t
     */
    static Node<T>* BuildFromPostInOrder(const T* post,const  T* in, int n, Node<T>*parent=NULL)
    {
        if(n <= 0) return 0;
        Node<T>* root = new Node<T>(post[n-1], parent);
        int t=0;
        while(post[n-1] != in[t] && t < n) ++t;
        root->LC = BuildFromPostInOrder(post,in,t, root);
        root->RC = BuildFromPostInOrder(post+t,in+t+1, n-1-t, root);
        root->UpdateHeight();
        return root;
    }

public: //成员方法
    //构造函数
    Node(const T& data=T(), Node* parent=NULL)
        :LC(0)
        ,RC(0)
        ,height(1) //叶结点的高度定义为0
        ,data(data)
        ,parent(parent)
        { 
            if(parent) parent->UpdateHeightAbove();
        }


    /**以当前结点为根的树的size = 1 + 左子树的size + 右子树的size
     * 时间复杂度为O(N).
     */
    int Size()
    {
        int s=1;
        if(LC) s += LC->Size();
        if(RC) s += RC->Size();
        return s;
    }

    /**找到中序遍历意义下的下一个结点,该方法将用于BST中寻找待删除结点的替代结点.
     * 1.如果当前结点有右孩子,则下一个结点出现在当前结点的右子树中,也就是右子树
     *   中值最小的那个结点.
     * 2.如果当前结点没有右孩子,则下一个结点是祖先结点中第一个使得当前结点出现在
     *   其左子树中的祖先结点.
     */
    Node* NextNode()
    {
        Node* next=NULL;
        if(RC) next= RC->LeftMostNode();
        else
        {
            next = this;
            while(next && next->isRC()) next = next->parent; //直到next是某个祖先结点的左孩子
            next = next->parent; //下一个要遍历的就是next的父结点
        }
        return next;
    }

    /**找到中序遍历意义下的上一个结点
     * 1.如果当前结点有左孩子, 则上一个结点是左子树中值最大的一个.
     * 2.如果当前结点没有左孩子,则上一个结点是祖先结点中第一个使得当前结点出现在其右
     *   子树中的祖先结点.
     */
    Node* PrevNode()
    {
        Node* prev=NULL;
        if(LC) prev = LC->RightMostNode();
        else
        {
            prev = this;
            while(prev && prev->isLC() ) prev = prev->parent;
            prev = prev->parent;
        }
        return prev;
    }

    
    inline Node* LeftMostNode()
    {
        Node* pos = this;
        while(pos && pos->LC) pos = pos->LC ;
        return pos;
    }

    inline Node* RightMostNode()
    {
        Node* pos=this;
        while(pos && pos->RC) pos = pos->RC;
        return pos;
    }


    //当前结点的高度为左右子结点的高度中较大的一个+1
    int UpdateHeight() 
    { return  height = 1 + std::max(stature(LC), stature(RC));}
    
    /**从当前结点一直更新到根节点
     * 过程中如果某个结点的高度没有变化,则后面的结点的高度也不会有变化,因此可以提前结束.
    */
    void UpdateHeightAbove()
    {
        Node* p = this;
        while(p)
        {
            int oldHeight = p->height;
            int newHeight = p->UpdateHeight();
            if(oldHeight == newHeight) break;
            p = p->parent;
        }
    }

    /** 1.创建一个新结点并连接到当前结点的左孩子指针
     *     如果左子结点存在,则返回NULL,不进行插入操作
     *  2.然后更新相关结点的高度
     *  e : 作为左子结点的值
     *  return : 返回左子结点的指针
    */
    Node* InsertLeftChild(const T& e)
    {
        if(LC) return NULL;
        LC = new Node(e,this);
        return LC;
    }

    /**1.创建一个新结点并连接到当前结点的右孩子指针
     *   如果右子结点存在 ,则返回NULL,不进行插入操作
     * 2.然后更新相关结点的高度
     * e : 作为右子结点的值
     * return : 新插入的右子结点的指针
    */
    Node* InsertRightChild(const T& e)
    {
        if(RC) return NULL;
        RC = new Node(e, this);
        return RC;
    }

    inline bool isLC(){ return parent && parent->LC==this; }

    inline bool isRC(){ return parent && parent->RC==this; }

    /** 1.删除左子树(注意判断指针是否非空)
     *  2.更新相关结点的高度
     */
    void RemoveLeftChild()
    {
        if(LC)
        {
            Clear(LC);
            UpdateHeightAbove();
        } 
    }
    /** 1.删除右子树(注意判断指针是否非空)
     *  2.更新相关结点的高度
     */
    void RemoveRightChild()
    {
        if(RC)
        {
            Clear(RC);
            UpdateHeightAbove();
        }
    }

    //分离左孩子,返回指向左孩子的指针
    Node* DetachLeftChild()
    {
        Node<T>* child = LC;
        LC=NULL;
        if(child) child->parent = NULL;
        return child;
    }

    //分离右孩子,返回指向右孩子的指针
    Node* DetachRightChild()
    {
        Node* child = RC;
        RC=0;
        if(child) child->parent = NULL;
        return child;
    }

    /**连接左子树
     * 1.如果左子树存在, 则先删除左子树
     * 2.将左孩子指针指向tree
     * 3.如果tree非空,将tree的父指针指向this
     */
    void AttachLeftChild(Node* tree, bool removeIfExist = true)
    {
        if(LC && removeIfExist) RemoveLeftChild();
        LC = tree;
        if(tree) tree->parent = this;
        UpdateHeightAbove();
    }

    /**连接右子树
     * 1.如果右子树存在, 则先删除右子树
     * 2.将右孩子指针指向tree
     * 3.如果tree非空,将tree的父指针指向this
     */
    void AttachRightChild(Node* tree, bool removeIfExist = true)
    {
        if(RC && removeIfExist) RemoveRightChild();
        RC = tree;
        if(tree) tree->parent = this;
        UpdateHeightAbove();
    }

    /**与父结点分离,当父指针不为空时,才进行分离操作
     * 1.将父结点的对应孩子指针置空
     * 2.更新父结点及其祖先结点的高度
     * 3.将当前结点的父结点指针置空
     */
    void Detach()
    {
        if(parent)
        {
            if(this == parent->LC) parent->LC = 0;
            else if(this == parent->RC) parent->RC = 0;
            parent->UpdateHeightAbove();
            parent = 0;
        }
    }

    /** 旋转左右子树
     *  applyToChild : 是否对孩子也进行旋转
     */
    void Rotate(bool applyToChild=true)
    {
        RotateAt(this,applyToChild);
    }

    /*返回高度较大的孩子*/
    inline Node<T>* TallerChild(){ return stature(LC) > stature(RC) ? LC : RC; }
    
};


NamespaceEnd
#endif