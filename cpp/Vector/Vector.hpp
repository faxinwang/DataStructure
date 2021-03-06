#ifndef Vector_H
#define Vector_H

#include "../util/require.hpp"

NamespaceBegin

template<typename T>
void swap(T &a, T &b){ T t=a; a = b; b = t;}

template<typename T>
struct Increase
{
	virtual void operator()(T& x){++x;} //call ++ operator
};

template<typename T>
struct Sum
{
	T sum;
	virtual void operator()(T& x){ sum += x;}
};

/** 以下实现了 >, >=, <, <=, ==, != 六种比较器
 *  使用时, T代表的类型只需实现 <, <=, == 三种运算符即可.
 */
template<typename T>
struct Comparator
{
	virtual bool operator()(const T &a, const T &b)=0;
};

template<typename T>
struct Greater : Comparator<T>
{
	bool operator()(const T&a, const T&b){return b<a;}
};

template<typename T>
struct GreaterEqual : Comparator<T>
{
	bool operator()(const T&a, const T&b){return b<=a;}
};

template<typename T>
struct Less : Comparator<T>
{
	bool operator()(const T&a, const T&b){return a<b;}
};

template<typename T>
struct LessEqual : Comparator<T>
{
	bool operator()(const T&a, const T&b){return a<=b;}
};

template<typename T>
struct Equal : Comparator<T>
{
	bool operator()(const T&a, const T&b){return a==b;}
};

template<typename T>
struct NotEqual : Comparator<T>
{
	bool operator()(const T&a, const T&b){return !(a==b);}
};


template<typename T>
class Vector
{
private:
	int _size, _cap; 
	T* _elem; //if not assign to 0, bug will occur in copy() funcation 
protected:
	void copy(T* const a,int low,int high);
	void expand();//double size
	int bubble(int low,int high); //call by bubbleSort() 
	void merge(int low, int mid, int high); //call by mergeSort ()

	/**使用给定的比较器将该vector中的元素与另一个vector中的对应元素逐一进行比较
	 * 1.如果两个vector中的元素个数不相同, 则返回false
	 * 2.只要有一对元素的比较结果为false, 就返回false
	 * 3.当所有的比较结果都为true时,才返回true
	 * 4.this指向的vector中的元素作为比较器的第一个参数,传入参数vector中的元素作为
	 *   比较器的第二个参数
	 */
	template<typename CMP>
	bool compareAll(const Vector& v, CMP cmp)
	{
		if(_size != v._size) return false;
		for(int i=0; i<_size; ++i)
			if( cmp(_elem[i], v._elem[i]) == false ) return false;
		return true;
	}

public:
	//init with n elements of the given value
	Vector<T>(int cap=10, int size=0, T value=T()):_cap(cap),_size(size){ 
		_elem = new T[cap];
		int i;
		for(i=0; i<size; ++i) _elem[i] = value; 
//			for(; i<cap; ++i) _elem[i] = T();
	}
	//init from range a[low,high)
	Vector<T>(T* const a, int low, int high):_elem(0) { copy(a,low,high); }
	//init from range _elem[low,high) of another Vector
	Vector<T>(const Vector<T>& v, int low,int high):_elem(0) { copy(v._elem,low,high);}
	//init from another Vector
	Vector<T>(const Vector<T>& v):_elem(0) { copy(v._elem, 0, v.size());} 

	//move constructor
	Vector<T>(Vector<T>&& v):_size(v._size), _cap(v._cap), _elem(v._elem)
	{
		v._size = 0;
		v._cap = 10;
		v._elem = new T[10];
	}

	//assign operator
	Vector<T>& operator=(const Vector<T>& v){ 
		if(this == &v) return *this; //do not copy from itself
		if(_elem) delete[] _elem;
		_cap = v._cap;
		_size = v._size;
		_elem = new T[_cap];
		for(int i=0; i<_size; ++i) _elem[i] = v._elem[i];
		return *this; 
	}
	//destructor
	~Vector<T>(){if(_elem) delete[] _elem; _elem=0;}
	
	//number of elements
	int size()const {return _size;}
	//length of internal array
	int capacity()const {return _cap;}
	//return true if size()==0, else false
	bool empty()const {return _size==0;}
	//clear all elements
	void clear(){ _size=0; }
	
	// 0 <= i < _size 
	T& operator[](int i){ 
		stringstream ss;
		require(0<= i && i<_size,(ss<<"error: index out of range size="<<_size<<" index="<<i,ss));
		return _elem[i]; 
	}
	const T& operator[](int i)const{
		stringstream ss;
		require(0<= i && i<_size,(ss<<"error: index out of range size="<<_size<<" index="<<i,ss));
		return _elem[i]; 
	}
	//insert element x to pos
	int insert(int pos, const T& x);
	//delete range, return (end - beg)
	int remove(int beg,int end);
	//remove element at pos, return _elem[pos]
	T remove(int pos);
	//liner find,return a pos 
	int find(const T& x,int beg,int end) const;
	//binary search
	int binSearch(const T& x,int beg,int end)const;
	//remove duplicates from the disordered sequence,return the num of elements removed
	int deduplicate();
	//check if elements is in order,return the number of reversed consecutive pairs
	int disordered()const;
	//remove the duplicates from the ordered sequence,return the num of elements removed
	int uniquify();
	//reserve place
	bool reserve(int newCap);
	
	void push_back(const T& x) { insert(_size,x); }
	void push_front(const T& x) { insert(0,x); }
	void pop_back() { --_size; }
	void pop_front() { remove(0); }
	T back() { return _elem[_size-1]; }
	T front() { return _elem[0]; }
	
	//traverse all elements
	//function pointer
	void traverse(void (*visit)(T&)){ for(int i=0;i<_size;++i) visit(_elem[i]); }
	//use function object, more power then function pointer, return Functor
	template<typename Functor>
	Functor traverse(Functor op){for(int i=0;i<_size;++i) op(_elem[i]); return op; }
	//apply ++ operation on every element in _elem[0,_size)
	template<typename Functor>
	Functor increase(Functor op = Increase<T>()){ return traverse( op ); }
	//get sum of all elements through Functor
	template<typename Functor>
	Functor sum(Functor op = Sum<T>()){ return traverse( op ); }
	
	//sort algorithms
	void bubbleSort(int low,int high);
	void mergeSort(int low,int high);

	//added on 2018/7/22
	bool operator==(const Vector& v) { return compareAll(v, Equal<T>());  		}

	bool operator<(const Vector& v)  { return compareAll(v, Less<T>()); 		}

	bool operator<=(const Vector& v) { return compareAll(v, LessEqual<T>()); 	}

	bool operator>(const Vector& v)  { return compareAll(v, Greater<T>());   	}
	
	bool operator>=(const Vector& v) { return compareAll(v, GreaterEqual<T>()); }

	//added on 
	void reverse()
	{
		for(int i=0,j=_size-1; i<j; ++i,--j) swap(_elem[i],_elem[j]);
	}
};

/*
1.delete the old _elem 
2.resize capacity to the size of the given range
3.copy elements of the given range to _elem, and update _size
*/
template<typename T>	//TC: O(N)
void Vector<T>::copy(T* const a,int low,int high){
	stringstream ss;
	require(0<=low && low < high, 
		(ss<<"copy():Illegal arguments: [0<=low && low < high] is required. low="<<low<<" high="<<high, ss));
	if(_elem) delete[] _elem; //step1
	_elem = new T[_cap = (high - low + 1)];//step2
	_size = 0;
	while(low < high) _elem[_size++] = a[low++]; //step3
}

/*
1.judge size
2.reallocate double size
3.copy old elements
*/
template<typename T>	//TC: O(N)
void Vector<T>::expand(){
	if(_size < _cap) return; //no need to expand
	T* oldElem = _elem;
	_elem = new T[ _cap<<=1 ]; //double size 
	for(int i=0;i<_size;++i) _elem[i] = oldElem[i];
	delete[] oldElem;
}

/*
1.expand()
2.right move
3._elem[pos] = x, _size++;
*/
template<typename T>  //0 <= pos <= _size	TC:O(N-pos) = O(N)
int Vector<T>::insert(int pos,const T& x){
	stringstream ss;
	require(0 <= pos && pos<=_size, (ss<<"insert position out of range size="<<_size<<" pos="<<pos, ss) );
	expand();
	for(int i=_size; i>pos; --i) _elem[i] = _elem[i-1];
	_elem[pos] = x; ++_size;
	return pos;
}

/*
delete element in range [beg, end)
1.judge if range is legal
2.remove range by override
*/
template<typename T>	// TC: O(N-pos)
int Vector<T>::remove(int beg,int end){
	stringstream ss;
	require(beg < end,
		(ss<<"remove():Illegal arguments: [begin < end] is required. begin="<<beg<<" end="<<end, ss));
	require(0<=beg && end <= _size, 
		(ss.str(""),ss<<"remove(): index out of range! beg="<<beg<<" end="<<end<<" size="<<_size,ss));
	if(beg == end) return 0;
	while(end < _size) _elem[beg++] = _elem[end++];
	_size = beg;
	return end - beg;
}

/*call remove(pos, pos+1), return _elem[pos]
*/
template<typename T> //0 <= pos < _size		TC: O(N-pos) = O(N)
T Vector<T>::remove(int pos){
	stringstream ss; 
	require(0<=pos && pos<_size, (ss<<"remove():Index out of range. index="<<pos<<" size="<<_size,ss));
	T tmp = _elem[pos];
	remove(pos,pos+1);
	return tmp;
}

/*linear search x in range _elem[beg,end),return a pos which can indicate the result
*/
template<typename T> //0 <= beg <  end <= _size		TC: O(end - beg) = O(n)
int Vector<T>::find(const T& x,int low,int high)const{
	stringstream ss;
	require(low < high, (ss<<"find():Illegal arguments: [low < high] is required, low="<<low<<" high="<<high, ss));
	require(0<=low && high<= _size,(ss.str(""), ss<<"index out of range low="<<low<<" high="<<high, ss));
	while( (low < high) && (x != _elem[low])) ++low;
	return low; // if beg < end found it, else not found
}

/*
binary Search:
return the right most position which is suitable for insertion:
the position of the last element which is no greater then x,
after which is where x should be inserted in the ordered sequence.
*/
template<typename T>	//TC: O(logN)
int Vector<T>::binSearch(const T& x, int low,int high)const{
	require(low < high, "binSearch():Illegal arguments: [low < high] is required");
	int mid;
	while(low < high){
		mid = low + (high-low)/2;
		x<_elem[mid]? high = mid : low=mid+1;
	}
	return low-1;
}

/* remove all duplicates,return the number of elements removed
for every current element _elem[cur], find if there is a duplicate in ragne[0,cur),
if find a duplicate, then remove current element, else ++cur.
return the number of elements removed
*/
template<typename T>	// TC: O(n^2)
int Vector<T>::deduplicate(){
	int oldSize = _size;
	int cur=1;
	while(cur < _size) find(_elem[cur],0,cur) < cur? remove(cur) : ++cur;
	return oldSize - _size;
}

/*check if elements is in order,return the number of reversed consecutive pairs,
which can measure the extent of disorder
*/
template<typename T>	//TC: O(n)
int Vector<T>::disordered()const{
	int n=0; 
	for(int i=1;i<_size;++i) if(_elem[i-1] > _elem[i]) ++n;
	return n;
}

/*remove the duplicates from the ordered sequence,return the num of elements removed
*/
template<typename T>	// TC: O(n)
int Vector<T>::uniquify(){
	int i=0,j=0;
	// if found a different element, copy it to the right of elem[i]
	while(++j<_size) if(_elem[i] != _elem[j]) _elem[++i] = _elem[j];
	_size = ++i;
	return j-i; //num of elements removed
}

/*
reserve place for future insertion
if newSize < oldSize or malloc new memory failed, return false
otherwise copy all elements to new array and return true
*/
template<typename T>
bool Vector<T>::reserve(int newCap){
	if(newCap <= _cap) return false;
	T* arr = new T[newCap];
	if(arr == 0) return false;
	for(int i=0; i<_size; ++i) arr[i] = _elem[i];
	delete[] _elem;
	_elem = arr;
	_cap = newCap;
	return true;
}


/*advanced bubble sort
bubble() returns the position of the last swap,which means the range [last,high)
is already in order, so we can set high = last to shrink the range to be sorted.
*/
template<typename T>	//TC:O(N^2)
void Vector<T>::bubbleSort(int low,int high){
	require(low < high, "bubbleSort():Illegal arguments: [low < high] is required");
	while(low < (high=bubble(low,high)));
}
template<typename T>
int Vector<T>::bubble(int low,int high){
	int last = low; // record the last position swapped
	while(++low < high) // stable sort
		if(_elem[low-1] > _elem[low]) { swap(_elem[low-1],_elem[low]); last=low; }
	return last;
}


template<typename T> 	//TC: O(NlogN)	SC:O(N/2)
void Vector<T>::mergeSort(int low,int high){
	require(low < high, "mergeSort():Illegal arguments: [low < high] is required");
	if(high - low < 2) return; // less then two elem,already in order
	int mid = low + (high - low) / 2;
	mergeSort(low,mid);
	mergeSort(mid,high);
	merge(low,mid,high);
}

template<typename T>
void Vector<T>::merge(int low,int mid,int high){
	T* left = new T[mid-low]; //left half range
	T* right = _elem+mid;
	for(int i=low; i < mid; left[i-low] = _elem[i++]);
	int i=0,j=0,k=low, la=mid-low, lb=high-mid;
	while(i<la && j<lb) left[i]<right[j] ? _elem[k++]=left[i++] : _elem[k++]=right[j++];
	while(i<la) _elem[k++] = left[i++];
	delete[] left;
}


NamespaceEnd
#endif 
