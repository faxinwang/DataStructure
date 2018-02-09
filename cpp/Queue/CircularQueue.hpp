#ifndef _CircularQueue_H_
#define _CircularQueue_H_

#include "../require.hpp"

template<class T>
class CircularQueue{
private:
    T* _elem;
    int _cap;
    int _front, _rear;
protected:
    void expand(){
    	int oldCap = _cap; 
        _cap = _cap * 2;
        T* arr = new T[_cap];
        int k=0;
        for(int i=_front; i != _rear; i=(i+1) % oldCap, ++k) arr[k] = _elem[i];
        delete[] _elem;
        _elem = arr;
        _front = 0;
        _rear = k;
    }

public:

    //constructor
    CircularQueue(int capacity=20)
        :_cap(capacity),    //the size of the array
         _elem(new T[capacity]), //the array to place elements
         _front(0),         //point to the index of the first element in the queue
         _rear(0){}         //point to the index AFTER the last element in the queue

    //copy constructor
    CircularQueue(const CircularQueue& q){
        _cap = q._cap;
        _front = q._front;
        _rear = q._rear;
        _elem = new T[_cap];
        for(int i=_front; i != _rear; i=(i+1)%_cap) _elem[i] = q._elem[i];
    }

    //assignment operator
    CircularQueue& operator=(const CircularQueue& q){
        if(this == &q) return *this;
        _cap = q._cap;
        _front = q._front;
        _rear = q._rear;
        if(_elem) delete[] _elem;
        _elem = new T[_cap];
        for(int i=_front; i != _rear; i=(i+1)%_cap) _elem[i] = q._elem[i];
    }

    //destructor
    ~CircularQueue(){ if(_elem) delete[] _elem;}
    
    //return true if queue is empty, else false
    bool empty(){ return _front == _rear; }

    //return the count of elements in the queue
    int size(){ return (_rear - _front + _cap) % _cap; }

    //return the length of the array
    int capacity(){ return _cap;}

    //return the element in the front of the queue
    T& front(){ return _elem[_front]; }

    //return the element in the back of the queue
    T& back(){ return _elem[(_rear-1+_cap)%_cap]; }

    //push an element into the queue
    void push(const T& x){ 
        if( size() + 1 >= _cap) expand();
        _elem[_rear] = x;
        _rear = (_rear + 1) % _cap;
    }

    //delete the element in the front from the queue
    T pop(){
        require(size()>0, "can not pop from the empty queue!");
        T tmp = front();
        _front = (_front + 1) % _cap;
        return tmp;
    }

};


#endif
