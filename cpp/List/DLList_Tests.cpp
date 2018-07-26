#include<iostream>
#include<string>
#include<functional>
#include "DLList.hpp"
using namespace std;
using namespace wfx;

//print all elements in lst
template<typename T>
void print(DLList<T>& lst, string hint){
	cout<<"[size:"<<lst.size()<<"]: "<<hint<<endl;
	if(!lst.empty()){
		typename DLList<T>::Iterator pos = lst.begin(), end=lst.end();
		for(; pos!=end; ++pos) cout<<*pos<<" ";
		cout<<endl<<endl;
	}else{
		cout<<"lst is empty"<<endl;
	}
}

bool cmp(int a,int b){ return a<b; }

int main(){
	DLList<int> lst;
	for(int i=0; i<10 ;++i) lst.push_back(i);
	print(lst,"after push_back() from 0 to 9");
	/*
	[size:10]: after push_back() from 0 to 9
	0 1 2 3 4 5 6 7 8 9
	*/ 

	//pop elements at front and back	
	lst.pop_back();
	lst.pop_front();
	print(lst,"after pop_back() and pop_front()");
	/*
	[size:8]: after pop_back() and pop_front()
	1 2 3 4 5 6 7 8
	*/ 
	
	//push elements at front and back
	lst.push_back(15);
	lst.push_front(20);
	print(lst,"after push_back(15) and push_front(20)");
	/*
	[size:10]: after push_back(15) and push_front(20)
	20 1 2 3 4 5 6 7 8 15
	*/ 
	
	cout<<"element at front:"<<lst.front()<<endl;	
	cout<<"element at back:"<<lst.back()<<endl<<endl;
	/*
	element at front:20
	element at back:15
	*/ 
	
	//visit elements by position
	cout<<"element at lst.size()-2: "<<lst.get(lst.size()-2)<<endl<<endl;
	//element at lst.size()-2: 8
	 
	//find elements
	cout<<"find(100):";
	DLList<int>::Iterator pos = lst.find(100,lst.begin(),lst.end());
	if(pos.notNull()) cout<<"found it: "<<*pos<<endl<<endl;
	else cout<<"not found"<<endl<<endl;
	//find(100):not found
	
	cout<<"find(15):";
	pos = lst.find(15,lst.begin(),lst.end());
	if(pos.notNull()) cout<<"found it: "<<*pos<<endl<<endl;
	else cout<<"not found"<<endl<<endl;
	//find(15):found it: 15
	
	//insert elements
	lst.insertBefore(pos, 55);
	lst.insertAfter(lst.begin(),22);
	print(lst,"after insert 55 before 15 and insert 22 after lst.begin()");
	/*
	[size:12]: after insert 55 before 15 and insert 22 after lst.begin()
	20 22 1 2 3 4 5 6 7 8 55 15
	*/ 
	
	//remove element
	lst.erase(lst.find(5,lst.begin(),lst.end()));
	print(lst,"after erase element 5");
	/*
	[size:11]: after erase element 5
	20 22 1 2 3 4 6 7 8 55 15
	*/ 
	
	//test reversed iterator
	cout<<"reversed order:";
	DLList<int>::Iterator rbeg = lst.rBegin(),rend = lst.rEnd();
	for(;rbeg != rend; ++rbeg) cout<<*rbeg<<" ";
	cout<<endl<<endl;
	//reversed order:15 55 8 7 6 4 3 2 1 22 20 
	
	for(int i=0;i<10;++i) lst.push_front(i);
	print(lst,"after push_front from 0 to 9");
	/*
	[size:21]: after push_front from 0 to 9
	9 8 7 6 5 4 3 2 1 0 20 22 1 2 3 4 6 7 8 55 15
	*/ 
	
	int cnt = lst.deduplicate();
	print(lst,"after deduplicate:");
	cout<<cnt<<" elements removed"<<endl<<endl;
	/*
	[size:14]: after deduplicate:
	9 5 0 20 22 1 2 3 4 6 7 8 55 15
	
	7 elements removed
	*/
	
	
	for(int i=0;i<15;++i) lst.push_back(i);
	print(lst,"after push_back from 0 to 14");
	/*
	[size:29]: after push_back from 0 to 14
	9 5 0 20 22 1 2 3 4 6 7 8 55 15 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
	*/ 
	
	lst.selectionSort(lst.begin(), lst.end(), greater<int>());
	print(lst,"after descending sort:");
	/*
	[size:29]: after descending sort:
	55 22 20 15 14 13 12 11 10 9 9 8 8 7 7 6 6 5 5 4 4 3 3 2 2 1 1 0 0
	*/ 
	
	lst.selectionSort(lst.begin(),lst.end(), cmp);
	print(lst, "after ascending sort:");
	/*
	[size:29]: after ascending sort:
	0 0 1 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 10 11 12 13 14 15 20 22 55
	*/ 
	
	cout<<"find(8): ";//use the reversed iterator,and will find the last element with value 8
	DLList<int>::Iterator pos8 = lst.find(8, lst.rBegin(), lst.rEnd());
	if(pos8.notNull()) cout<<"the right element:"<<*(--pos8)<<endl<<endl;
	else cout<<"not found"<<endl<<endl;
	//find(8): the right element:9 
	
	cnt = lst.unquify();
	print(lst,"after make unquify of the sorted lst:");
	cout<<cnt<<" elements removed"<<endl<<endl;
	/*
	[size:19]: after make unquify of the sorted lst:
	0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 20 22 55
	
	10 elements removed
	*/ 
	
	//swap the element just by changing and redirecting the pointers
	lst.Swap(lst.begin(),lst.rBegin());
	DLList<int>::Iterator pos5 = lst.find(5, lst.begin(), lst.end());
	DLList<int>::Iterator pos15 = lst.find(15, lst.begin(), lst.end());
	lst.Swap( pos5,pos15 );
	print(lst,"after Swapped the first element and the last element, 5 and 15");
	/*
	[size:19]: after Swapped the first element and the last element, 5 and 15
	55 1 2 3 4 15 6 7 8 9 10 11 12 13 14 5 20 22 0
	*/

	DLList<int> lst1(lst);
	DLList<int> lst2;
	lst2 = lst1;
	
	lst.clear();
	print(lst,"after clear lst");
	/*
	[size:0]: after clear lst
	lst is empty
	*/

	print(lst1, "lst1: test copy constructor");
	/*
	[size:19]: lst1: test copy constructor
	55 1 2 3 4 15 6 7 8 9 10 11 12 13 14 5 20 22 0
	*/

	print(lst2, "lst2: test assignment operator");
	/*
	[size:19]: lst2: test assignment operator
	55 1 2 3 4 15 6 7 8 9 10 11 12 13 14 5 20 22 0
	*/
	
	return 0;
}
