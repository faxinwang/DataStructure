#include <iostream>
#include "SplayTree.hpp"
using namespace std;
using namespace wfx;

void visit(int& x){ cout<<x<<' '; }

int main()
{
    SplayTree<int> splay;
    for(int i=1; i<=60; ++i) splay.Insert(i);

    cout<<"after insert from 1 to 60"<<endl;
    splay.InOrderGo(visit); cout<<endl;
    cout<<endl;

    int cnt=0;
    cout<<"after Remove range [5, 10]"<<endl;
    cnt = splay.RemoveRange(5, 10);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [5, 20]"<<endl;
    cnt = splay.RemoveRange(5, 20);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [0, 20]"<<endl;
    cnt = splay.RemoveRange(0, 20);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [33, 40]"<<endl;
    cnt = splay.RemoveRange(33, 40);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [50, 55]"<<endl;
    cnt = splay.RemoveRange(50, 55);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [45,45]"<<endl;
    cnt = splay.RemoveRange(45,45);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [0,40]"<<endl;
    cnt = splay.RemoveRange(0,40);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [45,58]"<<endl;
    cnt = splay.RemoveRange(45, 58);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [55,60]"<<endl;
    cnt = splay.RemoveRange(55, 60);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    cout<<"after Remove range [0,60]"<<endl;
    cnt = splay.RemoveRange(0, 60);
    splay.InOrderGo(visit); cout<<endl;
    cout<<"number of elements removed : "<<cnt<<endl<<endl;

    return 0;
}

/*
after insert from 1 to 60
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60

after Remove range [5, 10]
1 2 3 4 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
number of elements removed : 6

after Remove range [5, 20]
1 2 3 4 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
number of elements removed : 10

after Remove range [0, 20]
21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
number of elements removed : 4

after Remove range [33, 40]
21 22 23 24 25 26 27 28 29 30 31 32 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
number of elements removed : 8

after Remove range [50, 55]
21 22 23 24 25 26 27 28 29 30 31 32 41 42 43 44 45 46 47 48 49 56 57 58 59 60
number of elements removed : 6

after Remove range [45,45]
21 22 23 24 25 26 27 28 29 30 31 32 41 42 43 44 46 47 48 49 56 57 58 59 60
number of elements removed : 1

after Remove range [0,40]
41 42 43 44 46 47 48 49 56 57 58 59 60
number of elements removed : 12

after Remove range [45,58]
41 42 43 44 59 60
number of elements removed : 7

after Remove range [55,60]
41 42 43 44
number of elements removed : 2

after Remove range [0,60]

number of elements removed : 4

*/