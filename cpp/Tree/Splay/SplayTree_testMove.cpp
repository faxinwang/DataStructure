#include<iostream>
#include "SplayTree.hpp"
using namespace wfx;
using namespace std;

int main()
{
    SplayTree<int> st1;
    int a[]={4,3,5, 20, 300, 39, 21, 0, 1, -10, 19, 36, 44, 11};
    int n = sizeof(a) / sizeof(a[0]);
    for(int i=0; i<n; ++i) st1.Insert(a[i]);

    SplayTree<int> st2 = st1;
    cout<<"after st2 assigned from st1 : st2 "<<(st1==st2?"==" : "!=")<<"st1"<<endl;

    SplayTree<int> st3 = move(st1);
    cout<<"after st3 move copied from st1 :"<<endl;
    cout<<"st3 "<<(st1 == st3? "==" : "!=")<<" st1"<<endl;
    cout<<"st3 "<<(st2 == st3? "==" : "!=")<<" st2"<<endl;
    
    cout<<"after st3 removed element 4:"<<endl;
    st3.Remove(4);
    cout<<"st3 "<<(st2 == st3? "==" : "!=")<<" st2"<<endl;

    return 0;
}

/*
after st2 assigned from st1 : st2 ==st1
after st3 move copied from st1 :
st3 != st1
st3 == st2
after st3 removed element 4:
st3 != st2
*/
