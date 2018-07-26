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

    void operator()(T& t) { vis.push_back(t); }

    bool test(){ vis == expected; }

    void printExpected()
    { for(int i=0,n=expected.size(); i<n;++i) cout<<expected[i]<<' '; }

    void printOutput(){ for(int i=0,n=vis.size(); i<n;++i) cout<<vis[i]<<' '; }
};


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
    int kiss = 0;
    string pre = "ABDHPIQREJSKTCFLUVMWGNXOYZ";
    string in = "HPDQIRBJSETKAULVFMWCNXGYOZ";
    string post = "PHQRIDSJTKEBUVLWMFXNYZOGCA";
    string level = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    BinaryTree<char> bt = BinaryTree<char>::BuildFromPreInOrder(pre.c_str(), in.c_str(),26);
    TNode*A = bt.Root();
    cout<<"---------Build tree from PreOrder and InOrder---------"<<endl;

    cout<<"Case#"<< kiss++ <<": test number of nodes"<<endl;
    cout<<"expected: 26"<<endl;
    int numOfNode = A->Size();
    cout<<"output:"<<numOfNode<<endl;
    cout<<(numOfNode == 26 ? "PASS!" : "Failed!")<<endl<<endl;
    /*
     ---------Build tree from PreOrder and InOrder---------
    Case#0: test number of nodes
    expected: 26
    output:26
    PASS!
    */


    cout<<"Case#"<< kiss++ <<": test the height of root node"<<endl;
    cout<<"expected: 4"<<endl;
    cout<<"output:"<<A->height<<endl;
    cout<<(A->height !=4? "Failed!" : "PASS!")<<endl<<endl;
    /*
    Case#1: test the height of root node
    expected: 4
    output:4
    PASS!
    */


   cout<<"Case#"<< kiss++ <<": test levelOrder traverse"<<endl;
   TraverseOrderTest<char> levelOrder(level.c_str(), 26);
   bt.LevelOrderGo(levelOrder);
   cout<<"expected:";   levelOrder.printExpected(); cout<<endl;
   cout<<"output  :";   levelOrder.printOutput();   cout<<endl;
   cout<<(levelOrder.test() ? "PASS!" : "Failed!")<<endl<<endl;
   /*
    Case#2: test levelOrder traverse
    expected:A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    output  :A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    PASS!
   */

    
    cout<<"Case#"<< kiss++ <<": test PreOrder traverse"<<endl;
    TraverseOrderTest<char> preOrder(pre.c_str(), 26);
    bt.PreOrderGo(preOrder);
    cout<<"expected:";   preOrder.printExpected(); cout<<endl;
    cout<<"output  :";   preOrder.printOutput();   cout<<endl;
    cout<<(preOrder.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#3: test PreOrder traverse
    expected:A B D H P I Q R E J S K T C F L U V M W G N X O Y Z
    output  :A B D H P I Q R E J S K T C F L U V M W G N X O Y Z
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test InOrder traverse"<<endl;
    TraverseOrderTest<char> inOrder(in.c_str(), 26);
    bt.InOrderGo(inOrder);
    cout<<"expected:";   inOrder.printExpected(); cout<<endl;
    cout<<"output  :";   inOrder.printOutput();   cout<<endl;
    cout<<(inOrder.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#4: test InOrder traverse
    expected:H P D Q I R B J S E T K A U L V F M W C N X G Y O Z
    output  :H P D Q I R B J S E T K A U L V F M W C N X G Y O Z
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test PostOrder traverse"<<endl;
    TraverseOrderTest<char> postOrder(post.c_str(), 26);
    bt.PostOrderGo(postOrder);
    cout<<"expected:";   postOrder.printExpected(); cout<<endl;
    cout<<"output  :";   postOrder.printOutput();   cout<<endl;
    cout<<(postOrder.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#5: test PostOrder traverse
    expected:P H Q R I D S J T K E B U V L W M F X N Y Z O G C A
    output  :P H Q R I D S J T K E B U V L W M F X N Y Z O G C A
    PASS!
    */


    bt = BinaryTree<char>::BuildFromPostInOrder(post.c_str(),in.c_str(),26);
    A = bt.Root();
    cout<<"---------Build tree from PostOrder and InOrder---------"<<endl;

    cout<<"Case#"<< kiss++ <<": test number of nodes"<<endl;
    cout<<"expected: 26"<<endl;
    numOfNode = A->Size();
    cout<<"output:"<<numOfNode<<endl;
    cout<<(numOfNode == 26 ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    ---------Build tree from PostOrder and InOrder---------
    Case#6: test number of nodes
    expected: 26
    output:26
    PASS!
    */


    cout<<"Case#"<< kiss++ <<": test the height of root node"<<endl;
    cout<<"expected: 4"<<endl;
    cout<<"output:"<<A->height<<endl;
    cout<<(A->height !=4? "Failed!" : "PASS!")<<endl<<endl;
    /*
    Case#7: test the height of root node
    expected: 4
    output:4
    PASS!
    */


    cout<<"Case#"<< kiss++ <<": test levelOrder traverse"<<endl;
    TraverseOrderTest<char> levelOrder2(level.c_str(), 26);
    bt.LevelOrderGo(levelOrder2);
    cout<<"expected:";   levelOrder2.printExpected(); cout<<endl;
    cout<<"output  :";   levelOrder2.printOutput();   cout<<endl;
    cout<<(levelOrder2.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#8: test levelOrder traverse
    expected:A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    output  :A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    PASS!
    */

    
    cout<<"Case#"<< kiss++ <<": test PreOrder traverse"<<endl;
    TraverseOrderTest<char> preOrder2(pre.c_str(), 26);
    bt.PreOrderGo(preOrder2);
    cout<<"expected:";   preOrder2.printExpected(); cout<<endl;
    cout<<"output  :";   preOrder2.printOutput();   cout<<endl;
    cout<<(preOrder2.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#9: test PreOrder traverse
    expected:A B D H P I Q R E J S K T C F L U V M W G N X O Y Z
    output  :A B D H P I Q R E J S K T C F L U V M W G N X O Y Z
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test InOrder traverse"<<endl;
    TraverseOrderTest<char> inOrder2(in.c_str(), 26);
    bt.InOrderGo(inOrder2);
    cout<<"expected:";   inOrder2.printExpected(); cout<<endl;
    cout<<"output  :";   inOrder2.printOutput();   cout<<endl;
    cout<<(inOrder2.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#10: test InOrder traverse
    expected:H P D Q I R B J S E T K A U L V F M W C N X G Y O Z
    output  :H P D Q I R B J S E T K A U L V F M W C N X G Y O Z
    PASS!
    */

    cout<<"Case#"<< kiss++ <<": test PostOrder traverse"<<endl;
    TraverseOrderTest<char> postOrder2(post.c_str(), 26);
    bt.PostOrderGo(postOrder2);
    cout<<"expected:";   postOrder2.printExpected(); cout<<endl;
    cout<<"output  :";   postOrder2.printOutput();   cout<<endl;
    cout<<(postOrder2.test() ? "PASS!" : "Failed!")<<endl<<endl;
    /*
    Case#11: test PostOrder traverse
    expected:P H Q R I D S J T K E B U V L W M F X N Y Z O G C A
    output  :P H Q R I D S J T K E B U V L W M F X N Y Z O G C A
    PASS!
    */

    return 0;
}
