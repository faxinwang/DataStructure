#ifndef _SplayTree_H_
#define _SplayTree_H_

#include "../BST/BST.hpp"

NamespaceBegin

template<typename T>
class SplayTree : public BST<T>
{

protected:


    /**对于zig-zag和zag-zig情况, 调整方法与AVL树相同
     * zigzag: 先zag ,再zig
     *       g                                  g                                    v
     *     /  \                                / \                                 /   \
     *    p    d          zag at p            v   d           zig at g            p     g
     *   / \         ==============>         / \          ==============>        / \   / \
     *  a   v                               p   c                               a   b c   d
     *     / \                             / \
     *    b   c                           a   b
     * zagzig: 先zig, 再zag
     *         g                              g                                     v
     *       /   \                          /   \                                 /   \
     *      a      p         zig at p      a     v            zag at g           g     p
     *            / \     ============>         /  \      ===============>      / \   / \
     *           v   d                         b    p                          a  b  c   d
     *          / \                                / \
     *         b   c                              c   d
     */
    /**对于zigzig和zagzag情况, 则调整方法略有不同, 按照Tarjan所建议的调整进行方法, 也就是先旋转祖先结点g,
     * 再旋转父亲结点p, 这样可以起到路径折叠的效果, 从而有效避免了退化为单链的最坏情况的发生.
     *         g                       p                           v
     *       /   \                   /   \                       /   \
     *      p     d                 v     g                     a     p
     *    /  \          zig(g)     / \   / \       zig(p)            /  \
     *   v    c       ========>   a   b c   d   ==========>         b    g
     *  / \                                                             /  \
     * a   b                                                           c    d
     *               
     *         g                        p                            v
     *       /   \                    /   \                        /   \
     *      a     p       zag(g)     g     v         zag(p)       p     d
     *           / \    ========>   / \   / \     ==========>    / \
     *          b   v              a   b c   d                  g   c
     *             / \                                         / \
     *            c   d                                       a   b
     */

    //使用双层调整的方法, 可有效避免退化为单链的情况反复发生
    Node<T>* Splay(Node<T>* v)
    {
        if(!v) return v;
        Node<T> *p = v->parent, *g = (p? p->parent : NULL);
        for(; g ; p = v->parent , g = (p? p->parent : NULL) )
        {
            if(g->LC == p) 
            {
                if(p->LC == v) v = this->zig( this->zig(g) );
                else v = this->connect34(p , v, g, p->LC, v->LC, v->RC, g->RC, g);
            }
            else
            {
                if(p->RC == v) v = this->zag( this->zag(g) );
                else v = this->connect34(g, v, p, g->LC, v->LC, v->RC, p->RC, g);
            }
        }
        //最后如果v处于第二层, 则只需根据情况进行一次单旋即可将v调整至根结点
        if(p && p == v->parent) p->LC == v ? this->zig(p) : this->zag(p);
        return v;

        //下面是最简单的代码实现, 但是无法避免最坏情况重复发生
        // for(; p; p = v->parent)
        // {
        //     if(p->LC == v) this->zig(p);
        //     else this->zag(p);
        // }
    }


    //删除以给定结点为根的局部子树
    int DeleteSubtree(Node<T>*& rt)
    {
        if(rt)
        {
            int cnt = rt->Size();
            this->Clear(rt);
            this->_size -= cnt;
            return cnt;
        }
        return 0;
    }


public:

    SplayTree():BST<T>(){}
    
    /**返回指向搜索元素所在结点的迭代器
     * 如果所搜的元素存在, 则将该元素所在结点伸展到树根
     */
    virtual typename BST<T>::Iterator Search(const T& e)
    {
        Node<T>*& v = BST<T>::SearchIn(e, this->_root, this->_hot=NULL);
        Splay( v ? v : this->_hot ); //可能两个指针都为空,因此Splay()函数需要做空指针判断
        return typename BST<T>::Iterator(NULL, v , NULL);
    }


    /**往树中插入新元素, 返回是否执行了插入操作
     * 如果元素已经存在, 则直接返回不进行插入
     * 如果元素不存在, 则插入元素后, 将新插入的结点伸展到树根
     */
    virtual bool Insert(const T& e)
    {
        using namespace std;
        Node<T>*& v = BST<T>::SearchIn(e, this->_root, this->_hot=NULL);
        if(!v)
        {
            v = new Node<T>(e, this->_hot);
            ++(this->_size);
            Splay(v); //将新插入的结点伸展到根结点
            return true;
        }
        return false;
    }

    /**删除给定元素, 返回是否执行了删除操作
     * 如果要删除的元素不存在, 则将_hot指针指向的结点伸展至根结点
     * 如果要删除的元素存在, 则删除步骤如下:
     * 1.先将要删除的元素伸展至根结点
     * 2.将左右子树与根结点脱离, 然后释放掉根结点
     * 3.将右子树中值最小的元素取出,作为新的根结点,注意将新根结点父指针置空,并正确跟新_root指针
     * 4.将左右子树作为新根结点的左右子树
     * 
     * 注: 如果右子树为空, 则用左子树中键值最大的作为新的根结点; 如果左子树也为空, 则结点个数变为0,
     *     将根指针置空.
     */
    virtual bool Remove(const T& e)
    {
        Node<T>*& v = BST<T>::SearchIn(e, this->_root, this->_hot);
        if(v == NULL)
        {
            Splay(this->_hot);
            return false;
        }
        Node<T>* rt = Splay(v); //1
        Node<T>* lc = rt->DetachLeftChild(); //2
        Node<T>* rc = rt->DetachRightChild();
        delete rt;

        /*------3 选择右子树中最小的元素或者左子树中最大的元素作为新的根结点------*/
        //选择右子树中键值最小的元素最为新的根结点
        Node<T>* newRoot =  rc ? rc->LeftMostNode() : NULL;
        if(newRoot && newRoot != rc) newRoot->parent->AttachLeftChild(newRoot->RC, false);
        //如果右子树为空, 则选择左子树中键值最大的元素作为新的根结点
        if(newRoot == NULL )
        {
            newRoot = lc ? lc->RightMostNode() : NULL;
            if(newRoot && newRoot != lc) newRoot->parent->AttachRightChild(newRoot->LC, false);
        }
        //如果左右子树都为空, 则二叉树没有结点了,置_root为空
        if(newRoot == NULL )
        {
            this->_root = NULL; //左右子树都为空,将根结点置空
            return true;
        }
         /*------4 将剩下的左右子树重新拼接成一颗树---------*/
        newRoot->parent = NULL;
        if(newRoot != lc) newRoot->AttachLeftChild(lc, false);
        if(newRoot != rc) newRoot->AttachRightChild(rc, false);
        this->_root = newRoot;
        --(this->_size);
        return true;
    }


    /**删除区间
     * 伸展树删除区间的速度非常快速, 设区间[L,R]中元素个数为n个, 删除该区间的时间复杂度为O(n)
     */

    int RemoveRange(const T& L, const T& R)
    {
        using namespace std;
        int cnt = 0;
        if(this->_root == NULL || L > R) return 0;
        if( L == R ) return this->Remove(L);
        
        Node<T> *head=NULL, *tail=NULL;
        Node<T>* left = this->_TheLargestElementLessThan(L);
        if(left == NULL) left = head = this->_root->LeftMostNode();
        Node<T>* right = this->_TheSmallestElementGreaterThan(R);
        if(right == NULL) right = tail = this->_root->RightMostNode();

        if(left == head && right == tail) //删除区间覆盖了整颗树, 直接清空
        {
            this->Clear();
            cnt = this->_size;
            this->_size = 0;
        }
        else if(left == head)
        {
            Splay(right);
            cnt = DeleteSubtree(this->_root->LC);
        }
        else if(right == tail)
        {
            Splay(left);
            cnt = DeleteSubtree(this->_root->RC);
        }
        else
        {
            Splay(left);
            Splay(right);
            T& lc = this->_root->LC->data;
            if(L <= lc && lc <= R ) this->zig(this->_root->LC);
            cnt = DeleteSubtree(this->_root->LC->RC);
        }
        return cnt;
    }
    
};




NamespaceEnd
#endif