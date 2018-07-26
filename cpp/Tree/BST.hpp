#ifndef _BST_H_
#define _BST_H_

#include "BinaryTree/BinaryTree.hpp"
#include "../util/require.hpp"

NamespaceBegin

/*词条模板
 * Key  : 用于比较，需要支持小于号运算符
 * value: 保存key对应的信息
*/
template<typename K, typename V>
struct Entry{
    K key;
    V value;
    Entry(K k=K(), V v=V()): key(k),value(v){} //默认构造函数
    Entry(Entry<K,V> const& e):key(e.key),value(e.value){} //拷贝构造函数
    //比较器,判断器等。
    bool operator< ( Entry<K,V> const &e){ return key < e.key; }
    bool operator> ( Entry<K,V> const &e){ return e.key < key; }
    bool operator==( Entry<K,V> const &e){ return (!(key<e.key)) && (!(e.key<key)); }
    bool operator!=( Entry<K,V> const &e){ return key < e.key || e.key < key; }
};

/**BinarySearchTree提供了如下三个API
 * Node<T>* search(const T &e) : 查找BST中是否存在给定元素, 返回该元素所在的结点
 * Node<T>* insert(cosnt T &e) : 向BST中插入元素，返回该元素所在结点（不重复插入）
 * bool remove(const T &e)     : 删除给定元素，成功返回true，否则返回false
 */

//继承自BinaryTree类模板
template<typename T>
class BST: public BinaryTree<T>
{
protected:  //成员变量
    Node<T>* _hot; //始终指向搜索结束时的父亲结点

protected:  //static 成员方法

    /**从根结点开始查找给定元素,返回该元素所在结点指针的引用
     * 1.如果目标结点存在, 则返回指向该结点指针的引用
     * 2.如果目标结点不存在, 则返回指向空结点指针的引用
     * 3.两种情况下_hot分别指向叶子结点的父结点和叶子结点
     * 4.由于返回的是指针的引用, 因此可以直接对该指针进行赋值等操作.
     * rt : 根结点
     * e  : 查找元素 
     * hot: 记忆热点，不管查找成功还是失败，总是指向所返回结点的父结点
     * TC = O(h) ,h为返回结点在树中的深度
    */
    static Node<T>* & searchIn(const T& e, Node<T>* &rt, Node<T>*& hot)
    {
        if( !rt || (e==rt->data) ) return rt;
        hot = rt; //先记下当前非空结点，然后在继续搜索
        return searchIn( e, (e < rt->data? rt->LC : rt->RC), hot );
    }

    /**删除结点x中的元素,结点x可能被摘除.
     * 由于x是指向待删除结点的指针的引用,因此修改x的值就是修改指向待删除结点指针的值. 
     * 设del指向实际将要被删除的结点,初始时指向x指向的结点,next指向del的适当的孩子结点,初值为NULL
     * 1.当x指向的结点没有左孩子时, 就让x和next指向该结点的右孩子
     * 
     * 2.当x指向的结点没有右孩子时, 就让x和next指向该结点的左孩子
     *   上述两种操作也能够正确处理待删除结点没有孩子的情况,这时x被正确地置空了
     * 
     * 3.当x指向的结点具有两个孩子时,就将del指向x所指结点的中序遍历意义下的下一个孩子结点,
     *   该结点有可能是x所指结点的右孩子, 也可能是x所指结点右子树中最左边的那个结点,不管怎样,
     *   该结点都不可能有左孩子, 因此该结点的删除操作同步骤1,next指向该结点的右孩子.由于现在
     *   del指向的结点并不是x指向的结点,所以还需要将del所指结点中的元素拷贝到x指向的结点中去.
     * 
     * 4.此时del正确地指向了要被摘除的结点,next正确地指向了del所指结点的唯一的孩子,或为空(当x没有孩子时)
     * 
     * 5.在执行删除操作之前,先要将next所指结点的父指针正确连接到新的父结点,也就是del的父结点上.
     *  TC = O(h), h为树的高度
    */
    static Node<T>* removeAt(Node<T>* &x, Node<T>*& hot)
    {
        Node<T>* del, *next;

        if( !x->LC ){
            del = x;
            next = x = x->RC; //不存在左孩子， 用右孩子替代
        } 
        else if( !x->RC ){
            del = x;
            next = x = x->LC; //不存在右孩子，用左孩子替代
        } 
        else{ //左右孩子均存在, 用中序遍历的直接后继元素替代
            del = x->NextNode();
            x->data = del->data;
            next = del->RC; //待删除结点只可能有右孩子
            //将待删除结点的可能存在的子结点next正确连接到其父结点上。
            if(x == del->parent) del->parent->RC = next;
            else del->parent->LC = next;
        } //这三条分枝依然可以处理左右孩子均不存在的情况

        hot = del->parent; //记录实际被删除结点的父亲
        if( next ) next->parent = del->parent; 
        delete del;
        return next; 
    }

public:

    /**从根结点开始查找给定元素,返回指向该元素所在的结点的指针
     * 1.内部调用searchIn()函数
     * 2.如果目标结点存在, 则返回指向该结点的指针
     * 3.如果目标结点不存在, 则返回指向空结点的指针
     * 4.两种情况下_hot分别指向叶子结点的父结点和叶子结点
     * 
     * [问题]:
     * 这里发现了一个问题,就是在类模板中,子类无法直接访问父类public或protected
     * 的成员,例如这里要访问父类的_root成员变量, 直接访问的时候编译不通过,显示在
     * 该范围内没有定义.
     * 
     * 解决方法:
     * 1.通过this来访问: this->_root
     * 2.通过域限定符访问: BinaryTree<T>::_root
     * 
     * 原因: 
     * 对于一些编译器，例如gcc和xcode，在扫描模板类的定义的时候，就先确定每一个成员
     * 都是在哪里声明的。但是VC++把这件事放倒了实例化的时候，而具体的顺序C++标准实际
     * 上是没有规定的。
     */
    virtual Node<T>* search(const T& e)
    {
        return searchIn(e, this->_root, _hot = NULL); 
        // return searchIn(e, BinaryTree<T>::_root, _hot = NULL); 
    }


    /**插入给定元素，返回该元素所在的结点指针
     * 1.查找待插入元素是否存在
     * 2.如果存在,则不插入,否则插入对应位置处
     * 3.更新祖先结点的高度
     * 对于首个结点插入之类的边界情况，均可正确处理
     * TC = O(h), h为树的高度
    */
    virtual Node<T>* insert(const T& e)
    {
        Node<T>*& x = searchIn(e, this->_root, _hot=NULL);
        if(!x){ //禁止重复元素
            x = new Node<T>(e, _hot); //_hot作为父结点
            // ++(this->_size);
            x->UpdateHeightAbove();
        }
        return x;
    }


    /*删除给定元素
     * 1.如果目标结点不存在,返回false.
     * 2.目标结点存在,则调用removeAt()删除该元素
     * 3.更新祖先结点的高度,返回true
     *TC = O(h),  h为树的高度
    */
    virtual bool remove(const T& e)
    {
        Node<T>*& x = searchIn(e, this->_root, _hot=NULL);// 定位目标结点
        if(!x) return false; //目标元素不存在
        //若目标结点存在,则删除目标结点中的元素
        removeAt(x, _hot);
        _hot->UpdateHeightAbove();
        return true;
    }
};

NamespaceEnd

#endif
