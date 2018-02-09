#ifndef _DLList_H_
#define _DLList_H_

#include "../require.hpp"
/*
AUTHOR : FAXIN WANG
DATE :	2017/8/10
NOTE: 
	this is a implementation of double-linked list. It has two inner class Node and 
	Iterator. Node is for data storage. Iterator provides some simple but useful 
	interface to visit and operate datas.
*/

template<typename T>
class DLList{
	private:
		struct Node{
			T data;
			Node *prev;
			Node *next;
			Node():prev(NULL),next(NULL){}
			Node(T d, Node *prev,Node *next):data(d),prev(prev),next(next){}
			Node* insertAsPred(const T& x);
			Node* insertAsSucc(const T& x);
		};
		int _size;
		Node *header,*tail;
	protected:
		Node* erase(Node* pos);
		void Swap(Node *a, Node *b);
	public:
		class Iterator{
			private:
				enum Type{Normal, Reversed};
				Type type;
				Node *cur;
				const Node* Trail;
				const Node* Head;
			public:
				//let List<T> to be friend of Iterator so that we can visit cur in functions
				friend class DLList<T>;
				Iterator(Node* node, const Node* he, const Node* tr,Type type)
					:cur(node),Head(he),Trail(tr),type(type){}
				Iterator():cur(0),Trail(0),Head(0),type(Normal){}
				Iterator operator++();		//prefix self increase
				Iterator operator++(int);	//suffix self increase
				Iterator operator--(); 		//prefix self decrease
				Iterator operator--(int);	//suffix self decrease
				bool operator==(const Iterator& it){return cur==it.cur;}
				bool operator!=(const Iterator& it){return cur!=it.cur;}
				T& operator*(){return cur->data;}
				bool notNull(){return cur!=NULL;}
				bool hasNext(){return cur->next!=Trail;}
				bool hasPrev(){return cur->prev!=Head;} 
		};

	public:
		//constructor
		DLList();
		//copy constructor
		DLList(DLList& lst);
		//assignment operator
		DLList& operator=(DLList& lst);
		//return the count of elements in the list
		int size(){return _size;}
		//return turn if size() is 0, else false
		bool empty(){return !_size;}

		//return the data at n,start from 0
		T get(int n);

		//return the first element in the list
		T front(){return header->next->data;}
		//push element into list at front
		void push_front(const T& x){header->insertAsSucc(x); ++_size;}
		//pop element out of list at front
		void pop_front();

		//return the last element in the list
		T back(){return tail->prev->data;}
		//push element into list at back
		void push_back(const T& x){ tail->insertAsPred(x); ++_size; }
		//pop element out of list at back
		void pop_back();
		
		//find x in the range[beg,end)
		Iterator find(const T& x, Iterator beg, Iterator end);
		//insert element before iterator p
		Iterator insertBefore(Iterator p, const T& x);
		//insert element after iterator p
		Iterator insertAfter(Iterator p, const T& x);
		
		//return the Iterator point to the first element
		Iterator begin(){return Iterator(header->next,header,tail,Iterator::Normal);} 
		//return the Iterator point to the position after the last element
		Iterator end(){return Iterator(0,header,tail,Iterator::Normal);}
		//return the right begin iterator point to the last element
		Iterator rBegin(){return Iterator(tail->prev,header,tail,Iterator::Reversed);}
		//return the right end iterator
		Iterator rEnd(){return Iterator(0,header,tail,Iterator::Reversed);}
		//remove element at pos, return a iterator point to previous element
		Iterator erase(Iterator p){return Iterator( erase(p.cur), header, tail, p.type); }
		//remove all duplciates of disordered list,return the number of elements removed
		int deduplicate();
		//remove all duplicates of ordered list, return the number of elements removed
		int unquify();
		void Swap(Iterator a,Iterator b){Swap(a.cur,b.cur);}
		
		/*I don't know the syntax of writing this template function outside of the class
		because it has another template param CMP*/
		template<typename CMP>
		void selectionSort(Iterator beg,Iterator end, CMP cmp){
			for(; beg != end; ++beg){
				Iterator pos = beg,tar = beg;
				for(++pos; pos!=end; ++pos) if(cmp(*pos,*tar)) tar = pos;
				/*here, I called Swap(beg,tar),which just change the pointer of the nodes,
				but it failed, there must be something wrong but I don't konw what it is.*/
				if(beg != tar) {T tmp = *beg; *beg = *tar; *tar = tmp;}
			}
		}
		
		void clear(){ while(header->next != tail) erase(header->next); }
		~DLList(){clear(); delete header; delete tail;}
};

template<typename T>
typename DLList<T>::Node* DLList<T>::Node::insertAsPred(const T& x){
	Node* node = new Node(x, prev,this);
	prev->next = node; prev = node;
	return node;
}
template<typename T>
typename DLList<T>::Node* DLList<T>::Node::insertAsSucc(const T& x) {
	Node *node = new Node(x,this, next);
	next->prev = node;  next = node;
	return node;
}
/*for normal iterator, ++ operator will make it move right
  for reversed iterator, ++ operator will make it move left*/
template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator++(){
	require(cur!=NULL,"DLList<T>::Iterator::operator++(): Iterator run out of range");
	if(type == Normal) cur = cur->next == Trail? 0 : cur->next;
	else cur = cur->prev == Head? 0 : cur->prev;
	return *this;
}
template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator++(int){
	require(cur!=NULL,"DLList<T>::Iterator::operator++(int): Iterator run out of range");
	Iterator tmp = *this;
 	if(type == Normal) cur = cur->next == Trail? 0 : cur->next;
 	else cur = cur->prev == Head? 0 : cur->prev;
 	return tmp;
}
/*for normal iterator, -- operator will make it move left,
  for reversed iterator, -- operator will make it move right*/
template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator--(){
	require(cur!=NULL,"DLList<T>::Iterator::operator--(): Iterator run out of range");
	if(type == Normal) cur = cur->prev == Head? 0 : cur->prev;
	else cur = cur->next == Trail? 0 : cur->next;
	return *this;
}
template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator--(int){
	require(cur!=NULL,"DLList<T>::Iterator::operator--(int): Iterator run out of range");
	Iterator tmp = *this;
	if(type == Normal) cur = cur->prev == Head? 0 : cur->prev;
	else cur = cur->next == Trail? 0 : cur->next;
	return tmp;
}


//constructor
template<typename T>
DLList<T>::DLList(){
	header = new Node;
	tail = new Node;
	header->next = tail;
	tail->prev = header;
	_size = 0 ;
}

//copy constructor
template<typename T>
DLList<T>::DLList(DLList& lst){
header = new Node;
	tail = new Node;
	header->next = tail;
	tail->prev = header;
	_size = 0 ;
	DLList<T>::Iterator pos = lst.begin();
	for(; pos!= lst.end(); ++pos) push_back(*pos);
}

//assignment operator
template<typename T>
DLList<T>& DLList<T>::operator=(DLList<T>& lst){
	clear();
	DLList<T>::Iterator pos = lst.begin();
	for(; pos!= lst.end(); ++pos) push_back(*pos);
}


//get the data of n-th elmeent
template<typename T>
T DLList<T>::get(int n){
	require(0<= n && n< _size,"get():Index out of range");
	Node *p = header->next;
	while(0 < n--) p = p->next;
	return p->data;
}

/*Find x in range [beg,end),return the iterator of first occurence if found,else return end.
  If the iterator are reversed iterators, this function will return the last element in the
  sequence correspondingly.
*/
template<typename T>
typename DLList<T>::Iterator DLList<T>::find(const T& x,Iterator beg, Iterator end){
	for(; beg.notNull() && beg != end && *beg != x; ++beg);
	return beg;
}

//insert x before Node p,return the new inserted node
template<typename T>
typename DLList<T>::Iterator DLList<T>::insertBefore(Iterator p ,const T& x){
	require(p.notNull(), "insertBefore():NULL pointer exception:iterator p is out of range");
	++_size; 
	return Iterator(p.cur->insertAsPred(x), header, tail, p.type);
}

//insert x after Node p, return the new inserted node
template<typename T>
typename DLList<T>::Iterator DLList<T>::insertAfter(Iterator p ,const T& x){
	require(p.cur!=NULL,"insertAfter():NULL pointer exception: argument p is NULL"); 
	++_size; 
	return Iterator(p.cur->insertAsSucc(x), header, tail, p.type);
}

//pop the first element
template<typename T>
void DLList<T>::pop_front(){
	require(_size>0, "pop_front(): can not pop element, DLList is empty");
	erase(header->next);
}

//pop the last element
template<typename T>
void DLList<T>::pop_back(){
	require(_size>0, "pop_back(): can not pop element, DLList is empty");
	erase(tail->prev);
}

template<typename T>
typename DLList<T>::Node* DLList<T>::erase(Node* pos){
	require(pos!=NULL,"DLList<T>::remove(): NULL pointer exception");
	Node* tmp = pos;
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	pos = pos->prev;
	delete tmp; tmp=0;
	--_size;
	return pos;
}

/* for every element cur(start from the second):
find(cur) in range[begin(), cur), if found it, remove it
*/
template<typename T>
int DLList<T>::deduplicate(){
	int oldSize = _size;
	Iterator cur = begin(), nd = end(), p;
	for(++cur; cur != nd; ++cur ) if( (p=find(*cur, begin(), cur)) != cur) erase(p);
	return oldSize - _size;
}

/* remove all duplicates in the ordered list
for every element q(start from the second),p(start from the first):
if(p->data == q->data) remove node q,
else move p to q
*/
template<typename T>
int DLList<T>::unquify(){
	int oldSize = _size;
	if(_size < 2) return 0;
	Node *p = header->next,*q = header->next;
	while(tail != (q=q->next)) 
		if(p->data == q->data) q = erase(q);
		else p = q;
	return oldSize - _size;
}

/*swap the position of node a and b by change the pointers*/
template<typename T>
void DLList<T>::Swap(Node* a,Node* b){
	a->prev->next = b; //1
	a->next->prev = b;
	b->prev->next = a;
	b->next->prev = a;
	
	Node* tmp = a->next;
	a->next = b->next;
	b->next = tmp;
	
	tmp = a->prev;
	a->prev = b->prev;
	b->prev = tmp;
}

#endif 
