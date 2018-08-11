#include<iostream>
#include<cstdlib>
#include "AVLTree.hpp"
using namespace std;
using namespace wfx;


void visit(char ch){ cout<<ch<<' '; }


int main()
{
    AVLTree<char> avl;
    printf("insert from 'A' to 'Z' :\n");
    for(char ch='A'; ch<='Z'; ++ch) avl.Insert(ch);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
    cout<<endl;
    avl.Clear();
    
    printf("insert from 'Z' to 'A' :\n");
    for(char ch='Z'; ch>='A'; --ch) avl.Insert(ch);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
    cout<<endl;
    avl.Clear();
    
    srand(107);
    string abc="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0; i<26; ++i) std::swap(abc[i], abc[rand()%26] );
    printf("insert sequence \"%s\"\n",abc.c_str());
    for(int i=0; i<26; ++i) avl.Insert(abc[i]);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;
	  cout<<endl;
    avl.Clear();
	
    srand(1007);
    abc="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0; i<26; ++i) std::swap(abc[i], abc[rand()%26] );
    printf("insert sequence \" %s \"\n",abc.c_str());
    for(int i=0; i<26; ++i) avl.Insert(abc[i]);
    cout<<"preOrder: "; avl.PreOrderGo(visit); cout<<endl;
    cout<<"inOrder : "; avl.InOrderGo(visit);  cout<<endl;

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


insert from 'Z' to 'A' :
preOrder: K G C B A E D F I H J S O M L N Q P R W U T V Y X Z
inOrder : A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
                           K
                        /     \
                      /         \
                    /             \
                   G               S
                  / \             /   \
                 /   \          /       \ 
                C     I        O          W
              /  \   / \     /   \       /  \
             B    E  H  J   M     Q     U    Y
            /    / \       / \   / \   / \   / \
           A    D   F     L   N P   R T   V X   Z

insert sequence "CZVNWTPREXHKUSGMIFLBDJQAOY"
preOrder: N H E C B A D G F K I J M L V R P O Q T S U X W Z Y
inOrder : A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
                            N
                         /    \
                       /        \
                     /            \
                    H                V
                  /   \             /  \
                 /     \           /     \
                E        K        R       X 
               /  \    /   \     /  \    /  \
             C     G  I     M   P    T   W   Z
            / \   /    \   /   / \  / \     /
           B   D F      J L   O   Q S  U   Y   
          /    
         A  


insert sequence " QFKEOSZNHLMIJGWRDAXVCTPUBY "
preOrder: N H D B A C F E G K I J L M S Q O P R V T U X W Z Y
inOrder : A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
                            N
                         /    \
                       /        \
                     /            \
                    H              S
                  /   \           /  \ 
                 /     \         /    \
                D       K       Q       V
              /  \     / \     / \    /   \
            B     F   I   L   O   R  T     X
           / \   / \   \   \   \      \   / \
          A   C E   G   J   M   P      U W   Z
                                            /
                                           Y

可以看出, 按照从A到Z的顺序往AVL树中插入元素,最终得到的AVL树确实
是满足平衡定义的,而且其平衡性从上图中来看,确实比BST优秀了很多
*/                                          
