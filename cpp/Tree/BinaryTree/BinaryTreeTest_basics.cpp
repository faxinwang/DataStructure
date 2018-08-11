#include<iostream>
#include<cstdio>
#include<vector>
#include "BinaryTree.hpp"
using namespace std;
using namespace wfx;

typedef Node<char> TNode;


/*              A
               / \
             /      \
          /           \
        B               C
      /  \             /  \
    /     \           /     \
   D        E        F       G
 /   \     /  \     / \    /   \
H     I   J    K   L   M   N    O
 \   / \   \   /  / \  \   \   / \
  P Q   R   S T  U   V  W   X Y   Z

preOrder  : ABDHPIQREJSKTCFLUVMWGNXOYZ
inOrder   : HPDQIRBJSETKAULVFMWCNXGYOZ
postOrder : PHQRIDSJTKEBUVLWMFXNYZOGCA
levelOrder: ABCDEFGHIJKLMNOPQRSTUVWXYZ
*/


int main()
{
    int kiss = 1;
    TNode *A = new TNode('A');
    BinaryTree<char> bt(A);

    TNode *B = A->InsertLeftChild('B');
    TNode *C = A->InsertRightChild('C');
    TNode *D = B->InsertLeftChild('D');
    TNode *E = B->InsertRightChild('E');
    TNode *F = C->InsertLeftChild('F');
    TNode *G = C->InsertRightChild('G');
    TNode *H = D->InsertLeftChild('H');
    TNode *I = D->InsertRightChild('I');
    TNode *J = E->InsertLeftChild('J');
    TNode *K = E->InsertRightChild('K');
    TNode *L = F->InsertLeftChild('L');
    TNode *M = F->InsertRightChild('M');
    TNode *N = G->InsertLeftChild('N');
    TNode *O = G->InsertRightChild('O');
    TNode *P = H->InsertRightChild('P');
    TNode *Q = I->InsertLeftChild('Q');
    TNode *R = I->InsertRightChild('R');
    TNode *S = J->InsertRightChild('S');
    TNode *T = K->InsertLeftChild('T');
    TNode *U = L->InsertLeftChild('U');
    TNode *V = L->InsertRightChild('V');
    TNode *W = M->InsertRightChild('W');
    TNode *X = N->InsertRightChild('X');
    TNode *Y = O->InsertLeftChild('Y');
    TNode *Z = O->InsertRightChild('Z');

    cout<<"Case#"<< kiss++ <<": test tree empty"<<endl;
    cout<<"expected: false"<<endl;
    cout<<"output: "<<(bt.Empty()?"true" : "false")<<endl;
    cout<<(bt.Empty()? "Failed!" : "PASS!")<<endl<<endl;
    /*
    Case#1: test tree empty
    expected: false
    output: false
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test number of node"<<endl;
    cout<<"expected : 26"<<endl;
    cout<<"output : "<<bt.Size()<<endl;
    cout<<(bt.Size()==26? "PASS!" : "Failde!")<<endl<<endl;
    /*
    Case#2: test number of node
    expected : 26
    output : 26
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test height of root node"<<endl;
    cout<<"expected : 5"<<endl;
    cout<<"output : "<<A->height<<endl;
    cout<<(A->height==5? "PASS!" : "Failde!")<<endl<<endl;
    /*
    Case#3: test height of root node
    expected : 5
    output : 5
    PASS!
    */

    /**此处的赋值运算实际调用的是拷贝构造函数, 然后拷贝构造函数里面其实
     * 是调用了赋值运算符(内部调用了Copy私有函数进行复制).
     */
    cout<<"Case#"<< kiss++ <<": test assignment operator: bt2 = bt"<<endl;
    BinaryTree<char> bt2 = bt;
    int bt2Nodes = bt2.Size();
    int bt2RootHeight=A->height;
    cout<<"bt2 nodes : "<<bt2Nodes<<endl;
    cout<<"bt2 root height:"<<bt2RootHeight<<endl;
    cout<<(bt2Nodes==26 && bt2RootHeight==5? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#4: test assignment operator: bt2 = bt
    bt2 nodes : 26
    bt2 root height:5
    PASS!
    */


    cout<<"Case#"<< kiss++ <<": test operator: bt2 == bt"<<endl;
    cout<<"expected : true"<<endl;
    bool testEqual = bt==bt2;
    cout<<"output : "<<(testEqual? "true":"false")<<endl;
    cout<<(testEqual? "PASS!":"Failed!")<<endl<<endl;
    /*
    Case#5: test operator: bt2 == bt
    expected : true
    output : true
    PASS!
    */
   

    return 0;
}
