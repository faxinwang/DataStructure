#ifndef _BST_H_
#define _BST_H_

#include "../BinaryTree/BinaryTree.hpp"
#include "../../util/require.hpp"

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


/**BinarySearchTree提供了如下API
 * Iterator* Search(const T &e) : 查找BST中是否存在给定元素, 返回该元素所在的结点
 * void Insert(cosnt T &e)      : 向BST中插入元素，返回该元素所在结点（不重复插入）
 * bool Remove(const T &e)      : 删除给定元素，成功返回true，否则返回false
 * int Size()  : 返回结点个数
 * Iterator Begin() : 返回指向第一个元素的迭代器, 通过 ++it 配合 End() 向右遍历
 * Iterator RBegin(): 返回指向末尾元素的迭代器, 通过 --it 配合 End() 向左遍历
 * Iterator End()   : 返回表示遍历结尾的哨兵迭代器
 * Iterator Head()  : 返回指向第一个元素前面一个位置的迭代器, 通过 Next() 向右遍历,无需与End()比较
 * Iterator Tail()  : 返回指向最后一个元素后一个位置的迭代器, 通过 Prev() 向左遍历,无需与End()比较
 * 
 * protected 方法:
 * Node<T>*& SearchIn(const T& e): 返回指向元素为e的结点的指针的引用
 * static Node<T>* RemoveAt(Node<T>* &x, Node<T>*& hot) BST删除结点的算法实现
 * Node<T>* connect34() : 将需要进行zigzag或zagzig旋转所涉及到的点直接连接成最终的平衡态
 * Node<T>* zig() :  对给定的结点进行zig旋转
 * Node<T>* zag() :  对给定的结点进行zag旋转
 * 
 * 
 * 详细使用方法参见测试文件:
 * BST_TestIterator.cpp
 * BST_TestBasic.cpp
 */

//继承自BinaryTree类模板
template<typename T>
class BST: public BinaryTree<T>
{
public:  //An implementation of the internal iterator
    class Iterator
    {
    private:
        Node<T>* cur; //指向当前结点的指针
        Node<T>* next; //指向当前结点下一个结点的指针
        Node<T>* prev; //指向当前结点上一个结点的指针
    public:
        Iterator(Node<T> *pre=NULL, Node<T> *cur=NULL, Node<T> *nxt=NULL)
        :cur(cur),prev(pre),next(nxt)
        { 
            if(cur)
            {
                 next = cur->NextNode();
                 prev = cur->PrevNode();
            }
        }

        T& operator*(){ return cur->data; }

        inline bool operator==(const Iterator& it){ return cur==it.cur; }

        inline bool operator!=(const Iterator& it){ return cur!=it.cur; }

        //前缀++运算符,该操作使当前迭代器指向中序遍历序列的下一个结点.
        Iterator& operator++()
        {
            prev=cur;
            cur=next; 
            if(cur) next = cur->NextNode();
            return *this;
        }
        //后缀式++
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            operator++();
            return tmp;
        }

        //前缀--运算符,该操作使当前迭代器指向中序遍历序列的上一个结点.
        Iterator& operator--()
        {
            next = cur;
            cur = prev;
            if(cur) prev = cur->PrevNode();
            return *this;
        }
        //后缀式--
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            operator--();
            return tmp;
        }

        //将当前指针移向下一个位置,并返回该位置是否为空,类似jdbc中resultSet的next()方法
        inline bool Next(){ operator++(); return cur != NULL; }
        //将当前指针移向上一个位置,并返回该位置是否为空
        inline bool Prev(){ operator--(); return cur != NULL; }
        //判断迭代器当前指向的位置是否为空
        inline bool IsNull(){ return cur==NULL; }
        //判断迭代器当前指向的位置是否非空
        inline bool NotNull(){ return cur!=NULL; }
    };

protected:  //成员变量
    Node<T>* _hot; //始终指向搜索结束时的父亲结点
    int _size;  //由于现在所有的插入和删除都是通过BST进行的, 因此使用变量保存结点个数会更高效

protected:  //静态函数 SearchIn() RemoveAt()

    /**从根结点开始查找给定元素,返回该元素所在结点指针的引用
     * 1.如果目标结点存在, 则返回指向该结点指针的引用
     * 2.如果目标结点不存在, 则返回指向空结点指针的引用
     * 3.两种情况下_hot分别指向叶子结点的父结点和叶子结点
     * 4.由于返回的是指针的引用, 因此可以直接对该指针进行赋值等操作.
     * rt : 指向某个结点的引用
     * e  : 待查找元素
     * hot: 记忆热点，不管查找成功还是失败，总是指向所返回结点的父结点
     * TC = O(h) ,h为返回结点在树中的深度
     * 
    */
    static Node<T>*& SearchIn(const T& e, Node<T>*& rt, Node<T>*& hot)
    {
        //循环实现, 注意因为参数rt是指针的引用, 且引用到了实际的_root变量, 因此
        //不能对其进行修改,要获得最后待插入结点的引用, 只能不断创建新的引用指向
        //路径上的结点,最后返回的要么是指向已存在结点的引用, 要么是某个空指针的引用,
        //当对返回的引用赋值之后,树上原来的那个指针也将被赋为同样的值.
        if(!rt || rt->data == e) return rt;
        hot = rt;
        while(1)
        {   
            Node<T>*& v = e < hot->data ? hot->LC : hot->RC;
            if( !v || (e==v->data) ) return v;
            hot = v; //先记下当前非空结点，然后再继续搜索
        }
        //递归实现
        // if( !rt || (e==rt->data) ) return rt;
        // hot = rt; //先记下当前非空结点，然后在继续搜索
        // return SearchIn(e, (e<rt->data? rt->LC : rt->RC), hot);
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
    static Node<T>* RemoveAt(Node<T>* &x, Node<T>*& hot)
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

protected: //辅助函数

    Node<T>* _TheSmallestElementGreaterThan(const T& e)
    {
        Node<T>* v = SearchIn(e, this->_root, this->_hot);
        if(v)
        {
            Node<T>* next = v->NextNode();
            return next ? next : NULL;
        }
        if(this->_hot)
        {
            if(this->_hot->data > e) return this->_hot;
            Node<T>* next  = this->_hot->NextNode();
            return next ? next: NULL;
        }
        return NULL;
    }

    Node<T>* _TheLargestElementLessThan(const T& e)
    {
        Node<T>* v = SearchIn(e, this->_root, this->_hot);
        if(v)
        {
            Node<T>* prev = v->PrevNode();
            return prev ? prev : NULL;
        }
        if(this->_hot)
        {
            if(this->_hot->data < e) return this->_hot;
            Node<T>* prev = this->_hot->PrevNode();
            return prev ? prev : NULL;
        }
        return NULL;
    }

protected: //methods for Balanced Binary Search Tree(BBST) subclasses

    /*************** The follow methods are for BBST subclasses ****************/

    /**after rotate, the final structure of the rotated subtree must be as the following
     *            y
     *          /  \
     *        x     z
     *       / \   / \
     *      a   b c   d
     * 
     * connect34()方法直接将给定的七个结点指针连接成上述的平衡状态.
     * 当需要进行zigzag或者zagzig双旋调整时, 直接使用该方法将相应结点连接成最终状态,
     * 这样比进行两次单旋效率稍微要高一些
     * rt为调整之前局部子树的根结点, 为了正确设置调整之后的新根结点的父指针, 需要知道
     * 调整之前局部子树根结点的父亲, 这里通过rt得到了该信息; 另外, 知道了局部根结点,
     * 还能正确更新_root指针.
     */
    Node<T>* connect34(Node<T>* x, Node<T>* y,Node<T>* z,
        Node<T>* a, Node<T>* b, Node<T>* c, Node<T>* d, Node<T>* rt)
    {
        //连接y的父亲指针
        Node<T>* gg = rt->parent;
        y->parent = gg;
        if(gg) (gg->LC==rt? gg->LC : gg->RC ) = y;
        if(this->_root == rt) this->_root = y; //正确更新根结点指针

        x->LC = a; if(a) a->parent = x;
        x->RC = b; if(b) b->parent = x; x->UpdateHeight();
        z->LC = c; if(c) c->parent = z;
        z->RC = d; if(d) d->parent = z; z->UpdateHeight();
        y->LC = x; x->parent = y;
        y->RC = z; z->parent = y; y->UpdateHeightAbove();
        return y;
    }

    /**zigzig: 只需进行一次zig旋转
     *         g                        p
     *        / \                     /   \
     *       p   d                  v       g
     *     /  \       zig at g    /  \     / \
     *   v     c    ===========> a    b   c   d
     *  / \   
     * a   b
     * 
     * 调用该方法,需要保证结点g的左孩子非空
     */
 
    Node<T>* zig(Node<T>* g)
    {
        //连接父亲指针
        Node<T>* p = g->LC;
        Node<T>* gg = g->parent;
        p->parent = gg;
        g->parent = p;
        if(gg) ( gg->LC == g ? gg->LC : gg->RC ) = p;

        //连接孩子指针
        g->AttachLeftChild( p->DetachRightChild(), false );
        p->AttachRightChild( g );
        
        g->UpdateHeightAbove();
        if( this->_root == g) this->_root = p; //正确更新根结点指针
        return p;
    }

     /**zagzag: 只需进行一次zag旋转
      *        g                            p
      *      /   \                        /   \
      *    a      p        zag at g      g     v
      *          / \      =========>    / \   / \
      *        b    v                  a   b c   d
      *            / \
      *           c   d
      * 调用该方法,需要保证结点g的右孩子非空
      */
    Node<T>* zag(Node<T>* g)
    {
        //连接父亲指针
        Node<T>* p = g->RC;
        Node<T>* gg = g->parent;
        p->parent = gg;
        g->parent = p;
        if(gg) ( gg->LC ==g ? gg->LC : gg->RC) = p;

        //连接孩子指针
        g->AttachRightChild( p->DetachLeftChild(), false );
        p->AttachLeftChild( g );
        
        g->UpdateHeightAbove();
        if( this->_root == g) this->_root = p; //正确更新根结点指针
        return p;
    }

     /**zagzig: 先zig, 再zag
      *         g                              g                                     v
      *       /   \                          /   \                                 /   \
      *      a      p         zig at p      a     v            zag at g           g     p
      *            / \     ============>         /  \      ===============>      / \   / \
      *           v   d                         b    p                          a  b  c   d
      *          / \                                / \
      *         b  c                               c   d
      */

     /** zigzag: 先zag ,再zig
      *       g                                  g                                    v
      *     /  \                                / \                                 /   \
      *    p    d          zag at p            v   d           zig at g            p     g
      *   / \         ==============>         / \          ==============>        / \   / \
      *  a   v                               p   c                               a   b c   d
      *     / \                             / \
      *    b  c                            a   b
      * 
      */
    
    /***********************************************************************************************************/

public:  //公共接口
    
    BST():
        BinaryTree<T>(),
        _size(0),
        _hot(NULL)
        {}
    
    BST(const BST& bst) : BinaryTree<T>()
    {
        this->_root = this->Copy(bst._root);
        _size = bst._size;
    }

    // 移动构造函数
    BST( BST && bst):
        BinaryTree<T>(bst._root),
        _size(bst._size),
        _hot(bst._hot)
        { 
            bst._root=NULL; 
            bst._hot = NULL;
            bst._size = 0;
        }

    BST& operator=(const BST& bst)
    {
        if(this == &bst) return *this;
        this->Clear(this->_root);
        this->_root = this->Copy(bst._root);
        this->_size = bst._size;
        return *this;
    }


    /**从根结点开始查找给定元素,返回指向该元素所在的结点的迭代器
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
    virtual Iterator Search(const T& e)
    {
        Node<T>* pos = SearchIn(e, this->_root, _hot = NULL);
        return Iterator(NULL, pos, NULL);
    }


    /**插入给定元素.
     * 1.查找待插入元素是否存在
     * 2.如果存在,则不插入,否则插入对应位置处
     * 3.更新祖先结点的高度
     * 对于首个结点插入之类的边界情况，均可正确处理
     * TC = O(h), h为树的高度
    */
    virtual bool Insert(const T& e)
    {
        Node<T>*& x = SearchIn(e, this->_root, _hot=NULL);
        if(!x) //禁止重复元素
        { 
            x = new Node<T>(e, _hot); //_hot作为父结点
            ++_size;
            return true;
        }
        return false;
    }


    /*删除给定元素
     * 1.如果目标结点不存在,返回false.
     * 2.目标结点存在,则调用removeAt()删除该元素
     * 3.更新祖先结点的高度,返回true
     *TC = O(h),  h为树的高度
    */
    virtual bool Remove(const T& e)
    {
        Node<T>*& x = SearchIn(e, this->_root, _hot=NULL);// 定位目标结点
        if(!x) return false; //目标元素不存在
        //若目标结点存在,则删除目标结点中的元素
        RemoveAt(x, _hot);
        --_size;
        _hot->UpdateHeightAbove();
        return true;
    }


    //返回树中结点的个数
    virtual int Size(){ return _size; }


    /**使用Begin(), RBegin() 和 End() 返回的迭代器
     * 需要使用 ++ 和 -- 运算符进行迭代.
     */
    Iterator Begin() { return Iterator(NULL,this->_root->LeftMostNode(),NULL ); }
    
    Iterator RBegin() { return Iterator(NULL,this->_root->RightMostNode(),NULL ); }

    Iterator End(){ return Iterator(); }


    /** 使用Head() 和 Tail 返回的迭代器, 
     * 需要使用Prev() 和Next() 进行遍历
     */
    Iterator Head()
    { return Iterator(NULL,NULL,this->_root->LeftMostNode() ); }

    Iterator Tail()
    { return Iterator(this->_root->RightMostNode(),NULL,NULL); }


    bool Contains(const T& e){ return SearchIn(e, this->_root, this-_hot) != NULL;  }

    /**返回BST中大于参数e的最小的元素, 如果没有比e大的元素, 则返回e
     * 首先查找元素e, 
     *   如果e存在, 则通过e所在结点获取其中序遍历的下一个结点
     *      如果下一个结点非空, 即为要找的结点
     *      如果下一个结点为空, 则树中没有比e大的元素, 直接返回e
     *   如果e不存在, 则通过_hot结点进行查找
     *      如果_hot结点中的元素大于e,则_hot中的元素就是所求
     *      如果_hot结点中的元素小于e,则通过_hot获取其中序遍历的下一个结点
     *          如果下一个结点非空, 即为要找的结点
     *          如果下一个结点为空, 则树中没有比e大的元素, 这时应该返回e
     */
    T TheSmallestElementGreaterThan(const T& e)
    {
        Node<T>* v = _TheSmallestElementGreaterThan(e);
        return v ? v->data : e;
    }

    /**返回BST中小于参数e的最大的元素, 如果没有比e小的元素, 则返回e
     * 首先查找元素e,
     *   如果e存在, 则通过e所在结点获取其中序遍历的上一个结点
     *      如果上一个结点非空, 即为所求结点
     *      如果上一个结点为空, 则树中没有比e小的元素, 返回e
     *   如果e不存在,则通过_hot结点进行查找
     *      如果_hot结点中的元素小于e,则_hot中的元素就是所求
     *      如果_hot结点中的元素大于, 则通过_hot获取其中序遍历的上一个结点
     *          如果上一个结点非空, 即为所求
     *          如果上一个结点为空, 则上中没有比e小的元素, 直接返回e
     */
    T TheLargestElementLessThan(const T& e)
    {
        Node<T>* v = _TheLargestElementLessThan(e);
        return v ? v->data : e;
    }

};

NamespaceEnd

#endif
