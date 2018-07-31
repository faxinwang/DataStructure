/**
 * author: wfx
 * desc: My implementation of BineryTree data structure
 */

#ifndef _BinaryTree_
#define _BinaryTree_

//计算结点的高度, 叶子结点的高度定义为0, 空结点的高度定义为-1
#include<algorithm>  //用到std::max()函数
#include "../../Stack/Stack.hpp"
#include "../../Queue/Queue.hpp"
#include "Node.hpp"
#include "../../util/require.hpp"

NamespaceBegin

/**
 *  二叉树类模板, 提供基本的二叉树建立, 遍历, 旋转, 复制, 相等判断等方法.
 *  
 * 成员变量:
 * _root : 二叉树根节点
 * 
 * 方法:
 * BinaryTree() : 默认构造函数, 生成的二叉树对象中包含一颗空二叉树
 * BinaryTree(Node<T>* rt)          : 将给定的结点作为根结点构造二叉树
 * BinaryTree(const BinaryTree& bt) : 拷贝构函数
 * operator=(const BinaryTree& bt)  : 赋值运算符
 * operator==(const BinaryTree& bt) : 相等运算符
 * 
 * Empty() : 如果二叉树为空, 返回ture, 否则返回false
 * Size() : 返回二叉树节点的个数
 * Clear(): 清空二叉树,删除所有的结点
 * 
 * PreOrder() : 先序遍历,循环实现
 * InOrder() : 中序遍历,循环实现
 * PostOrder() : 后续遍历,递归实现
 * LevelOrder(): 层序遍历, 循环实现
 * 
 */

template<typename T>
class BinaryTree
{
protected: 
    Node<T> *_root;

private:  //私有静态方法

    template<typename VIS>
    static void PostOrder(Node<T>* rt, VIS& visit)
    {
        if(rt)
        {
            PostOrder(rt->LC, visit);
            PostOrder(rt->RC, visit);
            visit(rt->data);
        }
    }

    //注意参数需要使用指针的引用, 否则会产生野指针
    static void Clear(Node<T>*& rt)
    {
        if(rt)
        {
            Clear(rt->LC);
            Clear(rt->RC);
            delete rt;
            rt = 0;
        }
    }

    //复制二叉树, 只复制树结构, 不复制二叉树的其他成员变量
    static Node<T>* Copy(Node<T>* rt, Node<T>* parent=NULL)
    {
        if(rt)
        {
            Node<T>* root = new Node<T>(rt->data, parent);
            root->LC = Copy(rt->LC, root);
            root->RC = Copy(rt->RC, root);
            root->UpdateHeight();
            return root;
        }
        return NULL;
    }

    static bool Equal(const Node<T>* rt1, const Node<T>* rt2)
    {
        if(rt1==NULL && rt2==NULL) return true;
        return  rt1 && 
                rt2 && 
                rt1->data == rt2->data &&
                Equal(rt1->LC, rt2->LC) &&
                Equal(rt1->RC, rt2->RC);
    }

public:  //公开方法
    
    //无参构造函数, 建立一颗空树
    BinaryTree() 
        :_root(NULL)
        {}
    
    /**通过给定的结点作为二叉树的根结点.
     * 传入的结点必须是根结点,否则其所有的祖先结点将不能被删除,
     * 除非外部能够对其祖先结点进行正确处理,否则将会导致内存泄露.
    */
    BinaryTree(Node<T>* node)
        :_root(node)
        {}

    //虚析构函数
    virtual ~BinaryTree(){ Clear(_root); }

    /**拷贝构造函数, 调用赋值函数
     * 这里一定要将_root初始化为空,否则_root会是一个随机值.然后
     * 在调用赋值运算符时,两个if判断基本都不会成立,进而在Clear(_root)
     * 时,会去删除一块随机的内存,从而导致程序出错!!!
     */
    BinaryTree(const BinaryTree& bt):_root(NULL) { *this = bt; }

    //赋值运算符
    BinaryTree& operator=(const BinaryTree& bt)
    {
        if(this == &bt) return *this; //自己赋值给自己
        if(_root == bt._root) return *this; //两个二叉树对象引用同一颗二叉树
        //先清空被赋值的二叉树,再进行复制
        Clear(_root);
        _root = Copy(bt._root);
    }

    /** 判断两颗二叉树是否相等
     *  当且仅当两颗二叉树的结构和对应结点中的数据均相等时才判断为相等.
     */
    bool operator==(const BinaryTree& bt)
    {
        if(this == &bt) return true; //同一个对象,必定相等
        return Equal(_root, bt._root); //否则再比较树
    }

    bool Empty()const { return _root==NULL; }

    virtual int Size()const { return _root==NULL? 0 : _root->Size(); }

    void Clear() { Clear(_root) ;}

    /**二叉树的先序遍历,用循环实现
     * 借助于栈的后进先出特性,每遍历到一个结点时, 先访问该结点的数据, 然后
     * 先将其右孩子入栈, 再将其左孩子入栈.然后不断访问栈顶元素并重复上述操作.
     * 注意当子结点为空时不能入栈, 需要注意当父结点也为空时的特殊情况.
     * 
     * visit为模板参数,实际调用时参数可以是函数,也可以是函数对象function object, 
     * 如需要获取中序遍历序列, 可以在函数对象中定义一个容器,在遍历时将数据放入容器中.
     */
    template<typename VIS>
    void PreOrderGo(VIS &visit)
    {
        Stack<Node<T>*> s;
        s.reserve(this->Size());//当栈内容器是vector时,使用reserve可提升效率.
        if(_root) s.push(_root);
        while(!s.empty())
        {
            Node<T>* x = s.pop();
            visit(x->data);
            if(x->RC) s.push(x->RC);
            if(x->LC) s.push(x->LC);
        }
        // PreOrder(_root, visit);
    }

    /**二叉树的中序遍历, 使用循环实现
     * 1. 对于以每一个结点为根结点所构成的树,先将其左侧链全部入栈.
     * 2. 若栈为空, 则遍历结束.
     * 3. 弹出栈顶元素, 访问其元素值.
     * 4. 转移到当前结点的右子树上去, 并重复上述步骤.
     */
    template<typename VIS>
    void InOrderGo(VIS &visit)
    {
        Stack<Node<T>*> s;
        s.reserve(this->Size());
        Node<T>*x = _root;
        while(true)
        {
            while(x) //将左侧分枝上的结点全部放入栈中
            {
                s.push(x);
                x = x->LC;
            }
            if(s.empty()) break;
            x = s.pop();
            visit(x->data); //访问左侧分枝末端的结点
            x = x->RC;  //访问该结点的右子树
        }
    }
    //后序遍历驱动
    template<typename VIS>
    void PostOrderGo(VIS &visit)
    {
        PostOrder(_root, visit);
    }

    /**用队列实现的层序遍历
     * 1.对于每个结点, 先访问其数据, 然后将其左孩子入队, 再将其右孩子入队.
     * 2.然后不断取出队头元素,重复步骤一的操作,直到队列为空.
     * 3.空结点不入队.
     */
    template<typename VIS>
    void LevelOrderGo(VIS &visit)
    {
        Queue<Node<T>*> Q;
        if(_root) Q.push(_root);
        while(!Q.empty())
        {
            Node<T>* x = Q.pop();
            visit(x->data);
            if(x->LC) Q.push(x->LC);
            if(x->RC) Q.push(x->RC);
        }
    }
};


NamespaceEnd
#endif 
