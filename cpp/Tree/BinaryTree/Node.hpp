#ifndef _Node_
#define _Node_

NamespaceBegin

#include "../../Queue/Queue.hpp"
#include "../../util/require.hpp"
#define stature(rt) ((rt)? rt->height : -1)

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
 * UpdateHeight(): 更新当前结点的高度
 * UpdateHeightAbove(): 更新当前结点及其所有祖先结点的高度
 * InsertLeftChild(const T& e):  将元素作为该结点的左孩子插入
 * InsertRightChild(const T& e): 将元素作为该结点的右孩子插入
 * RemoveLeftSubTree() : 删除左子树
 * RemoveRightSubTree() : 删除右子树
 * Detach() : 与父结点分离
 */


template<typename T>
struct Node
{
public:
    T data;
    int height;
    Node *LC;
    Node *RC;
    Node *parent;

private: //私有方法
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

public: //成员方法
    //构造函数
    Node(const T& data=T(), Node* parent=NULL)
        :LC(0)
        ,RC(0)
        ,height(0) //叶结点的高度定义为0
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

    //找到中序遍历意义下的下一个"子孙"结点,该方法将用于BST中寻找待删除结点的替代结点.
    Node* NextNode()
    {
        Node* next=RC;
        while(next && next->LC) next = next->LC;
        return next;
    }

    //找到中序遍历意义下的上一个"子孙"结点
    Node* PrevNode()
    {
        Node* prev = LC;
        while(prev && prev->RC) prev = prev->RC;
        return prev;
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

    /** 1.删除左子树(注意判断指针是否非空)
     *  2.更新相关结点的高度
     */
    void RemoveLeftSubTree()
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
    void RemoveRightSubTree()
    {
        if(RC)
        {
            Clear(RC);
            UpdateHeightAbove();
        }
    }

    /**连接左子树
     * 1.如果左子树存在, 则先删除左子树
     * 2.将左孩子指针指向tree
     * 3.如果tree非空,将tree的父指针指向this
     */
    void AttachLeftSubTree(Node* tree)
    {
        if(LC) RemoveLeftSubTree();
        LC = tree;
        if(tree) tree->parent = this;
        UpdateHeightAbove();
    }

    /**连接右子树
     * 1.如果右子树存在, 则先删除右子树
     * 2.将右孩子指针指向tree
     * 3.如果tree非空,将tree的父指针指向this
     */
    void AttachRightSubTree(Node* tree)
    {
        if(RC) RemoveRightSubTree();
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
};


NamespaceEnd
#endif