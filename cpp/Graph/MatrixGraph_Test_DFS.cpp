#include<iostream>
#include"MatrixGraph.hpp"
using namespace std;

void visit(int x){ cout<<x<<' ';}

int main(){
    int v[]={1,2,3,4};
	MatrixGraph<int> g(sizeof(v)/sizeof(*v),v); //undirected, noEdgeFlag=0
	
    cout<<"test case 1:"<<endl;
	g.add_edge(1,2);
	g.add_edge(1,3);
	g.add_edge(2,4);
	g.add_edge(3,4);
	g.DFS(visit);
	cout<<endl; 
	
    cout<<"test case 2:"<<endl;
	g.add_node(5),
	g.add_node(6);
	g.add_edge(4,5);
	g.add_edge(3,6);
	g.DFS(visit);
	cout<<endl;
	
    cout<<"test case 3:"<<endl;
	g.del_edge(2,4);
	g.DFS(visit);
	cout<<endl;
	
    cout<<"test case 4:"<<endl;
	g.add_node(7);
	g.add_node(8);
	g.add_edge(3,7);
	g.add_edge(7,8);
	g.DFS(visit);
	cout<<endl;
	
    cout<<"test case 5:"<<endl;
	g.del_edge(3,7);
	g.DFS(visit);
	cout<<endl;

    return 0;
}


/*
		1
	   / \
	  2   3
	   \ /
	    4 
------------------1 2 4 3
	    1
	   / \
	  2   3
	   \ /\
	    4  6
	    \
	     5
------------------1 2 4 3 6 5
		1
	   / \
	  2   3 
	     /\
	    4  6
	    \
	     5
-------------------1 2 3 4 5 6
		1
	   / \
	  2   3-7-8
	     /\
	    4  6
	    \
	     5
-------------------1 2 3 4 5 6 7 8

		1
	   / \
	  2   3  7-8
	     /\
	    4  6
	    \
	     5
-------------------1 2 3 4 5 6
				   7 8
				   
				   
*/
