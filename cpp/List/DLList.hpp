#ifndef _DLList_H_
#define _DLList_H_

#include "../util/require.hpp"
/*
AUTHOR : FAXIN WANG
DATE :	2017/8/10
NOTE: 
	this is a implementation of double-linked list. It has two inner class Node and 
	Iterator. Node is for data storage. Iterator provides some simple but useful 
	interface to visit and operate datas.
*/

NamespaceBegin

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
		Node *head,*tail;
	protected:
		Node* erase(Node* pos);
		void Swap(Node *a, Node *b);
	public:
		class Iterator{
			private:
				enum Type{Normal, Reversed};
				Type type;
				Node *cur;
				const Node* Tail;
				const Node* Head;
			public:
				//let List<T> to be friend of Iterator so that we can visit cur in functions
				friend class DLList<T>;
				Iterator(Node* cur, const Node* head, const Node* tail, Type type=Normal)
					:cur(cur),Head(head),Tail(tail),type(type){}

				Iterator():cur(0),Tail(0),Head(0),type(Normal){}

				Iterator& operator++();		//prefix self increase
				Iterator operator++(int);	//suffix self increase
				Iterator& operator--(); 		//prefix self decrease
				Iterator operator--(int);	//suffix self decrease
				bool operator==(const Iterator& it){return cur==it.cur;}
				bool operator!=(const Iterator& it){return cur!=it.cur;}
				T& operator*(){return cur->data;}
				bool notNull(){return cur!=NULL;}
				bool hasNext(){return cur->next!=Tail;}
				bool hasPrev(){return cur->prev!=Head;} 
		};

	public:
		//constructor
		DLList();
		//copy constructor
		DLList(DLList& lst);
		//move copy constructor
		DLList(DLList &&lst);
		//assignment operator
		DLList& operator=(DLList& lst);
		//return the count of elements in the list
		int size()const {return _size;}
		//return turn if size() is 0, else false
		bool empty()const {return !_size;}

		//return the data at n,start from 0
		T get(int n) const;

		//return the first element in the list
		T front(){return head->next->data;}
		//push element into list at front
		void push_front(const T& x){head->insertAsSucc(x); ++_size;}
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
		Iterator begin()const {return Iterator(head->next, head, tail, Iterator::Normal);} 
		//return the Iterator point to the position after the last element
		Iterator end()const {return Iterator(tail, head, tail );}
		//return the right begin iterator point to the last element
		Iterator rBegin()const {return Iterator(tail->prev, head, tail, Iterator::Reversed);}
		//return the right end iterator
		Iterator rEnd()const {return Iterator(head, head, tail, Iterator::Reversed);}
		//remove element at pos, return a iterator point to the previous position of the removed element
		Iterator erase(Iterator p){return Iterator( erase(p.cur), head, tail, p.type); }
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
		
		void clear(){ while(head->next != tail) erase(head->next); }
		~DLList(){clear(); delete head; delete tail;}

		bool operator==(const DLList<T>& lst) const
		{
			if(_size != lst._size) return false;
			Iterator p1 = this->begin(), p2 = lst.begin();
			for(Iterator end = this->end(); p1 != end; ++p1, ++p2 ) if(*p1 != *p1) return false;
			return true;
		}

		bool operator!=(const DLList<T>& lst){ return ! operator==(lst); }

		
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
typename DLList<T>::Iterator& DLList<T>::Iterator::operator++(){
	require(cur!=NULL,"DLList<T>::Iterator::operator++(): Iterator run out of range");
	if(type == Normal) cur = cur == Tail? cur : cur->next;
	else cur = cur == Head? cur : cur->prev;
	return *this;
}
template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator++(int){
	require(cur!=NULL,"DLList<T>::Iterator::operator++(int): Iterator run out of range");
	Iterator tmp = *this;
 	operator++();
 	return tmp;
}
/*for normal iterator, -- operator will make it move left,
  for reversed iterator, -- operator will make it move right*/
template<typename T>
typename DLList<T>::Iterator& DLList<T>::Iterator::operator--(){
	require(cur!=NULL,"DLList<T>::Iterator::operator--(): Iterator run out of range");
	if(type == Normal) cur = cur == Head? cur : cur->prev;
	else cur = cur == Tail? cur : cur->next;
	return *this;
}
template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator--(int){
	require(cur!=NULL,"DLList<T>::Iterator::operator--(int): Iterator run out of range");
	Iterator tmp = *this;
	operator--();
	return tmp;
}


//constructor
template<typename T>
DLList<T>::DLList(){
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
	_size = 0 ;
}

//copy constructor
template<typename T>
DLList<T>::DLList(DLList& lst){
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
	_size = 0 ;
	DLList<T>::Iterator pos = lst.begin();
	for(; pos!= lst.end(); ++pos) push_back(*pos);
}

//move constructor
template<typename T>
DLList<T>::DLList(DLList &&lst){
	_size = lst._size;
	head = lst.head;
	tail = lst.tail;
	lst.head = new Node;
	lst.tail = new Node;
	lst.head->next = lst.tail;
	lst.tail->prev = lst.head;
	lst._size = 0;
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
T DLList<T>::get(int n) const {
	require(0<= n && n< _size,"get():Index out of range");
	Node *p = head->next;
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
	return Iterator(p.cur->insertAsPred(x), head, tail, p.type);
}

//insert x after Node p, return the new inserted node
template<typename T>
typename DLList<T>::Iterator DLList<T>::insertAfter(Iterator p ,const T& x){
	require(p.cur!=NULL,"insertAfter():NULL pointer exception: argument p is NULL"); 
	++_size; 
	return Iterator(p.cur->insertAsSucc(x), head, tail, p.type);
}

//pop the first element
template<typename T>
void DLList<T>::pop_front(){
	require(_size>0, "pop_front(): can not pop element, DLList is empty");
	erase(head->next);
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
	Node *p = head->next,*q = head->next;
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


NamespaceEnd
#endif 
