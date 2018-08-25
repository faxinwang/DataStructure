#include<iostream>
#include "SplayTree.hpp"
using namespace std;
using namespace wfx;

void visit(char ch){ cout<<ch<<' '; }

int main()
{
    SplayTree<char> splay;

    cout<<"after insert from 'A' to 'N':"<<endl;
    for(char ch='A'; ch<='N'; ++ch) splay.Insert(ch);
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after search 'A':"<<endl;
    splay.Search('A');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after search 'C':"<<endl;
    splay.Search('C');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after search 'I':"<<endl;
    splay.Search('I');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;


    return 0;
}
/*
after insert from 'A' to 'N':
N M L K J I H G F E D C B A
A B C D E F G H I J K L M N
                            N
                           /
                          M
                         /
                        L
                       /
                      K
                     /
                    J
                   /
                  I
                 /
                H
               /
              G
             /
            F
           /
          E
         /
        D
       /
      C
     /
    B
   /
  A

after search 'A':
A N L J H F D B C E G I K M
A B C D E F G H I J K L M N
                   A
                     \
                       \
                         \
                           N
                          /
                         L
                        / \
                       J   M
                      / \
                     H   K
                    / \
                   F   I
                  / \
                 D   G
                / \
               B   E
                \
                 C

after search 'C':
C A B N J F D E H G I L K M
A B C D E F G H I J K L M N
                        C
                      /    \
                    /        \
                   A          N
                   \         / 
                    B       J
                          /   \
                        F      L
                      /   \   /  \
                     D     H  K   M
                      \   / \
                       E G   I

after search 'I':
I C A B H F D E G J N L K M
A B C D E F G H I J K L M N
                     I
                   /   \
                 /       J
               C          \
             /   \         N
            A      H      /
             \    /      L
              B  F      / \
                / \    K   M
               D   G
                \
                 E
(可以发现, 在分别查询了C和I之后, C与I之间的所有元素就都在一颗局部子树上了, 这样删除区间[C,I]就很快很方便了)

*/
