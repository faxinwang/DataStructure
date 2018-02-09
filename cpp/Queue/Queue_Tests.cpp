#include "Queue.hpp"
#include<iostream>
using namespace std;

template<class T>
void popN(Queue<T>& q, int n, string str=""){
    if(q.empty()){
    	cout<<"queue is empty!\n"<<endl;
    	return;
	}
	
	if(n>q.size()) n = q.size();
	cout<<"[pop "<<n<<"]"<<endl;
    cout<<"size: "<<q.size()<<endl;
    cout<<"front: "<<q.front()<<endl;
	cout<<"back: "<<q.back()<<endl;
	if(str!="") cout<<str<<endl;
	for(int i=0; i < n; ++i) cout<<q.pop()<<' ';
	cout<<endl<<endl;
}

template<class T>
void insert(Queue<T>& q, T from, T to){
    for(T i = from; i <= to; ++i) q.push(i);
}

int main(){
    Queue<int> q;
    insert(q, 1, 10);
    popN(q, 5, "the first 5 element are");
    /*
    [pop 5]
	size: 10
	front: 1
	back: 10
	the first 5 element are
	1 2 3 4 5
	*/

    insert(q, 10,30);
	Queue<int> q2(q);
	Queue<int> q3;
	q3 = q2;
    
    popN(q, q.size(), "the rest are: ");
	/*
	[pop 26]
	size: 26
	front: 6
	back: 30
	the rest are:
	6 7 8 9 10 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
	*/
	
	popN(q,5); //empty
	/* queue is empty!
	*/
	
    insert(q,20,30);
    popN(q,10, "after insert from 20 to 30: ");
	/*
	[pop 10]
	size: 11
	front: 20
	back: 30
	after insert from 20 to 30:
	20 21 22 23 24 25 26 27 28 29
	*/    
	
	popN(q,5);
	/*
	[pop 1]
	size: 1
	front: 30
	back: 30
	30
	*/
	
	popN(q2,q2.size(), "q2: test copy constructor, copy from q");
	/*
	[pop 26]
	size: 26
	front: 6
	back: 30
	q2: test copy constructor, copy from q
	6 7 8 9 10 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
	*/
	
	popN(q3,q3.size(), "q3: test assignment operator, copy from q2");
	/*
	[pop 26]
	size: 26
	front: 6
	back: 30
	q3: test assignment operator, copy from q2
	6 7 8 9 10 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
	*/

    return 0;
}


