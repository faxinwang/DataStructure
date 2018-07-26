#include<iostream> 
#include<string>
#include"MatrixGraph.hpp"
using namespace std;
using namespace wfx;

void visit(string &x){ cout<<x<<' '; }

int main(){
    string v[]={"c1","c2","c3","c4","c5","c6","c7","c8","c9"};
	MatrixGraph<string> g(sizeof(v)/sizeof(v[0]), v, true);//directed, noEdgeFlag=0
	//add edges
	g.add_edge(2,3);
	g.add_edge(2,4);
	g.add_edge(2,5);
	g.add_edge(1,3);
	g.add_edge(1,8);
	g.add_edge(5,6);
	g.add_edge(4,6);
	g.add_edge(3,4);
	g.add_edge(4,7);
	g.add_edge(8,9);
	g.add_edge(9,7);
	g.topoSort(visit);
	
	
	return 0;
}

/*
this is a directed uncircle graph,
image every line has a arrow at the right of the line.
		  C5
	    /    \
	   /      C6
	  /	    /  
	C2----C4
	 \   /  \
	  \ /    \
	  C3      \
	 /    	  C7
   C1        /
     \      /
      C8   /
       \  /
        C9
output : c2 c5 c1 c8 c9 c3 c4 c7 c6

*/
