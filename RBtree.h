#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED
#include <iostream>
using namespace std;

class Node{
private:
	friend class RBtree;
	int key;
	Node *p,*left,*right;
	int size;
	bool color;
public:
	Node(int x){
		key=x;
		size=1;
	}
};

class RBtree{
private:
	void LeftRotate(Node* );
	void RightRotate(Node* );
	void InsertFix(Node* &);
	int NUM;
	Node *Root,*Nil;
	static bool RED;
	static bool BLACK;
public:
	void Insert(int);
	RBtree(){
	    cout<<"FUCK"<<endl;
		Nil=new Node(-1);
		Nil->color=BLACK;
		Nil->size=0;
		Root=Nil;
		NUM=0;
	}
	void print();
	void print(Node* t);
};

bool RBtree::BLACK=false;
bool RBtree::RED=true;

void RBtree::print()
{
	print(Root);
}

void RBtree::print(Node* x)
{
    if(x->left!=Nil) print(x->left);
    for(int i=0;i<x->size;i++) cout<<x->key<<' ';
    if(x->right!=Nil) print(x->right);
}

void RBtree::LeftRotate(Node* x)
{
//  (a,x,(b,y,c))
//  leftRotate->
//  ((a,x,b),y,c)
	Node* y=x->right;
//  link b to x
	x->right=y->left;
	if(y->left!=Nil){
		y->left->p=x;
	}
//  link y to parent of x
	y->p=x->p;
	if (x->p==Nil){
		Root=y;
	}else{
		if (x==x->p->left){
			x->p->left=y;
		}else{
			x->p->right=y;
		}
	}
//  link x to its new father:y
	y->left=x;
	x->p=y;
}

void RBtree::RightRotate(Node *x)
{
//  ((a,y,b),x,c)
//  RightRotate
//  (a,y,(b,x,c))
	Node* y=x->left;
//  link b to x
	x->left=y->right;
	if(y->right!=Nil){
		y->right->p=x;
	}
//  link y to parent of x
	y->p=x->p;
	if (x->p==Nil){
		Root=y;
	}else{
		if(x==x->p->left){
			x->p->left=y;
		}else{
			x->p->right=y;
		}
	}
//  link x to its new father:y
	y->right=x;
	x->p=y;
}

void RBtree::Insert(int t)
{
	NUM++;
	Node* y=Nil;
	Node* x=Root;
//  y becomes father of the position ready to be Insert
	while(x!=Nil && t!=x->key){
		y=x;
		if (t<x->key){
			x=x->left;
		}else{
			x=x->right;
		}
	}
//  t already exists in the tree
	if (x!=Nil && t==x->key){
		x->size++;
		return;
	}
	Node* z=new Node(t);
//  the tree is empty
	if (y==Nil){
		Root=z;
	}
	z->p=y;
	if(z->key<y->key){
		y->left=z;
	}else{
		y->right=z;
	}
	z->left=Nil;
	z->right=Nil;
	z->color=RED;
	InsertFix(z);
}

/*
Reference:

http://alrightchiu.github.io/SecondRound/red-black-tree-insertxin-zeng-zi-liao-yu-fixupxiu-zheng.html


*/



void RBtree::InsertFix(Node * &z)
{
	while(z->p->color==RED){
		if (z->p==z->p->p->left){
			Node* y=z->p->p->right;
			if(y->color==RED){
				z->p->color=BLACK;
				y->color=BLACK;
				z->p->p->color=RED;
				z=z->p->p;
			}else{
				if (z==z->p->right){
					z=z->p;
					LeftRotate(z);
				}
				z->p->color=BLACK;
				z->p->p->color=RED;
				RightRotate(z->p->p);
			}
		}else{
			Node* y=z->p->p->left;
			if(y->color==RED){
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}else{
				if (z==z->p->left){
					z=z->p;
					RightRotate(z);
				}
				z->p->color=BLACK;
				z->p->p->color=RED;
				LeftRotate(z->p->p);
			}
		}
	}
	Root->color=BLACK;
}



#endif // RBTREE_H_INCLUDED
