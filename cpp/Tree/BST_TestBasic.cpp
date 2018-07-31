#include<iostream>
#include<cstdio>
#include<set>
#include "../Vector/Vector.hpp"
#include "BST.hpp"
#include "../List/DLList.hpp"
using namespace std;
using namespace wfx;

template<typename T>
struct TestEqualWithSet
{
    set<T> st;
    BST<T> bst;

    Vector<T> v1; //for st
    Vector<T> v2; //for bst

    void insert(T x)
    {
        st.insert(x);
        bst.Insert(x);
    }

    void remove(T x)
    {
        st.erase(x);
        bst.Remove(x);
    }
    
    typename BST<T>::Iterator search(T x){ return bst.Search(x); }
    

    void operator()(const T& x)
    { 
        cout<<x<<' ';
        v2.push_back(x); 
    }

    bool test() { return v1==v2; }

    void printSet() 
    {
        v1.clear();
        typename set<T>::iterator pos;
        for(pos = st.begin(); pos!=st.end(); ++pos)
        {
            v1.push_back(*pos);
            cout<<*pos<<' ';
        }
        cout<<endl;
    }
    
    void printBST()
    { 
        v2.clear();
        bst.InOrderGo(*this); 
        cout<<endl;
    }
};


int main(){
    TestEqualWithSet<int> tester;
    Vector<int> numbers;
    int kiss=1;
    int a[]={4,2,6,9, 20, 10, 6, 11, 65, 100, 27, 1, 0, -4, -5, 45, 55, 19};
    int numOfElem = sizeof(a)/sizeof(a[0]);
    for(int i=0; i<numOfElem; ++i ) tester.insert(a[i]);

    cout<<"Case#"<<kiss++ <<" after inserted some elements :"<<endl;
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 11 :"<<endl;
    tester.remove(11);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" test if 11 exists :"<<endl;
    cout<<"expected : false"<<endl;
    typename BST<int>::Iterator pos = tester.search(11);
    bool existFlag = pos.NotNull() && *pos==11;
    cout<<"output   : "<<(existFlag? "true" : "false")<<endl;
    cout<<(existFlag==false? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" test if 100 exists :"<<endl;
    cout<<"expected : true"<<endl;
    pos = tester.search(100);
    existFlag = pos.NotNull() && *pos==100;
    cout<<"output   : "<<(existFlag? "true" : "false")<<endl;
    cout<<(existFlag==true? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" test tree size :"<<endl;
    cout<<"expected : 16"<<endl;
    cout<<"output   : "<<tester.bst.Size()<<endl;
    cout<<(tester.bst.Size()==16? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 55 :"<<endl;
    tester.remove(55);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 10 :"<<endl;
    tester.remove(10);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 6 :"<<endl;
    tester.remove(6);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 19 :"<<endl;
    tester.remove(19);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 20 :"<<endl;
    tester.remove(20);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 0 :"<<endl;
    tester.remove(0);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 27 :"<<endl;
    tester.remove(27);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 45 :"<<endl;
    tester.remove(45);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 4 :"<<endl;
    tester.remove(4);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 9 :"<<endl;
    tester.remove(9);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed -5 :"<<endl;
    tester.remove(-5);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;   

    cout<<"Case#"<<kiss++ <<" after removed 1:"<<endl;
    tester.remove(1);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;   

    cout<<"Case#"<<kiss++ <<" after removed 2:"<<endl;
    tester.remove(2);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl; 

    cout<<"Case#"<<kiss++ <<" after removed -4:"<<endl;
    tester.remove(-4);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl; 

    cout<<"Case#"<<kiss++ <<" after removed 100:"<<endl;
    tester.remove(100);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl; 

    cout<<"Case#"<<kiss++ <<" after removed 65:"<<endl;
    tester.remove(65);
    cout<<"expected : "; tester.printSet();
    cout<<"output   : ";   tester.printBST();
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl; 

    cout<<"Case#"<<kiss++ <<" test if tree is empty:"<<endl;
    cout<<"expected : true"<<endl;
    cout<<"output   : "<<(tester.bst.Empty()?"true" : "false")<<endl;
    cout<<(tester.bst.Empty()==true? "PASS!" : "Failed")<<endl<<endl; 

    return 0;
}

/*
Case#1 after inserted some elements :
expected : -5 -4 0 1 2 4 6 9 10 11 19 20 27 45 55 65 100
output   : -5 -4 0 1 2 4 6 9 10 11 19 20 27 45 55 65 100
PASS!

Case#2 after removed 11 :
expected : -5 -4 0 1 2 4 6 9 10 19 20 27 45 55 65 100
output   : -5 -4 0 1 2 4 6 9 10 19 20 27 45 55 65 100
PASS!

Case#3 test if 11 exists :
expected : false
output   : false
PASS!

Case#4 test if 100 exists :
expected : true
output   : true
PASS!

Case#5 test tree size :
expected : 16
output   : 16
PASS!

Case#6 after removed 55 :
expected : -5 -4 0 1 2 4 6 9 10 19 20 27 45 65 100
output   : -5 -4 0 1 2 4 6 9 10 19 20 27 45 65 100
PASS!

Case#7 after removed 10 :
expected : -5 -4 0 1 2 4 6 9 19 20 27 45 65 100
output   : -5 -4 0 1 2 4 6 9 19 20 27 45 65 100
PASS!

Case#8 after removed 6 :
expected : -5 -4 0 1 2 4 9 19 20 27 45 65 100
output   : -5 -4 0 1 2 4 9 19 20 27 45 65 100
PASS!

Case#9 after removed 19 :
expected : -5 -4 0 1 2 4 9 20 27 45 65 100
output   : -5 -4 0 1 2 4 9 20 27 45 65 100
PASS!

Case#10 after removed 20 :
expected : -5 -4 0 1 2 4 9 27 45 65 100
output   : -5 -4 0 1 2 4 9 27 45 65 100
PASS!

Case#11 after removed 0 :
expected : -5 -4 1 2 4 9 27 45 65 100
output   : -5 -4 1 2 4 9 27 45 65 100
PASS!

Case#12 after removed 27 :
expected : -5 -4 1 2 4 9 45 65 100
output   : -5 -4 1 2 4 9 45 65 100
PASS!

Case#13 after removed 45 :
expected : -5 -4 1 2 4 9 65 100
output   : -5 -4 1 2 4 9 65 100
PASS!

Case#14 after removed 4 :
expected : -5 -4 1 2 9 65 100
output   : -5 -4 1 2 9 65 100
PASS!

Case#15 after removed 9 :
expected : -5 -4 1 2 65 100
output   : -5 -4 1 2 65 100
PASS!

Case#16 after removed -5 :
expected : -4 1 2 65 100
output   : -4 1 2 65 100
PASS!

Case#17 after removed 1:
expected : -4 2 65 100
output   : -4 2 65 100
PASS!

Case#18 after removed 2:
expected : -4 65 100
output   : -4 65 100
PASS!

Case#19 after removed -4:
expected : 65 100
output   : 65 100
PASS!

Case#20 after removed 100:
expected : 65
output   : 65
PASS!

Case#21 after removed 65:
expected :
output   :
PASS!

Case#22 test if tree is empty:
expected : true
output   : true
PASS!

*/
