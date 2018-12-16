#ifndef _HEADER_
#define _HEADER_

#define BLACK 0
#define RED 1

typedef struct node
{
	struct node* left;
	struct node* right;
	struct node* p;
	int key;
	int size;
	int color;
} Node;

typedef struct tree
{
	Node* root;
	Node* nil;
} Tree;

int OS_Insert(Tree* T, int i);
int OS_Delete(Tree* T, int i);
int OS_Select(Tree* T, int i);
int OS_Rank(Tree* T, int i);

#endif
