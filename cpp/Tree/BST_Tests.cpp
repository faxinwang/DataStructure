#include<iostream>
#include<cstdio>
#include<sstream>
#include "BST.hpp"
using namespace std;

int a[100]={345,20,90,6,110,200,210,23,40,97,100}; //11个

void visit(int t){ cout<<t<<" "; }

template<typename T>
void printAll(BST<T>& bst, string str){
    cout<<str<<endl;
    cout<<"size: "<<bst.size()<<endl;
    inOrder_iterative(visit, bst.root());
    cout<<endl<<endl;
}

int main(){
    BST<int> bst;
    for(int i=0; a[i]; ++i) bst.insert( a[i] );
    printAll(bst, "after inserted all elements in the array:");
    /*
    after inserted all elements in the array:
    size: 11
    6 20 23 40 90 97 100 110 200 210 345
    */

    //重复插入相同的元素
    for(int i=0; a[i]; ++i) bst.insert( a[i] );
    printAll(bst, "after inserted those elements again:");
    /*
    after inserted those elements again:
    size: 11
    6 20 23 40 90 97 100 110 200 210 345
    */

    //查找元素a[2]
    BinNode<int>* a2 =  bst.search(a[2]);
    if(a2) printf("found a[2] : %d\n", a2->data);
    else printf("a[2] is not found in BST.\n");
    /*
    found a[2] : 90
    */


    //删除元素a[2]
    bst.remove(a[2]);
    printAll(bst, "after removed a[2]:");
    /*
    after removed a[2]:
    size: 10
    6 20 23 40 97 100 110 200 210 345
    */

    //再次查找元素a[2]
    a2 =  bst.search(a[2]);
    if(a2) printf("found a[2] : %d\n", a2->data);
    else printf("a[2] is not found in BST.\n");
    /*
    a[2] is not found in BST.
    */

    //插入元素a[2]
    bst.insert(a[2]);
    printAll(bst, "after inserted a[2]:");
    /*
    after inserted a[2]:
    size: 11
    6 20 23 40 90 97 100 110 200 210 345
    */
    
    //remove all elements one by one
    for(int i=0; a[i]; ++i){
        bst.remove(a[i]);
        stringstream ss;
        ss<<"after removed "<<a[i];
        printAll(bst, ss.str());
    }
    /*
    after removed 345
    size: 10
    6 20 23 40 90 97 100 110 200 210

    after removed 20
    size: 9
    6 23 40 90 97 100 110 200 210

    after removed 90
    size: 8
    6 23 40 97 100 110 200 210

    after removed 6
    size: 7
    23 40 97 100 110 200 210

    after removed 110
    size: 6
    23 40 97 100 200 210

    after removed 200
    size: 5
    23 40 97 100 210

    after removed 210
    size: 4
    23 40 97 100

    after removed 23
    size: 3
    40 97 100

    after removed 40
    size: 2
    97 100

    after removed 97
    size: 1
    100

    after removed 100
    size: 0
    */

    return 0;
}
