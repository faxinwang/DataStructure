#ifndef BinTree_H
#define BinTree_H

#include "../Stack/Stack.hpp"
#include "../Queue/Queue.hpp"
#include <iostream>
#define stature(p) ( (p)? (p)->height : 1)

template<typename T>
struct BinNode{
	T data;		//data field 
	int height; //the height of this node
	int size(); //count all nodes of this node and its subnodes 
	BinNode<T> *Pa,*LC,*RC; //pointers to its parent,left child and righ child
	BinNode<T>* insertAsLC(const T& e); //insert element e as left(right) child of this node
	BinNode<T>* insertAsRC(const T& e);
	BinNode<T>* next ;	//the next node in inOrder sequence
	/*update the height of this node*/
	int updateHeight(){ return height = 1 + std::max(stature(LC), stature(RC)); }
	void updateHeightAbove();
	//four kinds of traverse orders
//	template<typename VIS> void levelOrder(VIS& vis);
//	template<typename VIS> void prevOrder(VIS& vis);
//	template<typename VIS> void inOrder(VIS& vis);
//	template<typename VIS> void postOrder(VIS& vis);
	//constructor
	BinNode(const T& dat, BinNode<T>* pa):data(dat),Pa(pa),height(1),LC(0),RC(0){}
};

template<typename T>
BinNode<T>* BinNode<T>::insertAsLC(const T& e){
	LC = new BinNode(e,this);
	updateHeightAbove();
 	return LC;
 }

template<typename T>
BinNode<T>* BinNode<T>::insertAsRC(const T& e){ 
	RC = new BinNode(e,this); 
	updateHeightAbove();
	return RC;
}

template<typename T> //TC: O(n)
int BinNode<T>::size(){
	int s = 1; //
	if(LC) s += LC->size();
	if(RC) s += RC->size();
	return s;
}

/*update the height of this node and its ancestors*/
template<typename T>	//TC: O( depth(x) )
void BinNode<T>::updateHeightAbove(){
	BinNode<T>* p = this;
	while(p){
		int oldHeight = p->height;
		int newHeight = p->updateHeight();
		if( newHeight == oldHeight ) break;
		p = p->Pa;
	}
}

template<typename T>
class BinTree{
	protected:
		BinNode<T>* _root;
		virtual int updateHeight(BinNode<T>* x){ return x->updateHeight(); }
		void updateHeightAbove(BinNode<T>* x) { x->updateHeightAbove(); }
	public:
		int size() const { return _root?_root->size() : 0; } 		//the size of all nodes
		bool empty() const { return !_root; }	//judge if the tree is empty
		BinNode<T>* root() const { return _root; }
		
		BinNode<T>* insertAsLC(BinNode<T>* x, const T& e);
		BinNode<T>* insertAsRC(BinNode<T>* x, const T& e);
		
		BinTree();
		BinTree(const T& data);
};

template<typename T>
BinTree<T>::BinTree(){
	_root = 0;
}

template<typename T>
BinTree<T>::BinTree(const T& data){
	_root = new BinNode<T>(data,NULL);
}


/*insert element e as the left child of node x*/
template<typename T>	//TC: O( depth(x) )
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, const T& e){
	BinNode<T> *lc = x->insertAsLC(e);
	updateHeightAbove(x);
	return lc;
}

/*insert element e as the right child of node x*/
template<typename T>	//TC: O( depth(x) )
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, const T& e){
	BinNode<T> *rc = x->insertAsRC(e);
	updateHeightAbove(x);
	return rc;
}

/*recursively traverse all nodes by prevOrder*/
template<typename T, typename VIS>	// TC: O( n )
void prevOrder_recursive(VIS& visit, BinNode<T>* x){
	if( !x ) return ;
	visit( x->data );
	prevOrder_recursive(visit, x->LC);
	prevOrder_recursive(visit, x->RC);
}

/* iteratively traverse all nodes by prevOrder */
template<typename T, typename VIS>		//TC: O(n)
void prevOrder_iterative(VIS& visit, BinNode<T>* x){
	Stack< BinNode<T>* > s;
	if(x) s.push(x);
	while( !s.empty() ){
		x = s.pop();
		visit( x->data );
		/*To get the prevOrder, we heve to let the right child(if exist) push into stack first 
		  because of the "Last In First Out(LIFO)" attribute of stack
		*/
		if( x->RC ) s.push( x->RC ); 
		if( x->LC ) s.push( x->LC );
	}
}

/*a new way to iteratively traverse all nodes by prevOrder*/
template<typename T, typename VIS>
void visitAlongLC(VIS& visit, BinNode<T>* x, Stack<BinNode<T>*> &s){
	while(x){
		visit(x->data);
		s.push(x->RC);
		x = x->LC;
	}
}
template<typename T, typename VIS>		//TC: O(n)
void prevOrder_iterative2(VIS& visit, BinNode<T> *x){
	Stack<BinNode<T>*> s;
	while(true){
		visitAlongLC(visit, x, s);
		if( s.empty() ) break;
		x = s.pop();
	}
}

/* recursively traverse all nodes by inOrder */
template<typename T, typename VIS>		//TC: O(n) 
void inOrder_recursive(VIS& visit, BinNode<T> *x){
	if(x){
		inOrder_recursive(visit, x->LC);
		visit( x->data );
		inOrder_recursive(visit, x->RC);
	}
}

/* Iteratively traverse all nodes by inOrder */
template<typename T>					//TC:O(n)
void goAlongLC(BinNode<T>* x, Stack<BinNode<T>*>& s){
	while(x) { s.push(x); x = x->LC; }
}
template<typename T,typename VIS>
void inOrder_iterative(VIS& visit, BinNode<T>* x){
	Stack<BinNode<T>*> s;
	while(1){
		goAlongLC(x,s);
		if(s.empty()) break;
		x = s.pop();
		visit(x->data);
		x = x->RC;
	}
}

/* post order traverse */
template<typename T,typename VIS>
void postOrder_recursive(VIS& visit, BinNode<T>* x){
	if(x){
		postOrder_recursive(visit, x->LC);
		postOrder_recursive(visit, x->RC);
		visit(x->data);
	}
}

/* level order traverse */
template<typename T, typename VIS>
void levelOrder(VIS& visit, BinNode<T>* x){
	Queue<BinNode<T>*>  Q;
	Q.push(x);
	while(!Q.empty()){
		x = Q.pop();
		visit(x->data);
		if(x->LC) Q.push(x->LC);
		if(x->RC) Q.push(x->RC);
	}
}


#endif 
