#include<iostream>
#include<cstdio>
#include<string>
#include "../../Vector/Vector.hpp"
#include "BST.hpp"
using namespace std;
using namespace wfx;

template<typename T>
void printBST(BST<T>& bst, string hint)
{
    if(hint!="") cout<<hint<<endl;
    typename BST<T>::Iterator pos = bst.Begin();
    for(; pos != bst.End();++pos) cout<<*pos<<' ';
    cout<<endl;
}


int main(){
    BST<int> bst1;
    int kiss=1;
    int a[]={4,2,6,9, 20, 10, 6, 11, 65, 100, 27, 1, 0, -4, -5, 45, 55, 19};
    int numOfElem = sizeof(a)/sizeof(a[0]);
    for(int i=0; i<numOfElem; ++i ) bst1.Insert(a[i]);
	
	cout<<"bst1 size() : "<<bst1.Size()<<endl;
    printBST(bst1,"elements of bst1:");
    cout<<endl;
	
    BST<int> bst2 = bst1; //copy constructor
    cout<<"bst2 size() : "<<bst2.Size()<<endl;
    printBST(bst2,"elements of bst2:");
    if(bst2 == bst1) cout<<"Test copy constructor succeeded"<<endl;
    else cout<<"Test copy constructor failed"<<endl;
    cout<<endl;
    
    
    BST<int> bst3;
    bst3 = bst1;
    cout<<"bst3 size() : "<<bst3.Size()<<endl;
    printBST(bst3,"elements of bst3:");
    if(bst3 == bst1) cout<<"Test assignment operator succeeded"<<endl;
    else cout<<"Test assignment operator failed"<<endl;
    cout<<endl;

    return 0;
}

/*
bst1 size() : 17
elements of bst1:
-5 -4 0 1 2 4 6 9 10 11 19 20 27 45 55 65 100

bst2 size() : 17
elements of bst2:
-5 -4 0 1 2 4 6 9 10 11 19 20 27 45 55 65 100
Test copy constructor succeeded

bst3 size() : 17
elements of bst3:
-5 -4 0 1 2 4 6 9 10 11 19 20 27 45 55 65 100
Test assignment operator succeeded

*/
