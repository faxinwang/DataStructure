#include <iostream>
#include "BST.hpp"
using namespace std;
using namespace wfx;

void visit(int& x){ cout<<x << ' '; }


int main()
{
    BST<int> bst1;
    int a[]={4,3,5, 20, 300, 39, 21, 0, 1, -10, 19, 36, 44, 11};
    int n = sizeof(a) / sizeof(a[0]);
    for(int i=0; i<n; ++i) bst1.Insert(a[i]);
	cout<<"after inserted some elements, bst1 :";
	bst1.InOrderGo(visit); cout<<endl;
	cout<<endl;
	
    BST<int> bst2 = move(bst1);
	cout<<"after bst2 = move(bst1) :"<<endl;
    cout<<"bst2 and bst1 is "<<(bst1 == bst2 ? "equal" : "not equal")<<endl;
	
	cout<<"bst1 : "; bst1.InOrderGo(visit); cout<<endl;
	cout<<endl;
	
	cout<<"bst2 : "; bst2.InOrderGo(visit); cout<<endl;
	cout<<endl;

    return 0;
}

/*
after inserted some elements, bst1 :-10 0 1 3 4 5 11 19 20 21 36 39 44 300

after bst2 = move(bst1) :
bst2 and bst1 is not equal
bst1 :

bst2 : -10 0 1 3 4 5 11 19 20 21 36 39 44 300
*/
