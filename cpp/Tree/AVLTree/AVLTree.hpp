#ifndef _AVLTree_H_
#define _AVLTree_H_

#include "../BST/BST.hpp"
#include <cmath>  //abs()


NamespaceBegin

template<typename T>
class AVLTree : public BST<T>
{
protected:

    //当结点的左右子树高度之差小于等于1时,就是平衡状态,否则就不平衡,需要调整
    static bool isBalanced(Node<T>* v)
    { return abs( stature(v->LC) - stature(v->RC) ) <=1 ; }


     /** zigzag: 先zag ,再zig
      *       g                                  g                                    v
      *     /  \                                / \                                 /   \
      *    p    d          zag at p            v   d           zig at g            p     g
      *   / \         ==============>         / \          ==============>        / \   / \
      *  a   v                               p   c                               a   b c   d
      *     / \                             / \
      *    b  c                            a   b
      */
      
      /**zagzig: 先zig, 再zag
      *         g                              g                                     v
      *       /   \                          /   \                                 /   \
      *      a      p         zig at p      a     v            zag at g           g     p
      *            / \     ============>         /  \      ===============>      / \   / \
      *           v   d                         b    p                          a  b  c   d
      *          / \                                / \
      *         b  c                               c   d
      */

    void RebalanceAbove(Node<T>* v, bool upToRoot=false)
    {   
        // Node<T>* p = v->parent, *g = (p ? p->parent : NULL);
        Node<T> *p=NULL, *g=NULL;
        for( g = v ; g ; g=g->parent)
        {
            if( !isBalanced(g) )
            {
                p = g->TallerChild();
                v = p->TallerChild();
                if( p == g->LC ) //zig
                {
                    if( v == p->LC ) g = this->zig(g); //zigzig, 只需要一次单旋
                    else g = this->connect34(p, v, g, p->LC, v->LC, v->RC, g->RC, g);//直接连接,一步到位
                }
                else //zag
                {
                    if( v == p->RC) g = this->zag(g); //zagzag, 只需要一次单旋
                    else g = this->connect34(g, v, p, g->LC, v->LC, v->RC, p->RC, g);//直接连接,一步到位
                }
                if(!upToRoot) break; //当执行插入时,最多只需要进行一次调整
            }
        }
    }
    
public:
    AVLTree():
        BST<T>()
        {}

    /**执行AVL树的插入操作,返回插入操作是否被执行
     * 首先看一下插入操作会导致结点失去平衡的情况:
     * 情况(一), 单旋型, 具有对称的zag()旋转情况
     *       g                       g                           p
     *      / \     插入x           / \       zig(g)           /   \
     *     p   b  ========>        p   b   ===========>      v      g
     *    / \                     / \                       /      / \
     *   v   a                   v   a                     x      a   b
     *                          /
     *                         x
     *  
     * 情况(二), 双旋型, 具有对称的zagzig()旋转情况
     *       g                       g                          g                          v
     *      / \     插入x           / \       zag(p)           /  \        zig(g)         /  \
     *     p   b  ========>        p   b   ===========>      v     b   ===========>      p    g
     *    / \                     / \                       /                           / \    \
     *   a   v                   a   v                     p                           a  x     b
     *                              /                     / \
     *                             x                     a   x
     * 
     * 可以看出,不管在情况(一)还是情况(二)中, 插入x前后, 该局部子树根结点的高度都没有发生变化
     * 故根结点以上的祖先的高度也不会发生变化,因此根结点以上的祖先不会因为次此插入操作而失去平衡
     * 因此,插入操作最多只会导致其祖先结点失衡,不会导致其他结点失衡
     * 时间复杂度O(logN),N为结点个数,其主要时间消耗在于查找待删除结点,插入以及调整操作只需O(1)的时间
     */
    virtual bool Insert(const T& e)
    {
        Node<T>*& v = BST<T>::SearchIn(e, this->_root, this->_hot=NULL);
        if(!v) //元素不存在时才进行插入操作
        {
            v = new Node<T>(e, this->_hot);
            ++(this->_size);
            if(this->_hot)
            {
                this->_hot->UpdateHeightAbove();
                RebalanceAbove(v); //最多只存在一个失衡的祖先结点,且调整为重平衡之后,不会造成其他结点失衡
            }
            return true;
        }
        return false;
    }

    /**执行AVL树的结点删除操作, 返回删除操作是否被执行
     * 首先看一下删除操作会导致结点失去平衡的情况:
     * 情况(一), 单旋型, 具有对称的zag()旋转情况
     *       g                       g                          p
     *      / \     删除b           /         zig(g)           /  \
     *     p   b  ========>        p       ===========>      v     g
     *    / \                     / \                             /
     *   v  a                    v   a                           a 
     * 
     * 情况(二), 单旋
     *       g                       g                          p
     *      / \     删除x           / \      zig(g)            /  \
     *     p   d  ========>        p   d  ===========>       v     g
     *    / \   \                 / \                       / \   /  \
     *   v   c   x               v   c                     a   b c    d
     *  / \   \                 / \   \                           \
     * a   b  (e)              a   b  (e)                         (e)
     *
     * 情况(三), 双旋
     *       g                  g                     g                        v
     *      / \     删除x      /  \       zag(p)     /  \    zig(g)          /   \
     *     p   d  ========>   p    d    ========>   v    d  ========>       p     g
     *    / \   \            /  \                  / \                     / \   / \
     *   a   v   x          a    v                p   c                   a   b c   d
     *      / \            /    / \              / \                     /
     *     b  c           (e)  b   c            a   b                  (e)
     *                                         /
     *                                        (e)
     * 
     * 在情况(一)中,删除前和删除b后,根结点的高度没有发生变化,也就意味着这种情况不会导致祖先结点失去平衡;
     * 但是在后面两种情况中,如果结点(e)不存在,则删除前后根结点的高度发生了变化, 若该局部子树正好是其某个祖先
     * 高度较低的孩子, 现在该孩子的高度反而还减小了, 就会导致祖先失去平衡, 因此, 删除操作会导致祖先结点失衡.
     * 而且在将祖先结点调整平衡之后, 上述情况可能还会再次发生, 所以删除操作要对被删除结点到根结点上的祖先
     * 结点都进行平衡检测,并对失衡结点进行调整.
     * 
     * 对于情况(二), 只需对根结点g进行一次zig旋转就可以让该局部子树恢复平衡,对于情况(三),如果使用旋转的方法,
     * 则需要先对结点p进行一次zag旋转,然后对结点g进行一次zig旋转,但是这里采用的是直接进行拼接的方法,可以一步到位,
     * 效率稍微要快一点
     * 时间复杂度O(logN),N为结点个数
     */
    virtual bool Remove(const T& e)
    {
        Node<T>*& v = BST<T>::SearchIn(e, this->_root, this->_hot=NULL);
        if(v) //元素存在时才进行删除操作
        {
            BST<T>::RemoveAt(v, this->_hot); //完成之后_hot将指向被删除结点的父亲结点
            --(this->_size);
            if(this->_hot)
            {
                this->_hot->UpdateHeightAbove();
                RebalanceAbove(this->_hot, true); //从_hot指向的结点开始,一直调整到根结点路径上的所有祖先结点
            }
            return true;
        }
        return false;
    }
    
};







NamespaceEnd

#endif
