#include<iostream>
#include<string>
#include"MatrixGraph.hpp"
using namespace std;

void printPath(int *p, int start, int end){
    if(start == end){
        printf("%d",start);
        return;
    } 
    if( p[end] ) printPath(p, start, p[end]);
    printf("-->%d",end);
}

int main(){
    string v[]={"v1","v2","v3","v4","v5","v6"};
    MatrixGraph<string> g(sizeof(v)/sizeof(v[0]), v); //undirected, noEdgeFlag=0
    g.add_edge(1,2,2);
    g.add_edge(1,3,1);
    g.add_edge(1,4,6);
    g.add_edge(2,5,5);
    g.add_edge(3,6,2);
    g.add_edge(4,5,3);
    g.add_edge(4,6,1);
    g.add_edge(5,6,2);
    
    int n=g.number_of_vertex();
    double dist[n+1];
    int p[n+1];

    cout<<"test 1:"<<endl;
    int start = 1;
    g.dijkstra(start, dist, p);
    for(int i=1; i<=n; ++i){
        cout<<"min distance from "<<g.getVertex(start)<<" to "<<g.getVertex(i)<<" is: "<<dist[i]<<endl;
        cout<<"path: ";
        printPath(p,start, i);
        cout<<endl<<endl;
    }

    cout<<"test 2:"<<endl;
    start = 2;
    g.dijkstra(start, dist, p);
    for(int i=1; i<=n; ++i){
        cout<<"min distance from "<<g.getVertex(start)<<" to "<<g.getVertex(i)<<" is: "<<dist[i]<<endl;
        cout<<"path: ";
        printPath(p,start, i);
        cout<<endl<<endl;
    }
        
    return 0;
}


/*
this is a undirected weighted graph
     2
v1-------v2
|  \      \5
|1  \6     \
v3   v4--3--v5
 \   |     /
 2\  |1  /2
   \ | /
    v6

output:
test 1:
min distance from v1 to v1 is: 0
path: 1
min distance from v1 to v2 is: 2
path: 1-->2
min distance from v1 to v3 is: 1
path: 1-->3
min distance from v1 to v4 is: 4
path: 1-->3-->6-->4
min distance from v1 to v5 is: 5
path: 1-->3-->6-->5
min distance from v1 to v6 is: 3
path: 1-->3-->6

test 2:
min distance from v2 to v1 is 2
path: 2-->1
min distance from v2 to v2 is 0
path: 2
min distance from v2 to v3 is 3
path: 2-->1-->3
min distance from v2 to v4 is 6
path: 2-->1-->3-->6-->4
min distance from v2 to v5 is 5
path: 2-->5
min distance from v2 to v6 is 5
path: 2-->1-->3-->6

*/