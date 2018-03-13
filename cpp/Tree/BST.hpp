#ifndef _BST_H_
#define _BST_H_

#include "BinTree.hpp"

/*词条模板
Key 用于比较，需要支持小于号运算符
value保存key对应的信息
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

/*
主要方法：
//查找BST中是否存在给定元素, 返回该元素所在的结点
BinNode<T>* search(const T &e);

//向BST中插入元素，返回该元素所在结点（不重复插入）
BinNode<T>* insert(cosnt T &e);

//删除给定元素，成功返回true，否则返回false
bool remove(const T &e);
*/

//继承自BinTree类模板
template<typename T>
class BST: public BinTree<T>{
protected:
    BinNode<T>* _hot; //搜索时命中结点的父亲结点
/*
    //3+4重构
    BinNode<T>* connect34(
		BinNode<T>* nd1, BinNode<T>* nd2, BinNode<T>* nd3,
        BinNode<T>* nd4, BinNode<T>* nd5, BinNode<T>* nd6, BinNode<T>* nd7)
    {

    }

    //旋转调整
    BinNode<T>* rotateAt(BinNode<T>* rt)
    {
        if(rt){
            BinNode<T>* tmp = rt->LC;
            rt->LC = rt->RC;
            rt->RC = tmp;
            rotateAt(rt->LC);
            rotateAt(rt->RC);
        }
    }
*/
    //rt:根结点
    //e:查找元素 
    //hot: 记忆热点，不管查找成功还是失败，总是指向所返回结点的父结点
    //TC = O(h) ,h为返回结点在树中的深度
    static BinNode<T>* & searchIn(BinNode<T>* &rt, const T& e, BinNode<T>* & hot)
    {
        if( !rt || (e==rt->data) ) return rt;
        hot = rt; //先记下当前非空结点，然后在继续搜索
        return searchIn( e < rt->data? rt->LC : rt->RC, e, hot );
    }

    /* hot指向x的父结点
       情况一：
       如果x没有左孩子，x结点将被删除，然后用其右孩子代替之
       如果x没有右孩子，x结点将被删除，然后用其左孩子代替之
       情况二：
       如果x结点的左右孩子均存在，则x结点中的元素将被替换为其中序后继结点中的元素值，然后删除该中序后继结点。
       TC = O(h), h为树的高度
    */
    static BinNode<T>* removeAt(BinNode<T>* &x, BinNode<T>* &hot)
    {
        BinNode<T>* del = x;
        BinNode<T>* next = NULL; //实际被删除结点的替代者

        if( !x->LC ) next = x = x->RC; //不存在左孩子， 用右孩子替代
        else if( !x->RC ) next = x = x->LC; //不存在右孩子，用左孩子替代
        else{ //左右孩子均存在, 用中序遍历的直接后继元素替代
            del = x->succ();
            x->data = del->data;
            next = del->RC; //待删除结点只可能有右孩子
            //将待删除结点的可能存在的子结点next正确连接到其父结点上。
            if(x == del->parent) del->parent->RC = next;
            else del->parent->LC = next;
        } //这三条分枝依然可以处理左右孩子均不存在的情况

        hot = del->parent; //记录实际被删除结点的父亲
        if( next ) next->parent = hot; 
        delete del;
        return next; 
    }

public:

    //从根结点开始查找给定元素,返回该元素所在结点
    virtual BinNode<T>* & search(const T& e){ return searchIn(this->_root, e, _hot=NULL); }

    /*插入给定元素，返回该元素所在结点，对于首个结点插入之类的边界情况，均可正确处理
     TC = O(h), h为树的高度
    */
    virtual BinNode<T>* insert(const T& e)
    {
        BinNode<T>*& x = search(e);
        if(!x){ //禁止重复元素
            x = new BinNode<T>(e, _hot); //_hot作为父结点
            ++this->_size;
            x->updateHeightAbove();
        }
        return x;
    }

    /*删除给定元素
      删除成功返回true, 否则返回false
      TC = O(h),  h为树的高度
    */
    virtual bool remove(const T& e)
    {
        BinNode<T>*& x = search(e);// 定位目标结点
        if(!x) return false; //目标元素不存在
        //确认目标存在，此时_hot指向x的父结点
        //分两大类情况实施删除操作，更新全树规模
        removeAt(x, _hot);
        --this->_size;
        this->updateHeightAbove(_hot);
        return true;
    }
};

#endif
