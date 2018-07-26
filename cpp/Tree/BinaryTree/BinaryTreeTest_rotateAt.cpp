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
      /  \
     B    C
    / \    \
   D   E    F
             \
              G
preOrder : ABDECFG
inOrder  : DBEACFG

Rotate at A, applyToChild = true
        A
       /  \
      C    B
     /    / \  
    F    E   D
    /
   G
preOrder  : ACFGBED
inOrder   : GFCAEBD

Rotate at A, applyToChild = false
         A
        /  \
      B      C
     / \     /
    E   D   F
           /
          G
preOrder  : ABEDCFG
inOrder   : EBDAGFC

*/


int main()
{
    int kiss = 1;
    string pre1 = "ABDECFG";
    string in1 = "DBEACFG";
    string pre2 = "ACFGBED";
    string in2 = "GFCAEBD";
    string pre3 = "ABEDCFG";
    string in3 = "EBDAGFC";
    
    BinaryTree<char> bt('A');
    TNode* A = bt.Root();
    TNode* B = A->InsertLeftChild('B');
    TNode* C = A->InsertRightChild('C');
    TNode* D = B->InsertLeftChild('D');
    TNode* E = B->InsertRightChild('E');
    TNode* F = C->InsertRightChild('F');
    TNode* G = F->InsertRightChild('G');

    cout<<"Case#"<< kiss++ <<" test PreOrder "<<endl;
    TraverseOrderTest<char> preOrder1(pre1.c_str(),7);
    bt.PreOrderGo(preOrder1);
    cout<<"expected : "; preOrder1.printExpected();   cout<<endl;
    cout<<"output   : "; preOrder1.printOutput();     cout<<endl;
    cout<<(preOrder1.test()? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#1 test PreOrder
    expected : A B D E C F G
    output   : A B D E C F G
    PASS!
    */

    cout<<"Case#"<< kiss++ <<" test InOrder "<<endl;
    TraverseOrderTest<char> inOrder1(in1.c_str(),7);
    bt.InOrderGo(inOrder1);
    cout<<"expected : "; inOrder1.printExpected();     cout<<endl;
    cout<<"output   : "; inOrder1.printOutput();       cout<<endl;
    cout<<(inOrder1.test()? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#2 test InOrder
    expected : D B E A C F G
    output   : D B E A C F G
    PASS!
    */

    cout<<"---------------Rotate At A, applyToChild = true------------------"<<endl;
    bt.RotateAt(A, true);

    cout<<"Case#"<< kiss++ <<" test PreOrder "<<endl;
    TraverseOrderTest<char> preOrder2(pre2.c_str(),7);
    bt.PreOrderGo(preOrder2);
    cout<<"expected : "; preOrder2.printExpected();   cout<<endl;
    cout<<"output   : "; preOrder2.printOutput();     cout<<endl;
    cout<<(preOrder2.test()? "PASS!" : "Failed!")<<endl<<endl;
    /*
    ---------------Rotate At A, applyToChild = true------------------
    Case#3 test PreOrder
    expected : A C F G B E D
    output   : A C F G B E D
    PASS!
    */

    cout<<"Case#"<< kiss++ <<" test InOrder "<<endl;
    TraverseOrderTest<char> inOrder2(in2.c_str(),7);
    bt.InOrderGo(inOrder2);
    cout<<"expected : "; inOrder2.printExpected();     cout<<endl;
    cout<<"output   : "; inOrder2.printOutput();       cout<<endl;
    cout<<(inOrder2.test()? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#4 test InOrder
    expected : G F C A E B D
    output   : G F C A E B D
    PASS!
    */

    cout<<"---------------Rotate At A, applyToChild = false------------------"<<endl;
    bt.RotateAt(A, false);

    cout<<"Case#"<< kiss++ <<" test PreOrder "<<endl;
    TraverseOrderTest<char> preOrder3(pre3.c_str(),7);
    bt.PreOrderGo(preOrder3);
    cout<<"expected : "; preOrder3.printExpected();   cout<<endl;
    cout<<"output   : "; preOrder3.printOutput();     cout<<endl;
    cout<<(preOrder3.test()? "PASS!" : "Failed!")<<endl<<endl;
    /*
    ---------------Rotate At A, applyToChild = false------------------
    Case#5 test PreOrder
    expected : A B E D C F G
    output   : A B E D C F G
    PASS!
    */

    cout<<"Case#"<< kiss++ <<" test InOrder "<<endl;
    TraverseOrderTest<char> inOrder3(in3.c_str(),7);
    bt.InOrderGo(inOrder3);
    cout<<"expected : "; inOrder3.printExpected();     cout<<endl;
    cout<<"output   : "; inOrder3.printOutput();       cout<<endl;
    cout<<(inOrder3.test()? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#6 test InOrder
    expected : E B D A G F C
    output   : E B D A G F C
    PASS!
    */


    return 0;
}
