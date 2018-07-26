#ifndef Queue_h
#define Queue_h

#include "../List/DLList.hpp"
#include "../util/require.hpp"

NamespaceBegin

/*
Queue, an adapter container, use DLList as the default container.
*/
template<typename T, typename Container = DLList<T> >
class Queue{
	private:
		Container _c;
	public:
		Queue(){}
		
		Queue(Queue& q){ _c = q._c; }
		
		Queue& operator=( Queue& q){ 
			if(this == &q) return *this;
			_c = q._c;
			return *this;
		}
		
		void push(const T& e){ _c.push_back(e); }
		
		T pop(){ T tmp = _c.front(); _c.pop_front(); return tmp; }
		
		T front(){ return _c.front(); }
		
		T back(){ return _c.back(); }
		
		int size(){ return _c.size(); }
		
		bool empty(){ return _c.empty(); }
};

NamespaceEnd

#endif 
