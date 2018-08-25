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
  
    cout<<"after remove 'A': "<<endl;
    splay.Remove('A');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after remove 'D': "<<endl;
    splay.Remove('D');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after remove 'E': "<<endl;
    splay.Remove('E');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after remove 'N': "<<endl;
    splay.Remove('N');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after remove 'M': "<<endl;
    splay.Remove('M');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after remove 'B': "<<endl;
    splay.Remove('B');
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    splay.Remove('C');
    splay.Remove('F');
    splay.Remove('G');
    splay.Remove('H');
    splay.Remove('I');
    splay.Remove('J');
    splay.Remove('K');
    cout<<"after remove C F G H I J K"<<endl;
    splay.PreOrderGo(visit);    cout<<endl;
    splay.InOrderGo(visit);     cout<<endl;
    cout<<endl;

    cout<<"after remove the last element 'L' "<<endl;
    splay.Remove('L');
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

after remove 'A':
B N L J H F D C E G I K M
B C D E F G H I J K L M N
               B
                 \
                   \
                     N
                    /
                   L
                  / \
                 J    M
                / \
               H   K
              / \
             F   I
            / \
           D   G
          / \
         C   E

after remove 'D':
E B C N J F H G I L K M
B C E F G H I J K L M N
                   E
                 /   \ 
               /       \
              B         N
               \       /
                C     J
                    /   \
                   F      L
                    \    / \
                     H  K   M
                    / \
                   G   I

after remove 'E':
F B C N J H G I L K M
B C F G H I J K L M N
                   F
                 /   \
               /       \
              B         N
               \       / 
                C     J
                    /   \
                   H     L
                  / \   / \
                 G   I K   M

after remove 'N':
M F B C J H G I L K
B C F G H I J K L M
                M
              /  
            /    
           F        
         /   \    
        B      J
        \    /   \
         C  H     L
           / \   /
          G   I K  

after remove 'M':
L F B C J H G I K
B C F G H I J K L
              L
             /
            F
          /   \
         B     J
         \    / \
          C  H   K
            / \
           G   I

after remove 'B':
C F L J H G I K
C F G H I J K L
           C
            \
             F
              \
               L
              /
             J
            / \
           H   K
          / \
         G   I

after remove C F G H I J K
L
L

after remove the last element 'L'

*/   
