#include <iostream>
#include "BST.hpp"
using namespace std;
using namespace wfx;

void visit(int e){ cout<<e<<' '; }

int main()
{
    int kiss=0, ret, than;
    BST<int> bst;
    int a[]={2, 10, 20, 55, 21, 14, 1, 4, 0, 23, 17, 28, 33, 44, 35, 45, 50};
    int b[]={0, 1, 2, 4, 10, 14, 17, 20, 21, 23, 28, 33, 35, 44, 45, 50, 55};

    int n = sizeof(a) / sizeof(int);
    for(int i=0; i<n; ++i) bst.Insert( a[i] );
    cout<<"size: "<<bst.Size()<<endl;
    bst.InOrderGo(visit);   cout<<endl;

    than = -1;
    cout<<"Case #"<< kiss++ << " element less than "<<than<<endl;
    ret = bst.TheLargestElementLessThan(than);
    cout<<"expected : -1"<<endl;
    cout<<"output   : "<<ret<<endl;
    cout<<(ret == -1? "PASS" : "Fail")<<endl<<endl;

    than = 0;
    cout<<"Case #"<< kiss++ << " element less than "<<than<<endl;
    ret = bst.TheLargestElementLessThan(than);
    cout<<"expected : 0"<<endl;
    cout<<"output   : "<<ret<<endl;
    cout<<(ret == 0? "PASS" : "Fail")<<endl<<endl;

    than = 1;
    cout<<"Case #"<< kiss++ << " element less than "<<than<<endl;
    ret = bst.TheLargestElementLessThan(than);
    cout<<"expected : 0"<<endl;
    cout<<"output   : "<<ret<<endl;
    cout<<(ret == 0? "PASS" : "Fail")<<endl<<endl;

    than = 60;
    cout<<"Case #"<< kiss++ << " element greater than "<<than<<endl;
    ret = bst.TheSmallestElementGreaterThan(than);
    cout<<"expected : 60"<<endl;
    cout<<"output   : "<<ret<<endl;
    cout<<(ret == 60? "PASS" : "Fail")<<endl<<endl;

    than = 55;
    cout<<"Case #"<< kiss++ << " element greater than "<<than<<endl;
    ret = bst.TheSmallestElementGreaterThan(than);
    cout<<"expected : 55"<<endl;
    cout<<"output   : "<<ret<<endl;
    cout<<(ret == 55? "PASS" : "Fail")<<endl<<endl;

    than = 54;
    cout<<"Case #"<< kiss++ << " element greater than "<<than<<endl;
    ret = bst.TheSmallestElementGreaterThan(than);
    cout<<"expected : 55"<<endl;
    cout<<"output   : "<<ret<<endl;
    cout<<(ret == 55? "PASS" : "Fail")<<endl<<endl;

    cout<<"Case #"<< kiss++ <<" test all [less] "<<endl;
    bool passFlag = true;
    for(int i=0; i < n ; ++i)
    {
        ret = bst.TheLargestElementLessThan(b[i] + 1);
        cout<<"element less than "<<b[i]+1<<endl;
        cout<<"expected : "<<b[i]<<endl;
        cout<<"output   : "<<ret<<endl;
        if(ret != b[i]) passFlag = false;
    }
    cout<<(passFlag ? "PASS" : "Fail")<<endl<<endl;
    
    cout<<"Case #"<< kiss++ <<" test all [less] "<<endl;
    passFlag = true;
    for(int i=1; i < n ; ++i)
    {
        ret = bst.TheLargestElementLessThan(b[i]);
        cout<<"element less than "<<b[i]<<endl;
        cout<<"expected : "<<b[i-1]<<endl;
        cout<<"output   : "<<ret<<endl;
        if(ret != b[i-1]) passFlag = false;
    }
    cout<<(passFlag ? "PASS" : "Fail")<<endl<<endl;

    cout<<"Case #"<< kiss++ <<" test all [greater] "<<endl;
    passFlag = true;
    for(int i=0; i < n ; ++i)
    {
        ret = bst.TheSmallestElementGreaterThan(b[i]-1);
        cout<<"element greater than "<<b[i]-1<<endl;
        cout<<"expected : "<<b[i]<<endl;
        cout<<"output   : "<<ret<<endl;
        if(ret != b[i]) passFlag = false;
    }
    cout<<(passFlag ? "PASS" : "Fail")<<endl<<endl;

    cout<<"Case #"<< kiss++ <<" test all [greater] "<<endl;
    passFlag = true;
    for(int i=1; i < n ; ++i)
    {
        ret = bst.TheSmallestElementGreaterThan(b[i-1]);
        cout<<"element greater than "<<b[i-1]<<endl;
        cout<<"expected : "<<b[i]<<endl;
        cout<<"output   : "<<ret<<endl;
        if(ret != b[i]) passFlag = false;
    }
    cout<<(passFlag ? "PASS" : "Fail")<<endl<<endl;

    return 0;
}

/*
size: 17
0 1 2 4 10 14 17 20 21 23 28 33 35 44 45 50 55
Case #0 element less than -1
expected : -1
output   : -1
PASS

Case #1 element less than 0
expected : 0
output   : 0
PASS

Case #2 element less than 1
expected : 0
output   : 0
PASS

Case #3 element greater than 60
expected : 60
output   : 60
PASS

Case #4 element greater than 55
expected : 55
output   : 55
PASS

Case #5 element greater than 54
expected : 55
output   : 55
PASS

Case #6 test all [less]
element less than 1
expected : 0
output   : 0
element less than 2
expected : 1
output   : 1
element less than 3
expected : 2
output   : 2
element less than 5
expected : 4
output   : 4
element less than 11
expected : 10
output   : 10
element less than 15
expected : 14
output   : 14
element less than 18
expected : 17
output   : 17
element less than 21
expected : 20
output   : 20
element less than 22
expected : 21
output   : 21
element less than 24
expected : 23
output   : 23
element less than 29
expected : 28
output   : 28
element less than 34
expected : 33
output   : 33
element less than 36
expected : 35
output   : 35
element less than 45
expected : 44
output   : 44
element less than 46
expected : 45
output   : 45
element less than 51
expected : 50
output   : 50
element less than 56
expected : 55
output   : 55
PASS

Case #7 test all [less]
element less than 1
expected : 0
output   : 0
element less than 2
expected : 1
output   : 1
element less than 4
expected : 2
output   : 2
element less than 10
expected : 4
output   : 4
element less than 14
expected : 10
output   : 10
element less than 17
expected : 14
output   : 14
element less than 20
expected : 17
output   : 17
element less than 21
expected : 20
output   : 20
element less than 23
expected : 21
output   : 21
element less than 28
expected : 23
output   : 23
element less than 33
expected : 28
output   : 28
element less than 35
expected : 33
output   : 33
element less than 44
expected : 35
output   : 35
element less than 45
expected : 44
output   : 44
element less than 50
expected : 45
output   : 45
element less than 55
expected : 50
output   : 50
PASS

Case #8 test all [greater]
element greater than -1
expected : 0
output   : 0
element greater than 0
expected : 1
output   : 1
element greater than 1
expected : 2
output   : 2
element greater than 3
expected : 4
output   : 4
element greater than 9
expected : 10
output   : 10
element greater than 13
expected : 14
output   : 14
element greater than 16
expected : 17
output   : 17
element greater than 19
expected : 20
output   : 20
element greater than 20
expected : 21
output   : 21
element greater than 22
expected : 23
output   : 23
element greater than 27
expected : 28
output   : 28
element greater than 32
expected : 33
output   : 33
element greater than 34
expected : 35
output   : 35
element greater than 43
expected : 44
output   : 44
element greater than 44
expected : 45
output   : 45
element greater than 49
expected : 50
output   : 50
element greater than 54
expected : 55
output   : 55
PASS

Case #9 test all [greater]
element greater than 0
expected : 1
output   : 1
element greater than 1
expected : 2
output   : 2
element greater than 2
expected : 4
output   : 4
element greater than 4
expected : 10
output   : 10
element greater than 10
expected : 14
output   : 14
element greater than 14
expected : 17
output   : 17
element greater than 17
expected : 20
output   : 20
element greater than 20
expected : 21
output   : 21
element greater than 21
expected : 23
output   : 23
element greater than 23
expected : 28
output   : 28
element greater than 28
expected : 33
output   : 33
element greater than 33
expected : 35
output   : 35
element greater than 35
expected : 44
output   : 44
element greater than 44
expected : 45
output   : 45
element greater than 45
expected : 50
output   : 50
element greater than 50
expected : 55
output   : 55
PASS

*/