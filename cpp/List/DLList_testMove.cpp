#include<iostream>
#include<string>
#include "DLList.hpp"
using namespace std;
using namespace wfx;

template<typename T>
void print(const DLList<T>& lst, string hint)
{
    cout<<hint<<endl;
    auto pos = lst.begin();
    for(auto end = lst.end(); pos != end; ++pos) cout<<*pos<<' ';
    cout<<endl;
}

int main()
{
    DLList<int> list1;
    for(int i=0; i<10; ++i) list1.push_back(i);
    print(list1, "after insert from 0 to 9, list1:");
    cout<<endl; 
	
    DLList<int> list2 = list1;
    print(list2, "after assigned from list1, list2: ");
    cout<<"list1 "<< (list1 == list2 ? "==":"!=")<<"list2"<<endl;
    cout<<endl;

    DLList<int> list3 = move(list1);
    print(list1, "after move assigned to list3, list1 : ");
    print(list3, "after move assigned from list1, list3: ");
    cout<<"list1 "<< (list1 == list3 ? "==":"!=")<<"list3"<<endl;
    cout<<endl;
	
	DLList<int> list4 = move(list3);
	print(list3, "after move assigned to list4, list3 : ");
    print(list4, "after move assigned from list3, list4: ");
    cout<<endl;
    
    return 0;
}

/*
after insert from 0 to 9, list1:
0 1 2 3 4 5 6 7 8 9

after assigned from list1, list2:
0 1 2 3 4 5 6 7 8 9
list1 ==list2

after move assigned to list3, list1 :

after move assigned from list1, list3:
0 1 2 3 4 5 6 7 8 9
list1 !=list3

after move assigned to list4, list3 :

after move assigned from list3, list4:
0 1 2 3 4 5 6 7 8 9
*/ 
