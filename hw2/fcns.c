#include <stdlib.h>
#include "header.h"

void left_Rotate(Tree* T, Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else x->p->right = y;
	y->left = x;
	x->p = y;
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

void right_Rotate(Tree* T, Node* x)
{
	Node* y = x->left;
	x->left = y->right;
	if (y->right != T->nil)
		y->right->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->right)
		x->p->right = y;
	else x->p->left = y;
	y->right = x;
	x->p = y;
	y->size = x->size;
	x->size = x->right->size + x->left->size + 1;
}

void RB_Insert_Fixup(Tree* T, Node* z)
{
	while (z->p->color == RED)
	{
		if (z->p == z->p->p->left)
		{
			Node* y = z->p->p->right;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->right)
			{
				z = z->p;
				left_Rotate(T, z);
			}
			else
			{
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_Rotate(T, z->p->p);
			}
		}
		else if(z->p == z->p->p->right)
		{
			Node* y = z->p->p->left;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->left)
			{
				z = z->p;
				right_Rotate(T, z);
			}
			else
			{
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_Rotate(T, z->p->p);
			}
		}
	}
	T->root->color = BLACK;
}

int OS_Insert(Tree* T, int i)
{
	// find node with key i
	Node* y = T->nil;
	Node* x = T->root;
	while (x != T->nil)
	{
		y = x;
		if (i < x->key)
			x = x->left;
		else if (i > x->key)
			x = x->right;
		else
			return 0;
	}

	Node* z = (Node*)malloc(sizeof(Node));
	z->key = i;
	z->left = T->nil;
	z->right = T->nil;
	z->size = 1;

	z->p = y;

	// size update executed right after insertion !!!
	Node* temp = z;
	while (temp->p != T->nil)
	{
		temp = temp->p;
		if(temp != T->nil)
			(temp->size)++;
	}

	if (y == T->nil)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;
	RB_Insert_Fixup(T, z);

	return i;
}

void RB_Transplant(Tree* T, Node* u, Node* v)
{
	if (u->p == T->nil)
		T->root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

Node* Tree_Min(Tree* T, Node* x)
{
	while (x->left != T->nil)
		x = x->left;
	return x;
}

void RB_Delete_Fixup(Tree* T, Node* x)
{
	Node* w;
	while ((x != T->root) && (x->color == BLACK))
	{
		if (x == x->p->left)
		{
			w = x->p->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				left_Rotate(T, x->p);
				w = x->p->right;
			}
			if ((w->left->color == BLACK) && (w->right->color == BLACK))
			{
				w->color = RED;
				x = x->p;
			}
			else if (w->right->color == BLACK)
			{
				w->left->color = BLACK;
				w->color = RED;
				right_Rotate(T, w);
				w = x->p->right;
			}
			else
			{
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				left_Rotate(T, x->p);
				x = T->root;
			}
		}
		else
		{
			w = x->p->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				right_Rotate(T, x->p);
				w = x->p->left;
			}
			if ((w->right->color == BLACK) && (w->left->color == BLACK))
			{
				w->color = RED;
				x = x->p;
			}
			else if (w->left->color == BLACK)
			{
				w->right->color = BLACK;
				w->color = RED;
				left_Rotate(T, w);
				w = x->p->left;
			}
			else
			{
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				right_Rotate(T, x->p);
				x = T->root;
			}
		}
	}
	x->color = BLACK;
}

int OS_Delete(Tree* T, int i)
{
	// find node with key i
	Node* y = T->nil;
	Node* z = T->root;
	while (z != T->nil)
	{
		y = z;
		if (i < z->key)
			z = z->left;
		else if (i > z->key)
			z = z->right;
		else break;
	}
	if (z == T->nil) return 0;

	y = z;
	int y_orig_color = y->color;
	Node* x;
	Node* temp; // update variable
	if (z->left == T->nil)
	{
		// update
		temp = z;
		while (temp->p != T->nil)
		{
			temp = temp->p;
			(temp->size)--;
		}

		x = z->right;
		RB_Transplant(T, z, z->right);
	}
	else if (z->right == T->nil)
	{
		// update
		temp = z;
		while (temp->p != T->nil)
		{
			temp = temp->p;
			(temp->size)--;
		}

		x = z->left;
		RB_Transplant(T, z, z->left);
	}
	else
	{
		y = Tree_Min(T, z->right);

		// update
		temp = y;
		while (temp->p != T->nil)
		{
			temp = temp->p;
			(temp->size)--;
		}
		temp = y;
		temp->size = temp->right->size;
		temp->size = z->left->size + z->right->size + 1;

		y_orig_color = y->color;
		x = y->right;
		if (y->p == z) x->p = y;
		else
		{
			RB_Transplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		RB_Transplant(T, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (y_orig_color == BLACK)
		RB_Delete_Fixup(T, x);

	return i;
}

int OS_SelectHelper(Node* x, int i)
{
	if (x->size < i) return 0;
	int r = x->left->size + 1;
	if (i == r)	return x->key;
	else if(i < r) return OS_SelectHelper(x->left, i);
	else return OS_SelectHelper(x->right, i - r);
}

int OS_Select(Tree* T, int i)
{
	Node* x = T->root;
	int res = OS_SelectHelper(x, i);
	return res;
}

int OS_Rank(Tree* T, int i)
{
	// find node with key i
	Node* y = T->nil;
	Node* x = T->root;
	while (x != T->nil)
	{
		y = x;
		if (i < x->key)
			x = x->left;
		else if (i > x->key)
			x = x->right;
		else break;
	}
	if (x == T->nil) return 0;

	int r = x->left->size + 1;
	y = x;
	while (y != T->root)
	{
		if (y == y->p->right)
			r += (y->p->left->size + 1);
		y = y->p;
	}
	return r;
}