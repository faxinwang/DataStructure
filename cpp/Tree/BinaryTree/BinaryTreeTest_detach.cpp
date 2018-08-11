#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include "BinaryTree.hpp"
using namespace std;
using namespace wfx;

typedef Node<char> TNode;

template<typename T>
struct TraverseOrderTest
{
    vector<T> vis;
    vector<T> expected;
    TraverseOrderTest(const T* exp,int n)
    {
        for(int i=0; i<n; ++i) expected.push_back(exp[i]);
    }

    void operator()(T& t) { 
        vis.push_back(t);
        // cout<<t<<' ';
    }

    bool test(){ vis == expected; }

    void printExpected()
    { for(int i=0,n=expected.size(); i<n;++i) cout<<expected[i]<<' '; }

    void printOutput()
    { for(int i=0,n=vis.size(); i<n;++i) cout<<vis[i]<<' ';
        // cout<<" size="<<vis.size();
    }
};


/*
        A
      /   \
     B     C
   /  \   /  \
  D    E F    G
preOrder : ABDECFG
inOrder  : DBEAFCG

C detach from A and attach to E as left child
        A
      / 
     B   
   /  \  
  D    E 
      /
     C
    / \
   F   G
preOrder : ABDECFG
inOrder  : DBFCGEA

E detach from B and attach to A as right child
        A
      /   \
     B     E
   /      /
  D      C
        / \
       F   G
preOrder : ABDECFG
inOrder  : DBAFCGE

B detach from A and attach to E as right child
        A
          \
           E
          /  \
         C    B
        / \   /
       F   G D
preOrder : AECFGBD
inOrder  : AFCGEDB

F detach from C and attach to E as right child
B and D will be removed and disposed
        A
          \
           E
          /  \
         C    F
          \ 
           G 
preOrder : AECGF
inOrder  : ACGEF

*/


int main()
{
    int kiss = 1;
    int height;
    string pre1 = "ABDECFG";
    string in1 = "DBEAFCG";
    string pre2 = "ABDECFG";
    string in2 = "DBFCGEA";
    string pre3 = "ABDECFG";
    string in3 = "DBAFCGE";
    string pre4 = "AECFGBD";
    string in4 = "AFCGEDB";
    string pre5 = "AECGF";
    string in5 = "ACGEF";

    TNode* A = new TNode('A');
    BinaryTree<char> bt(A);
    
    TNode* B = A->InsertLeftChild('B');
    TNode* C = A->InsertRightChild('C');
    TNode* D = B->InsertLeftChild('D');
    TNode* E = B->InsertRightChild('E');
    TNode* F = C->InsertLeftChild('F');
    TNode* G = C->InsertRightChild('G');

    cout<<"Case#"<< kiss++ <<": test PreOrder traverse"<<endl;
    TraverseOrderTest<char> preOrder1(pre1.c_str(),7);
    bt.PreOrderGo(preOrder1);
    cout<<"expected:";   preOrder1.printExpected(); cout<<endl;
    cout<<"output  :";   preOrder1.printOutput();   cout<<endl;
    height = A->height;
    cout<<"expected height of root: 3"<<endl;
    cout<<"height of root:" <<height<<endl;
    cout<<(preOrder1.test() &&height==3 ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#1: test PreOrder traverse
    expected:A B D E C F G
    output  :A B D E C F G
    expected height of root: 3
    height of root:3
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test InOrder traverse"<<endl;
    TraverseOrderTest<char> inOrder1(in1.c_str(), 7);
    bt.InOrderGo(inOrder1);
    cout<<"expected:";   inOrder1.printExpected(); cout<<endl;
    cout<<"output  :";   inOrder1.printOutput();   cout<<endl;
    cout<<(preOrder1.test()? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#2: test InOrder traverse
    expected:D B E A F C G
    output  :D B E A F C G
    PASS!
    */

    cout<<"---C detach from A and attach to E as left child---"<<endl;
    C->Detach();
    E->AttachLeftChild(C);

    cout<<"Case#"<< kiss++ <<": test PreOrder traverse"<<endl;
    TraverseOrderTest<char> preOrder2(pre2.c_str(),7);
    bt.PreOrderGo(preOrder2);
    cout<<"expected:";   preOrder2.printExpected(); cout<<endl;
    cout<<"output  :";   preOrder2.printOutput();   cout<<endl;
    height = A->height;
    cout<<"expected height of root: 5"<<endl;
    cout<<"height of root:" <<height<<endl;
    cout<<(preOrder1.test() &&height==5 ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    ---C detach from A and attach to E as left child---
    Case#3: test PreOrder traverse
    expected:A B D E C F G
    output  :A B D E C F G
    expected height of root: 5
    height of root:5
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test InOrder traverse"<<endl;
    TraverseOrderTest<char> inOrder2(in2.c_str(), 7);
    bt.InOrderGo(inOrder2);
    cout<<"expected:";   inOrder2.printExpected(); cout<<endl;
    cout<<"output  :";   inOrder2.printOutput();   cout<<endl;
    cout<<(preOrder1.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#4: test InOrder traverse
    expected:D B F C G E A
    output  :D B F C G E A
    PASS!
    */

    cout<<"---E detach from B and attach to A as right child---"<<endl;
    E->Detach();
    A->AttachRightChild(E);

    cout<<"Case#"<< kiss++ <<": test PreOrder traverse"<<endl;
    TraverseOrderTest<char> preOrder3(pre3.c_str(),7);
    bt.PreOrderGo(preOrder3);
    cout<<"expected:";   preOrder3.printExpected(); cout<<endl;
    cout<<"output  :";   preOrder3.printOutput();   cout<<endl;
    height = A->height;
    cout<<"expected height of root: 4"<<endl;
    cout<<"height of root:" <<height<<endl;
    cout<<(preOrder1.test() &&height==4 ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    ---E detach from B and attach to A as right child---
    Case#5: test PreOrder traverse
    expected:A B D E C F G
    output  :A B D E C F G
    expected height of root: 4
    height of root:4
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test InOrder traverse"<<endl;
    TraverseOrderTest<char> inOrder3(in3.c_str(), 7);
    bt.InOrderGo(inOrder3);
    cout<<"expected:";   inOrder3.printExpected(); cout<<endl;
    cout<<"output  :";   inOrder3.printOutput();   cout<<endl;
    cout<<(preOrder1.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#6: test InOrder traverse
    expected:D B A F C G E
    output  :D B A F C G E
    PASS!
    */

    cout<<"---B detach from A and attach to E as right child---"<<endl;
    B->Detach();
    E->AttachRightChild(B);

    cout<<"Case#"<< kiss++ <<": test PreOrder traverse"<<endl;
    TraverseOrderTest<char> preOrder4(pre4.c_str(),7);
    bt.PreOrderGo(preOrder4);
    cout<<"expected:";   preOrder4.printExpected(); cout<<endl;
    cout<<"output  :";   preOrder4.printOutput();   cout<<endl;
    height = A->height;
    cout<<"expected height of root: 4"<<endl;
    cout<<"height of root:" <<height<<endl;
    cout<<(preOrder1.test() &&height==4 ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    ---B detach from A and attach to E as right child---
    Case#7: test PreOrder traverse
    expected:A E C F G B D
    output  :A E C F G B D
    expected height of root: 4
    height of root:4
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test InOrder traverse"<<endl;
    TraverseOrderTest<char> inOrder4(in4.c_str(), 7);
    bt.InOrderGo(inOrder4);
    cout<<"expected:";   inOrder4.printExpected(); cout<<endl;
    cout<<"output  :";   inOrder4.printOutput();   cout<<endl;
    cout<<(preOrder1.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#8: test InOrder traverse
    expected:A F C G E D B
    output  :A F C G E D B
    PASS!
    */

    cout<<"---F detach from C and attach to E as right child---"<<endl;
    cout<<"---B and D will be removed and disposed---"<<endl;
    F->Detach();
    E->AttachRightChild(F);

    cout<<"Case#"<< kiss++ <<": test PreOrder traverse"<<endl;
    TraverseOrderTest<char> preOrder5(pre5.c_str(),5);
    bt.PreOrderGo(preOrder5);
    cout<<"expected:";   preOrder5.printExpected(); cout<<endl;
    cout<<"output  :";   preOrder5.printOutput();   cout<<endl;
    height = A->height;
    cout<<"expected height of root: 4"<<endl;
    cout<<"height of root:" <<height<<endl;
    cout<<(preOrder1.test() &&height==4 ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    ---F detach from C and attach to E as right child---
    ---B and D will be removed and disposed---
    Case#9: test PreOrder traverse
    expected:A E C G F
    output  :A E C G F
    expected height of root: 4
    height of root:4
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test InOrder traverse"<<endl;
    TraverseOrderTest<char> inOrder5(in5.c_str(), 5);
    bt.InOrderGo(inOrder5);
    cout<<"expected:";   inOrder5.printExpected(); cout<<endl;
    cout<<"output  :";   inOrder5.printOutput();   cout<<endl;
    cout<<(preOrder1.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#10: test InOrder traverse
    expected:A C G E F
    output  :A C G E F
    PASS!
    */

    return 0;
}

