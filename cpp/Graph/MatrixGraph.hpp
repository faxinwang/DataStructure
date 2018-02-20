#ifndef MatrixGraph_hpp
#define MatrixGraph_hpp

#include "../Vector/Vector.hpp"
#include "../require.hpp"
#include "../Queue/Queue.hpp"
#include "../Stack/Stack.hpp"
#include <sstream>

template<typename T>
class MatrixGraph{
private:
    int _numNode, _numEdge;
    int _relax;
    const int _noEdgeFlag;
    Vector<T> _nodes;
    bool _directed; //true if it's a directed graph, else false
    Vector< Vector<int> > _edges;
public:
    /*constructor*/
    MatrixGraph(int vSize,T *v, bool directed=false, int NoEdgeFlag=0)
    :_numNode(vSize),_numEdge(0),_directed(directed), _noEdgeFlag(NoEdgeFlag)
    {
        _relax = 5;
        _nodes.reserve(_numNode + _relax);
        _nodes.push_back( T() ); //place of index 0 is not used
        for(int i=0; i<_numNode; ++i) _nodes.push_back(v[i]);

        _edges.reserve(_numNode + _relax);
        _edges.push_back( Vector<int>(1) ); //the first row is not used

        for(int i=0; i<_numNode; ++i) 
            _edges.push_back( Vector<int>(_numNode + _relax, _numNode + 1, _noEdgeFlag) );
        
    }
    
    /************   basic functions  *********************/

    bool is_directed(){return _directed;}

    int number_of_vertex(){return _numNode;}
    
    int number_of_edges(){return _numEdge;}

    //get vertex  of the given id
    T getVertex(int id)
    { 
        stringstream ss;
        require(1 <= id && id <= _numNode, (ss<<"vertex not exists, id="<<id, ss) );
        return _nodes[id];
    }

    //add a vertex
    void add_node(T nd)
    {
        _nodes.push_back(nd);
        for(int i=1; i<= _numNode; ++i) _edges[i].push_back(_noEdgeFlag);
        ++_numNode;
        _edges.push_back(Vector<int>(_numNode + _relax , _numNode + 1, _noEdgeFlag));
    }
    
    //add an edge (u,v,w)
    void add_edge(int u,int v, int w=1)
    {
        stringstream ss;
        require(1 <= u && u <= _numNode , (ss<<"no such vertex u="<<u, ss) );
        require(1 <= v && v <= _numNode, (ss.str(""), ss<<"no such vertex v="<<v,ss) );
        require(_edges[u][v] == _noEdgeFlag, (ss.str(""),ss<<"edge already exists u="<<u<<" v="<<v,ss) );
        _directed ? _edges[u][v] = w : _edges[u][v] = _edges[v][u] = w;
        ++_numEdge;
    }

    //delete an edge
    void del_edge(int u,int v)
    {
        stringstream ss;
        require(1 <= u && u <= _numNode , (ss<<"no such vertex u="<<u, ss) );
        require(1 <= v && v <= _numNode, (ss.str(""), ss<<"no such vertex v="<<v,ss) );
        require(_edges[u][v] != _noEdgeFlag, (ss.str(""),ss<<"edge not exists u="<<u<<" v="<<v,ss) );
        _directed ? _edges[u][v] = _noEdgeFlag : _edges[u][v] = _edges[v][u] = _noEdgeFlag;
        --_numEdge;
    }

    //check if an edge is exists
    //return true if edge (u,v) exists, else false
    bool is_edges_exists(int u,int v)
    {
        stringstream ss;
        require(1 <= u && u <= _numNode , (ss<<"no such vertex u="<<u, ss) );
        require(1 <= v && v <= _numNode, (ss.str(""), ss<<"no such vertex v="<<v,ss) );
        return _edges[u][v]!=_noEdgeFlag;
    }


    //return the weight of edge (u,v)
    int get_weight(int u,int v)
    {
        stringstream ss;
        require(1 <= u && u <= _numNode , (ss<<"no such vertex u="<<u, ss) );
        require(1 <= v && v <= _numNode, (ss.str(""), ss<<"no such vertex v="<<v,ss) );
        return _edges[u][v];
    }

    //print the matrix
    void print_matrix()
    {
        printf("%d X %d / %d X %d\n",_numNode, _numNode, _edges.capacity(), _edges[1].capacity());
        for(int i=1; i<= _numNode; ++i)
        {
            for(int j=1; j<= _numNode; ++j) printf("%5d", _edges[i][j]);
            printf("\n");
        }
    }

    //return the in degree of the given vertex
    int in_degree(int u)
    {
        stringstream ss;
        require(1 <= u && u <= _numNode , (ss<<"no such vertex u="<<u, ss) );
        int cnt = 0;
        for(int i=1; i<= _numNode; ++i) if(_edges[i][u] != _noEdgeFlag) ++cnt;
        return cnt;
    }

    //return the out degree of the given vertex
    int out_degree(int u)
    {
        stringstream ss;
        require(1 <= u && u <= _numNode , (ss<<"no such vertex u="<<u, ss) );
        int cnt = 0;
        for(int i=1; i <= _numNode; ++i) if(_edges[u][i] != _noEdgeFlag) ++cnt;
        return cnt;
    }

    //return the degree of the given vertex
    int degree(int u)
    {
        return _directed? in_degree(u) + out_degree(u) : in_degree(u);
    }


    /**********   algorithms on graph     ****************/

    /*
    * The DFS() driver function
    * @param visit. The function or functor to operator on every node.
    */
    template<typename VIS>
    void BFS(VIS& visit)
    {
        bool visited[_numNode+1];
        for(int i=0; i<=_numNode; ++i) visited[i] = false;

        for(int i=1; i<=_numNode; ++i){
            if(!visited[i]) BFS(i,visited, visit);
        }
    }

    template<typename VIS>
    void BFS(int s, bool* visited,  VIS &visit)
    {
        Queue<int> Q;
        Q.push(s);
        visited[s] = true;
        while(!Q.empty()){
            int u = Q.pop();
            visit(_nodes[u]);
            for(int i=1;i<=_numNode; ++i){
                if(_edges[u][i] != _noEdgeFlag && !visited[i]){
                    Q.push(i);
                    visited[i] = true;
                } 
            }
        }
    }

    /*
    * the DFS() driver function
    * 
    */
    template<typename VIS>
    void DFS(VIS &visit)
    {
        bool visited[_numNode+1];
        for(int i=0;i<=_numNode; ++i) visited[i] = false;
        for(int i=1; i<= _numNode; ++i){
            if(!visited[i]) DFS(i,visited, visit);
        }
    }

    template<typename VIS>
    void DFS(int s, bool *visited, VIS visit)
    {
        visited[s] = true;
        visit(_nodes[s]);
        for(int i=1; i<=_numNode; ++i){
            if(!visited[i] && _edges[s][i] != _noEdgeFlag) DFS(i,visited,visit);
        }
    }

    /*
    拓扑排序
    topoSort, can be implemented on directed graph only
    1.get the inDegree of every vertex, push the vertex into stack if it's inDegree is 0
    2.if the stack is not empty, repeat the following steps:
        a.pop out a vertex from stack, and visit it
        b.remove all edges starting from this vertex, if the inDegree of the vertex at the end of edges 
          become zero, then push the vertex into stack.
    */
    template<typename VIS>
    bool topoSort(VIS &visit)
    {
        require(_directed, "topoSort can be implemented on directed graph only!");
        int inDegree[_numNode+1];
        Stack<int> s;
        for(int i=1; i<=_numNode; ++i) {
            inDegree[i] = in_degree(i);
            if(inDegree[i] == 0) s.push(i);
        }

        int cnt = 0;
        while(!s.empty()){
            ++cnt;
            int cur = s.pop();
            visit(_nodes[cur]);
            for(int i=1; i<=_numNode; ++i){
                if(_edges[cur][i] != _noEdgeFlag){
                    --inDegree[i];
                    if(inDegree[i] == 0) s.push(i);
                }
            }
        }
        return cnt==_numNode; //if cnt!= _numNode, there must be circle in the graph
    }

    /* dijkstra(迪杰斯特拉)
    * @param u.     calculate the shortest distance from u to all other vertex
    * @param dist.  after the operations, dist[i] will be the shortest distance from u to i 
    * @param p.     p[i] is the previous vertex in the shortest path from u to i
    */
    void dijkstra(int x, double *dist ,int *p=0, int INF=INT_MAX)
    {
        bool s[_numNode+1];
        for(int i=1; i<=_numNode; ++i){
            s[i] = 0;
            if(_edges[x][i] != _noEdgeFlag){
                dist[i] = _edges[x][i];
                if(p) p[i] = x;
            }else{
                dist[i] = INF;
                if(p) p[i] = 0;
            } 
        } 
        s[x] = true;
        dist[x] = 0;
        if(p) p[x] = x;

        for(int i=1; i<=_numNode; ++i){
            int u=0, Mid = INF;
            for(int j=1; j<=_numNode; ++j){
                if(!s[j] && Mid > dist[j]){ u = j; Mid = dist[j]; }
            }
            s[u] = true;
            for(int v=1; v<=_numNode; ++v){
                if(!s[v] && _edges[u][v] != _noEdgeFlag){
                    int tmp = Mid + _edges[u][v];
                    if(tmp < dist[v]){
                        dist[v] = tmp;
                        if(p) p[v] = u;
                    } 
                }
            }
        }
    }

    //calculate the shortest distance for all vertex to the other vertex
    void shortestDistanceForAll(Vector<Vector<T> >& a){
        //a[i][j] is the shortest distance between i and j
        a = _edges;
        for(int k=1; k<=_numNode; ++k){
            for(int i=1; i<=_numNode; ++i){
                for(int j=1; j<=_numNode; ++j){
                    int dist = a[i][k] + a[k][j];
                    if( dist < a[i][j]) a[i][j] = dist;
                }
            }
        }
    }



};


#endif


