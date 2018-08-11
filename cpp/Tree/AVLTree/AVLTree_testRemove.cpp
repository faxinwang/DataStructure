#include<iostream>
#include<cstdlib>
#include "AVLTree.hpp"
using namespace std;
using namespace wfx;


void visit(char ch){ cout<<ch<<' '; }


int main()
{
    char ch;
    AVLTree<char> avl;
    printf("insert from 'A' to 'Z' :\n");
    for(ch='A'; ch<='Z'; ++ch) avl.Insert(ch);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
    cout<<endl;
  
    ch='Y';
    avl.Remove(ch);
    printf("after remove %c\n",ch);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
    cout<<endl;

    ch='Z';
    avl.Remove(ch);
    printf("after remove %c\n",ch);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
    cout<<endl;

    ch='X';
    avl.Remove(ch);
    printf("after remove %c\n",ch);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
    cout<<endl;

    ch='P';
    avl.Remove(ch);
    printf("after remove %c\n",ch);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
    cout<<endl;

    return 0;
}

/*
insert from 'A' to 'Z' :
preOrder: P H D B A C F E G L J I K N M O T R Q S X V U W Y Z
inOrder : A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
                           P
                        /     \
                      /         \
                    /             \
                  H                T
                /  \             /  \
               /     \          /    \
             D        L        R      X
            / \      / \      / \    / \
           B   F    J    N   Q   S  V   Y   
          / \ / \  / \  / \        / \   \
         A  C E  G I  K M  O      U   W   Z

after remove Y
preOrder: P H D B A C F E G L J I K N M O T R Q S X V U W Z
inOrder : A B C D E F G H I J K L M N O P Q R S T U V W X Z
                           P
                        /     \
                      /         \
                    /             \
                  H                T
                /  \             /  \
               /     \          /    \
             D        L        R      X
            / \      / \      / \    / \
           B   F    J    N   Q   S  V   Z
          / \ / \  / \  / \        / \ 
         A  C E  G I  K M  O      U   W


after remove Z
preOrder: P H D B A C F E G L J I K N M O T R Q S W V U X
inOrder : A B C D E F G H I J K L M N O P Q R S T U V W X
                           P
                        /     \
                      /         \
                    /             \
                  H                T
                /  \             /  \
               /     \          /    \
             D        L        R      W
            / \      / \      / \    / \
           B   F    J    N   Q   S  V   X
          / \ / \  / \  / \        /
         A  C E  G I  K M  O      U   

after remove X
preOrder: P H D B A C F E G L J I K N M O T R Q S V U W
inOrder : A B C D E F G H I J K L M N O P Q R S T U V W
                           P
                        /     \
                      /         \
                    /             \
                  H                T
                /  \             /  \
               /     \          /    \
             D        L        R      V
            / \      / \      / \    / \
           B   F    J    N   Q   S  U    W
          / \ / \  / \  / \  
         A  C E  G I  K M  O 

after remove P
preOrder: Q H D B A C F E G L J I K N M O T R S V U W
inOrder : A B C D E F G H I J K L M N O Q R S T U V W
                            Q
                         /     \
                       /         \
                     /             \
                     H              T
                  /    \           /  \
                 /      \         /    \
                D         L      R      V
              /   \      /  \     \    / \
             B     F    J    N     S  U   W
            / \   / \  / \  / \
           A   C E   G I  K M  O
*/   
