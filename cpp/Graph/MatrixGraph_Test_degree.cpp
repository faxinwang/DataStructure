#include<iostream>
#include"MatrixGraph.hpp"
using namespace std;

int main(){
    int v[]={1,2,3,4,5,6};
    MatrixGraph<int> mg(sizeof(v)/sizeof(v[0]), v); //noEdgeFlag=0, directed=true
    mg.add_edge(1,2);
	mg.add_edge(1,4);
	mg.add_edge(2,3);
	mg.add_edge(3,5);
	mg.add_edge(4,5);
	mg.add_edge(4,6);

    mg.print_matrix();
    cout<<"is directed:"<<boolalpha<<mg.is_directed()<<endl;

    cout<<"in_degree(1):"<<mg.in_degree(1)<<endl;
    cout<<"out_degree(1):"<<mg.out_degree(1)<<endl;
    cout<<"degree(1):"<<mg.degree(1)<<endl;

    cout<<"in_degree(4):"<<mg.in_degree(4)<<endl;
    cout<<"out_degree(4):"<<mg.out_degree(4)<<endl;
    cout<<"degree(4):"<<mg.degree(4)<<endl;
	

    MatrixGraph<int> mg2(sizeof(v)/sizeof(v[0]), v, true); //noEdgeFlag=0
	mg2.add_edge(1,2);
	mg2.add_edge(2,3);
	mg2.add_edge(1,4);
	mg2.add_edge(4,5);
	mg2.add_edge(4,6);
	mg2.add_edge(6,5);

    cout<<endl<<endl;
    cout<<"is directed: "<<boolalpha<<mg2.is_directed()<<endl;
	mg2.print_matrix();
	cout<<"in_degree(1): "<<mg2.in_degree(1)<<endl;
	cout<<"out_degree(1): "<<mg2.out_degree(1)<<endl;
	cout<<"degree(1): "<<mg2.degree(1)<<endl<<endl;

	cout<<"in_degree(2): "<<mg2.in_degree(2)<<endl;
	cout<<"out_degree(2): "<<mg2.out_degree(2)<<endl;
	cout<<"degree(2): "<<mg2.degree(2)<<endl<<endl;
	
	cout<<"in_degree(3): "<<mg2.in_degree(3)<<endl;
	cout<<"out_degree(3): "<<mg2.out_degree(3)<<endl;
	cout<<"degree(3): "<<mg2.degree(3)<<endl<<endl;
	
	cout<<"in_degree(4): "<<mg2.in_degree(4)<<endl;
	cout<<"out_degree(4): "<<mg2.out_degree(4)<<endl;
	cout<<"degree(4): "<<mg2.degree(4)<<endl<<endl;



    return 0;
}

/*

1--2--3
\	 /
 4--5
 \
  6

*/

///////////////////
/*
	1-->2-->3
	|		
	-->4-->5
	   |  ^
	   V /
	   6/
*/
