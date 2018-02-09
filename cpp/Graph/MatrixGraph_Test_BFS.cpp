#include <iostream>
#include "MatrixGraph.hpp"
using namespace std;

void visit(int x){ cout<<x<<' '; }

int main(){
    int v[] = {1,2,3,4};
    MatrixGraph<int> g(sizeof(v)/sizeof(v[0]),v); //undirected, noEdgeFlag=0
    // g.print_matrix();

    cout<<"test case 1:"<<endl;
    g.add_edge(1,2);
    g.add_edge(1,3);
    g.add_edge(2,4);
    g.add_edge(3,4);
    g.BFS(visit);
    cout<<endl;
    // g.print_matrix();

    cout<<"test case 2:"<<endl;
    g.add_node(5);
    g.add_node(6);
    g.add_edge(4,5);
    g.add_edge(3,6);
    g.BFS(visit);
    cout<<endl;
    // g.print_matrix();


    cout<<"test case 3:"<<endl;
    g.del_edge(2,4);
    g.BFS(visit);
    cout<<endl;
    // g.print_matrix();

    cout<<"test case 4:"<<endl;
    g.add_node(7);
    g.add_node(8);
    g.add_node(9);
    g.add_edge(2,7);
    g.add_edge(7,8);
    g.add_edge(6,9);
    g.BFS(visit);
    cout<<endl;
    // g.print_matrix();

    cout<<"test case 5:"<<endl;
    g.add_node(10);
	g.add_node(11);
	g.add_node(12);
	g.add_edge(8,10);
	g.add_edge(5,11);
	g.add_edge(9,12);
	g.BFS(visit);
	cout<<endl;
    // g.print_matrix();

    cout<<"test case 6:"<<endl;
    g.add_edge(5,8);
	g.add_edge(5,9);
	g.del_edge(4,5);
	g.del_edge(6,9);
	g.BFS(visit);
	cout<<endl;


    cout<<"test case 7:"<<endl;
    g.del_edge(7,8);
	g.BFS(visit);
	cout<<endl;

    cout<<"test case 8:"<<endl;
	g.add_node(13);
	g.add_node(14);
	g.add_edge(10,13);
	g.add_edge(12,14);
	g.BFS(visit);
	cout<<endl;

    return 0;
}

/*
		1
	   / \
	  2   3
	   \ /
	    4 
1------------------1 2 3 4
	    1
	   / \
	  2   3
	   \ /\
	    4  6
	    \
	     5
2------------------1 2 3 4 6 5
		1
	   / \
	  2   3
	     /\
	    4  6
	    \
	     5
3------------------1 2 3 4 6 5
		1
	   / \
	  2   3
	 /   /\
	7   4  6
	\   \  \
	 8   5  9
4------------------1 2 3 7 4 6 8 5 9
		1
	   / \
	  2   3
	 /   /\
	7   4  6
	\   \  \
	 8   5  9
	/	/ 	\
   10  11	12
5---------------1 2 3 7 4 6 8 5 9 10 11 12
		1
	   / \
	  2   3
	 /   /\
	7   4  6
	\   
	 8--5--9
	/	/ 	\
   10  11	12
6-------------1 2 3 7 4 6 8 5 10 9 11 12
		1
	   / \
	  2   3
	 /   /\
	7   4  6
	
	 8--5--9
	/	/ 	\
   10  11	12
7----------------1 2 3 7 4 6
				 5 8 9 11 10 12

		1
	   / \
	  2   3
	 /   /\
	7   4  6
	
	 8--5--9
	/	/ 	\
   10  11	12
   	\		 \
   	13		 14
8---------------1 2 3 7 4 6
				5 8 9 11 10 12 13 14
*/
