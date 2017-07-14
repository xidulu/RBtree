#ifndef RBTREE_H
#define RBTREE_H


class Node{
private:
	friend class RBtree;
	int key;
	Node *parent,*left,*right;
	int size;
	bool color;
public:
	Node(int x){
		key=x;
		size=1;
	}
}

class RBtree{
private:
	void LeftRotate(Node* );
	void RightRotate(Node* );
	void InsertFix(Node*)
	int NUM;
	Node *Root,*Nil;
	static bool RED;
	static bool BLACK;
public:
	void Insert(int);
}

bool RBtree::BLACK=false;
bool RBtree::RED=true;

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
			x->p->rigth=y;
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
({B},({R},({R},A,x,B),y,C),z,D) 
({B},A,x,({R},B,y,({R},C,z,D))) 
({B},({R},A,x,({R},B,y,C)),z,D) 
({B},A,z,({R},({R},B,y,C),z,D)) 
balcance-> 
({R},({B},A,x,B),y,({B},C,z,D)) 
*/  


void RBtree::InsertFix(Node *x)
{
	 
}

#endif