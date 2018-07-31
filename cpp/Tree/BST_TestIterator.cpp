#include<iostream>
#include<cstdio>
#include<set>
#include "../Vector/Vector.hpp"
#include "BST.hpp"
using namespace std;
using namespace wfx;

template<typename T>
struct TestEqualWithSet
{
    set<T> st;
    BST<T> bst;

    Vector<T> v1; //for st
    Vector<T> v2; //for bst
    Vector<T> v2_reversed;
    Vector<T> v3; //for Prev()

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

    bool test()
    {
        return v1==v2 && v2_reversed==v3;
    }

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
        typename BST<T>::Iterator it = bst.First();
        while(it.Next())
        {
            cout<<*it<<' ';
            v2.push_back(*it);
        }
        cout<<endl;
        v2_reversed = v2;
        v2_reversed.reverse();
        v3.clear();
        while(it.Prev()) v3.push_back(*it);
    }

    void print(Vector<T>& v)
    {
        for(int i=0,n=v.size(); i<n; ++i) printf("%d ",v[i]);
        cout<<endl;
    }

    void testLast()
    {
        v1.clear();
        v2.clear();
        typename set<T>::reverse_iterator pos=st.rbegin();
        for(; pos!=st.rend(); ++pos) v1.push_back(*pos);

        typename BST<T>::Iterator it = bst.Last();
        while(it.Prev()) v2.push_back(*it);
    }

    void testSelfIncrease()
    {
        v1.clear();
        typename set<T>::iterator pos = st.begin();
        for(; pos != st.end(); ++pos) v1.push_back(*pos);

        v2.clear();
        typename BST<T>::Iterator it = bst.Begin();
        for(; it!=bst.End(); ++it) v2.push_back(*it);
    }

    void testSelfDecrease()
    {
        v1.clear();
        typename set<T>::reverse_iterator pos=st.rbegin();
        for(; pos!=st.rend(); ++pos) v1.push_back(*pos);

        v2.clear();
        typename BST<T>::Iterator it = bst.RBegin();
        for(; it!=bst.End(); --it) v2.push_back(*it);
    }
};


int main(){
    TestEqualWithSet<int> tester;
    Vector<int> numbers;
    int kiss=1;
    int a[]={4,2,6,9, 20, 10, 6, 11, 65, 100, 27, 1, 0, -4, -5, 45, 55, 19};
    for(int i=0,n=sizeof(a)/sizeof(a[0]); i<n; ++i ) tester.insert(a[i]);

    cout<<"Case#"<<kiss++ <<" after inserted some elements :"<<endl;
    cout<<"expected(normal) : "; tester.printSet();
    cout<<"output(normal)   : "; tester.printBST();
    cout<<"expected(reversed):"; tester.print(tester.v2_reversed);
    cout<<"output(reversed)  :"; tester.print(tester.v3);
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" after removed 11 :"<<endl;
    tester.remove(11);
    cout<<"expected(normal) : "; tester.printSet();
    cout<<"output(normal)   : "; tester.printBST();
    cout<<"expected(reversed):"; tester.print(tester.v2_reversed);
    cout<<"output(reversed)  :"; tester.print(tester.v3);
    cout<<(tester.test()? "PASS!" : "Failed")<<endl<<endl;
    
    cout<<"Case#"<<kiss++ <<" test Last() :"<<endl;
    tester.testLast();
    cout<<"expected(reversed):"; tester.print(tester.v1);
    cout<<"output(reversed)  :"; tester.print(tester.v2);
    cout<<(tester.v1==tester.v2? "PASS!" : "Failed")<<endl<<endl;
    
    cout<<"Case#"<<kiss++ <<" test Begin and operator++() :"<<endl;
    tester.testSelfIncrease();
    cout<<"expected:"; tester.print(tester.v1);
    cout<<"output  :"; tester.print(tester.v2);
    cout<<(tester.v1==tester.v2? "PASS!" : "Failed")<<endl<<endl;

    cout<<"Case#"<<kiss++ <<" test RBegin and operator--() :"<<endl;
    tester.testSelfDecrease();
    cout<<"expected(reversed):"; tester.print(tester.v1);
    cout<<"output(reversed)  :"; tester.print(tester.v2);
    cout<<(tester.v1==tester.v2? "PASS!" : "Failed")<<endl<<endl;

    return 0;
}

/*
Case#1 after inserted some elements :
expected(normal) : -5 -4 0 1 2 4 6 9 10 11 19 20 27 45 55 65 100
output(normal)   : -5 -4 0 1 2 4 6 9 10 11 19 20 27 45 55 65 100
expected(reversed):100 65 55 45 27 20 19 11 10 9 6 4 2 1 0 -4 -5
output(reversed)  :100 65 55 45 27 20 19 11 10 9 6 4 2 1 0 -4 -5
PASS!

Case#2 after removed 11 :
expected(normal) : -5 -4 0 1 2 4 6 9 10 19 20 27 45 55 65 100
output(normal)   : -5 -4 0 1 2 4 6 9 10 19 20 27 45 55 65 100
expected(reversed):100 65 55 45 27 20 19 10 9 6 4 2 1 0 -4 -5
output(reversed)  :100 65 55 45 27 20 19 10 9 6 4 2 1 0 -4 -5
PASS!

Case#3 test Last() :
expected(reversed):100 65 55 45 27 20 19 10 9 6 4 2 1 0 -4 -5
output(reversed)  :100 65 55 45 27 20 19 10 9 6 4 2 1 0 -4 -5
PASS!

Case#4 test Begin and operator++() :
expected:-5 -4 0 1 2 4 6 9 10 19 20 27 45 55 65 100
output  :-5 -4 0 1 2 4 6 9 10 19 20 27 45 55 65 100
PASS!

Case#5 test RBegin and operator--() :
expected(reversed):100 65 55 45 27 20 19 10 9 6 4 2 1 0 -4 -5
output(reversed)  :100 65 55 45 27 20 19 10 9 6 4 2 1 0 -4 -5
PASS!

*/