#include "rb_tree.hpp"

namespace ft
{

size_t _rb_tree_black_count(const node_base *node, const node_base *root) throw()
{
	size_t len = 0;
	if (node != NULL)
		while (node != root)
		{
			if (node->color == kBlack)
				++len;
			node = node->parent;
		}
	return len;
}


node_base*			_rb_tree_increment(node_base * x) throw()
{
	if (x->right != 0)
	{
		x = x->right;
		while (x->left != 0)
			x = x->left;
	}
	else
	{
		node_base* y = x->parent;
		while (x == y->right)
		{
			x = y;
			y = y->parent;
		}
		if (x->right != y)
			x = y;
	}
	return x;
}
const node_base*	_rb_tree_increment(const node_base *x) throw()
{
	if (x->right != 0)
	{
		x = x->right;
		while (x->left != 0)
			x = x->left;
	}
	else
	{
		node_base* y = x->parent;
		while (x == y->right)
		{
			x = y;
			y = y->parent;
		}
		if (x->right != y)
			x = y;
	}
	return x;
}
node_base*			_rb_tree_decrement(node_base * x) throw()
{
	if (x->color == kRed && x->parent->parent == x)
		x = x->right;
	else if (x->left != 0)
	{
		node_base* y = x->left;
		while (y->right != 0)
			y = y->right;
		x = y;
	}
	else
	{
		node_base* y = x->parent;
		while (x == y->left)
		{
			x = y;
			y = y->parent;
		}
		x = y;
	}
	return x;
}
const node_base *	_rb_tree_decrement(const node_base *x) throw()
{
	if (x->color == kRed && x->parent->parent == x)
		x = x->right;
	else if (x->left != 0)
	{
		node_base* y = x->left;
		while (y->right != 0)
			y = y->right;
		x = y;
	}
	else
	{
		node_base* y = x->parent;
		while (x == y->left)
		{
			x = y;
			y = y->parent;
		}
		x = y;
	}
	return x;
}

/*      y   right rotate     x
/      / \  ------------>   / \ 
/     x	  c                 a   y 
/    / \     left rotate       / \ 
/   a   b   <------------     b   c
*/
void _leftRotate(node_base *x, node_base*& root)
{
	assert(x->right != NULL);

	node_base* const y = x->right;

	x->right = y->left; // turn y’s left subtree into x’s right subtree
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent; // link x’s parent to y

	if (x == root)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x; // put x on y’s left
	x->parent = y;
}

 void _rightRotate(node_base *x, node_base*& root)
{
	assert(x->left != NULL);

	node_base* const y = x->left;

	x->left = y->right; // turn y’s left subtree into x’s right subtree
	if (y->right != NULL)
		y->right->parent = x;
	y->parent = x->parent; // link x’s parent to y

	if (x == root)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x; // put x on y’s left
	x->parent = y;
}


} /* namespace ft */
