#ifndef Stack_h
#define Stack_h

#include "../Vector/Vector.hpp"

/* use Vector as the default container */
template<typename T, typename Container = Vector<T> >
class Stack{
	private:
		Container _c;
	public:
		//constructor 
		Stack(){}
		
		//copy constructor
		Stack(Stack& s){ _c = s._c;}
		
		//assignment aperator
		Stack& operator=(Stack& s){
			if(this == &s) return *this;
			_c = s._c;
			return *this;
		}
		
		//push element into the top of  stack
		void push(const T& e){ _c.push_back(e); }
		
		//get the element on the top of stack
		T top(){ return _c.back(); }
		
		//pop top element out of stack
		T pop(){ T tmp = _c.back(); _c.pop_back(); return tmp;}
		
		//the count of elements in the stack
		int size(){ return _c.size(); }
		
		//return trun if stack is empty, else false.
		bool empty(){ return _c.empty(); }
};

#endif
