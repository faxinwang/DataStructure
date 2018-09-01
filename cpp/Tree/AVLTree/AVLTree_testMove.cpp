#include<iostream>
#include "AVLTree.hpp"
using namespace std;
using namespace wfx;

int main()
{
    AVLTree<int> t1;
    int a[]={4,3,5, 20, 300, 39, 21, 0, 1, -10, 19, 36, 44, 11};
    int n = sizeof(a) / sizeof(a[0]);
    for(int i=0; i<n; ++i) t1.Insert(a[i]);

    AVLTree<int> t2 = t1;
    cout<<"after assigned from t1 : \nt2 "<<(t2==t1?"==" : "!=")<<" t1"<<endl<<endl;

    AVLTree<int> t3 = move(t1);
    cout<<"after t3 = move(t1) : "<<endl;
    cout<<"t3 " <<(t3==t1? "==" : "!=")<<" t1"<<endl;
    cout<<"t3 " <<(t3==t2? "==" : "!=")<<" t2"<<endl<<endl;
	
	cout<<"after t3 removed element 4:"<<endl;
	t3.Remove(4);
	cout<<"t3 " <<(t3==t2? "==" : "!=")<<" t2"<<endl<<endl;
	
    return 0;
}

/*
after assigned from t1 :
t2 == t1

after t3 = move(t1) :
t3 != t1
t3 == t2

after t3 removed element 4:
t3 != t2
*/
