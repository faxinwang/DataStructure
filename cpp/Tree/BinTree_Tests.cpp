#include<iostream>
#include<cstdio>
#include<string>
#include "BinTree.hpp"
using namespace std;

void visit(string str){
	cout<<str<<" ";
}

int main(){
	BinTree<string> me("me");
	typedef BinNode<string> Node;
	Node *ma = me.insertAsLC(me.root(), "mather");
	Node *fa = me.insertAsRC(me.root(), "father");
	Node *gm = fa->insertAsLC("grandMa");
	Node *gf = fa->insertAsRC("grandFa");
	Node *ggm = gm->insertAsLC("grandGrandMa");
	Node *ggf = gf->insertAsRC("grandGrandFa");
	
	cout<<"size: "<< me.size() <<endl;					//7
	cout<<"height of me:"<< me.root()->height <<endl;	//4
	cout<<"height of ma:"<<ma->height<<endl;			//1
	cout<<"height of gm:"<<gm->height<<endl;			//2
	
	levelOrder(visit, me.root());			
	cout<<endl;
	//me mather father grandMa grandFa grandGrandMa grandGrandFa
	
	prevOrder_recursive(visit, me.root());
	cout<<endl;
	//me mather father grandMa grandGrandMa grandFa grandGrandFa
	prevOrder_iterative(visit, me.root());
	cout<<endl;
	//me mather father grandMa grandGrandMa grandFa grandGrandFa
	prevOrder_iterative2(visit, me.root());
	cout<<endl;
	//me mather father grandMa grandGrandMa grandFa grandGrandFa
	
	inOrder_recursive(visit, me.root());
	cout<<endl;
	//me mather father grandMa grandGrandMa grandFa grandGrandFa
	inOrder_iterative(visit, me.root());
	cout<<endl;
	//me mather father grandMa grandGrandMa grandFa grandGrandFa
	
	postOrder_recursive(visit, me.root());
	cout<<endl;
	//mather grandGrandMa grandMa grandGrandFa grandFa father me
	 
	return 0;
}
