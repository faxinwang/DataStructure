#include <iostream>
#include "CircularQueue.hpp"
using namespace std;
using namespace wfx;

int main()
{
    int id = 0;
    CircularQueue<int> q1;
    for(int i=0; i<15; ++i) q1.push(++id);

    for(int i=0; i<10; ++i) q1.pop();

    for(int i=0; i<10; ++i) q1.push(++id);

    CircularQueue<int> q2 = move(q1);

    cout<<"q1's size : "<<q1.size()<<endl<<endl;

    cout<<"q2's size : "<<q2.size()<<endl<<endl;

    while(!q2.empty())  cout<<q2.pop()<<' ';


    return 0;
}

/*
q1's size : 0

q2's size : 15

11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

*/
