#include<iostream>
#include<string>
#include "Vector.hpp"
using namespace std;
using namespace wfx;

template<typename T>
void print(Vector<T>& v, string hint)
{
    cout<<hint<<endl;
    for(int i=0,n=v.size(); i<n; ++i) cout<<v[i]<<' ';
    cout<<endl;
}

int main()
{
    Vector<int> v1;
    for(int i=0; i<10; ++i) v1.push_back(i);

    Vector<int> v2 = v1;
    print(v1, "after assigned to v2,  v1 : ");
    print(v2, "after assigned from v1,  v2 : ");
    cout<< (v1 == v2 ? "v1 == v2" : "v1 != v2") <<endl; 

    Vector<int> v3 = move(v1);
    print(v1, "after move asigned to v3, v1:");
    print(v3, "after move asigned from v1, v3:");
    cout<< (v1 == v3 ? "v1 == v3" : "v1 != v3") <<endl; 
    cout<< (v2 == v3 ? "v2 == v3" : "v2 != v3") <<endl; 

    return 0;
}

/*
after assigned to v2,  v1 :
0 1 2 3 4 5 6 7 8 9
after assigned from v1,  v2 :
0 1 2 3 4 5 6 7 8 9
v1 == v2
after move asigned to v3, v1:

after move asigned from v1, v3:
0 1 2 3 4 5 6 7 8 9
v1 != v3
v2 == v3
*/