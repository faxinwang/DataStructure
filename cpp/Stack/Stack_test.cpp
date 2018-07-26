#include <iostream>
#include <string>
#include "Stack.hpp"
using namespace std;
using namespace wfx;

template<class T>
void popN(Stack<T> &s, int n, string str=""){
    n = min(n,s.size());
    if(n==0){
        cout<<"stack is empty"<<endl;
        return;
    }
    cout<<"[ pop "<<n<<" ] " << str<<endl;
    cout<<"size: "<<s.size()<<endl;
    cout<<"empty: "<<boolalpha<<s.empty()<<endl;
    cout<<"top :"<<s.top()<<endl;
    for(int i=0;i<n; ++i) cout<<s.pop()<<' ';
    cout<<endl<<endl;
}

template<class T>
void pushN(Stack<T> &s,T from, T to){
    for(T t= from; t <= to; ++t) s.push(t);
}

int main(){
    Stack<int> s;
	s.reserve(15);
    pushN(s, 1, 15);
    popN(s,5,"after push from 1 to 15" );
    /*
    [ pop 5 ]
	size: 15
	empty: false
	top :15
	15 14 13 12 11
	*/

    pushN(s,20,30);
    Stack<int> s2(s);
    Stack<int> s3;
    s3 = s2;
    
    popN(s,15,"after push from 20 to 30");
    /*
    [ pop 15 ]
	size: 21
	empty: false
	top :30
	30 29 28 27 26 25 24 23 22 21 20 10 9 8 7
	*/

    popN(s,s.size(), "the rest are");
    /*
   [ pop 6 ]
	size: 6
	empty: false
	top :6
	6 5 4 3 2 1
	*/

    popN(s,1);
	//stack is empty
	
	popN(s2,s2.size(),"s2: test copy constructor,copy from s");
	/*
	[ pop 21 ]
	size: 21
	empty: false
	top :30
	30 29 28 27 26 25 24 23 22 21 20 10 9 8 7 6 5 4 3 2 1
	*/

	popN(s3,s3.size(),"s3: test assignment operator,copy from s2");
	/*
	[ pop 21 ]
	size: 21
	empty: false
	top :30
	30 29 28 27 26 25 24 23 22 21 20 10 9 8 7 6 5 4 3 2 1
	*/

    return 0;
}
