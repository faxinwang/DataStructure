#include<iostream>
#include<string>
#include"Vector.hpp"
using namespace std;

template<typename T>
void print(Vector<T>& v,string hint){
	cout<<"///"<<hint<<endl; 
	for(int i=0;i<v.size();++i) cout<<v[i]<<" ";
	cout<<endl<<endl;
}

template<typename T>
void printInfo(Vector<T>& v){
	cout<<"size:"<<v.size()<<endl;
	cout<<"capacity:"<<v.capacity()<<endl;
	cout<<endl;
}

int main(){
	Vector<int> v(10);
	for(int i=0;i<10;++i) v.push_back(i);
	print(v,"after push back from 0 to 9");		//0 1 2 3 4 5 6 7 8 9 
	printInfo(v);
	/*
	size:10
	capacity:10
	*/	
	
	for(int i=2;i<6;++i) v.push_back(i);
	print(v,"after push back from 2 to 5");		//0 1 2 3 4 5 6 7 8 9 2 3 4 5
	printInfo(v);	
	/*
	size:14
	capacity:20
	*/ 
	
	int cnt = v.deduplicate();
	print(v,"after deduplicate");				//0 1 2 3 4 5 6 7 8 9
	cout<<"num of elements removed:"<<cnt<<endl<<endl; //4 
	printInfo(v);
	/*
	size:10
	capacity:20
	*/ 
	
	v.increase(Increase<int>());
	print(v,"after increase");					//1 2 3 4 5 6 7 8 9 10
	
	Sum<int> s = v.sum(Sum<int>());
	cout<<"sum = "<<s.sum<<endl;				//55
	s = v.traverse(s);
	cout<<"sum = "<<s.sum<<endl;				//110 
	
	for(int i=1; i<10; i+=2) v.insert(i, i*i);
	print(v,"after insertion:");				//1 1 2 9 3 25 4 49 5 81 6 7 8 9 10
	printInfo(v);
	/*
	size:15
	capacity:20
	*/ 
	
	v.bubbleSort(v.size()/2, v.size());	 		//1 1 2 9 3 25 4 5 6 7 8 9 10 49 81
	print(v,"after sort right half range by bubbleSort()");
	
	v.mergeSort(0,v.size());					//1 1 2 3 4 5 6 7 8 9 9 10 25 49 81
	print(v,"after sort whole range by mergeSort()");
	
	v.insert(v.binSearch(15,0,v.size())+1,15);
	v.insert(v.binSearch(12,0,v.size())+1,12);
	v.insert(v.binSearch(9,0,v.size())+1,9);
	print(v,"after insert 15, 12 and 9");		//1 1 2 3 4 5 6 7 8 9 9 9 10 12 15 25 49 81 
	
	printInfo(v);
	/*
	size:18
	capacity:20
	*/ 
	
	cnt = v.uniquify();
	print(v,"after uniquified:");				//1 2 3 4 5 6 7 8 9 10 12 15 25 49 81
	printf("number of elements removed:%d\n",cnt);	//3 
	
	printInfo(v);
	/*
	size:15
	capacity:20
	*/ 
	
	
	Vector<string> v2(10,5, "hello world");
	print(v2, "after constructed:");
	printInfo(v2);
	
	Vector<string> v3(v2); 	print(v3, "test copy constructor");
	Vector<string> v4=v2;	print(v4, "test copy constructor");
	Vector<string> v5;		
	v5 = v2;				print(v5, "test assign operator");

	

	return 0;
}
