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


} /* namespace ft */
