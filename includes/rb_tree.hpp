#ifndef RB_TREE
#define RB_TREE

/**
 *  Rb tree rules
 * 
 *  1. a node is either red or black
 *  2. the root and leaves (NIL) are black
 *  3. if a node is red, then its children are black
 *  4. all paths from a node to its NIL descendants
 * 		contain the same number of black nodes
 * 
 *           8                            B                  
 *        /     \                      /     \               
 *       5       15                   B       R               
 * 	    / \     /   \                / \     /   \                 
 *    nil nil  12     19           nil nil  B      B               
 *            /   \   /  \                 / \     / \          
 *          9    13 nil   23             R     R  nil  R    
 *        /  \   / \     /  \          /  \   / \     /  \  
 *     nil  nil nil nil nil nil     nil  nil nil nil nil nil
 *  
 * Notes:
 *    The longest path (root to farthest NIL) is no more
 *  than twice the length of shortest path (root to nearest NIL)
 *   - SHortest path: all black nodes
 *   - Longest path: alernating red and black
 *
 */

#include <memory>
#include <cassert>

#include <iostream>

#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{

enum color { kBlack = false,	kRed = true, };



struct node_base
{
	typedef node_base*			base_ptr;
	typedef const node_base*	const_base_ptr;

	enum color color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	static base_ptr _s_minimum(base_ptr iterator)
	{
		while (iterator->left)
			iterator = iterator->left;
		return iterator;
	}
	static const_base_ptr _s_minimum(const_base_ptr iterator)
	{
		while (iterator->left)
			iterator = iterator->left;
		return iterator;
	}
	static base_ptr _s_maximum(base_ptr iterator)
	{
		while (iterator->right)
			iterator = iterator->right;
		return iterator;
	}
	static const_base_ptr _s_maximum(const_base_ptr iterator)
	{
		while (iterator->right)
			iterator = iterator->right;
		return iterator;
	}
}; /* struct node_base */

template <class T>
struct node : public node_base
{
	typedef node<T>* link_type;

	T data;

	node(const T& val): data(val){}
	T*			_m_dataPtr()		{ return &data;}
	const T*	_m_dataPtr() const 	{ return &data;}
}; /* struct node */

node_base*			_rb_tree_increment(node_base * x) throw();
const node_base*	_rb_tree_increment(const node_base *x) throw();
node_base*			_rb_tree_decrement(node_base * __x) throw();
const node_base *	_rb_tree_decrement(const node_base *__x) throw();

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

template <typename T>
struct RbTree_iterator
{
	typedef T value_type;
	typedef T &reference;
	typedef T *pointer;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

	typedef RbTree_iterator<T> Self;
	typedef node_base::base_ptr base_ptr;
	typedef node<T> *link_type;

	RbTree_iterator()						: _node() {}
	RbTree_iterator(base_ptr ptr) throw()	: _node(ptr) {}

	reference operator*() const throw() { return *static_cast<link_type>(_node)->_m_dataPtr(); }
	pointer operator->() const throw()	{ return static_cast<link_type>(_node)->getDataPtr(); }

	Self &operator++() throw()	{ _node = _rb_tree_increment(_node); return *this; }
	Self operator++(int) throw(){ Self tmp = *this; _node = _rb_tree_increment(_node); return tmp; }

	Self &operator--() throw()	{ _node = _rb_tree_decrement(_node); return *this; }
	Self operator--(int) throw(){ Self __tmp = *this; _node = _rb_tree_decrement(_node); return __tmp; }

	friend bool operator==(const Self &x, const Self &y) throw() { return x._node == y._node; }
	friend bool operator!=(const Self &x, const Self &y) throw() { return !(x._node == y._node); }

	base_ptr _node;
}; /* struct RbTree_iterator */

template <typename T>
struct RbTree_const_iterator
{
	typedef T value_type;
	typedef const T &reference;
	typedef const T *pointer;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

	typedef RbTree_const_iterator<T> Self;
	typedef node_base::const_base_ptr base_ptr;
	typedef const node<T> *link_type;

	RbTree_const_iterator()						: _node() {}
	RbTree_const_iterator(base_ptr ptr) throw()	: _node(ptr) {}

	reference operator*() const throw() { return *static_cast<link_type>(_node)->_m_dataPtr(); }
	pointer operator->() const throw()	{ return static_cast<link_type>(_node)->getDataPtr(); }

	Self &operator++() throw()	{ _node = _rb_tree_increment(_node); return *this; }
	Self operator++(int) throw(){ Self tmp = *this; _node = _rb_tree_increment(_node); return tmp; }

	Self &operator--() throw()	{ _node = _rb_tree_decrement(_node); return *this; }
	Self operator--(int) throw(){ Self __tmp = *this; _node = _rb_tree_decrement(_node); return __tmp; }

	friend bool operator==(const Self &x, const Self &y) throw() { return x._node == y._node; }
	friend bool operator!=(const Self &x, const Self &y) throw() { return !(x._node == y._node); }

	base_ptr _node;
}; /* struct RbTree_const_iterator */

struct rb_tree_header
{
	node_base _header;
	size_t	_nodeCount;

	rb_tree_header() throw() { _header.color = kRed; reset(); }

	void reset() throw()
	{
		_header.parent = NULL;
		_header.left = &_header;
		_header.right = &_header;
		_nodeCount = 0;
	}
};

template <typename _Compare>
struct rb_tree_key_compare
{
	_Compare _m_key_compare;

	rb_tree_key_compare()
		: _m_key_compare() {}
	rb_tree_key_compare(const _Compare& compare)
		: _m_key_compare(compare) {}
};

template<typename _Key, typename _Val, typename _KeyOfValue,
       typename _Compare = std::less<_Key>, typename _Alloc = ::std::allocator<_Val> >
class rbTree
{
public:
	typedef _Val 				value_type;
	typedef _Compare 			value_compare;
	typedef _Alloc				allocator_type;
private:
    // typedef std::allocator_traits<allocator_type>      _alloc_traits;
public:
	// typedef _Key 									key_type;

	// typedef typename _alloc_traits::pointer			*pointer;
	// typedef typename _alloc_traits::const_pointer	*const_pointer;
	// typedef typename _alloc_traits::size_type		size_type;
	// typedef typename _alloc_traits::difference_type	difference_type;
	typedef value_type								*pointer;
	typedef const value_type						*const_pointer;
	typedef size_t									size_type;
	typedef std::ptrdiff_t							difference_type;

	typedef value_type								&reference;
	typedef const value_type						&const_reference;
	
	typedef RbTree_iterator<value_type>				iterator;
	typedef RbTree_const_iterator<value_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
	typedef node_base			*base_ptr;
	typedef const node_base 	*const_base_ptr;

	typedef node<_Val>			*link_type;
	typedef const node<_Val>	*const_link_type;

	typedef typename _Alloc::template rebind< node<_Val> >::other		node_allocator;
    // typedef std::allocator_traits<node_allocator>     					node_traits;

	template <typename __Compare>
	struct rbTree_impl
		: public rb_tree_header,
		  public rb_tree_key_compare<__Compare>
	{
		rb_tree_key_compare<_Compare> com;

		rbTree_impl() {}
		~rbTree_impl() {}

	};
	rbTree_impl<_Compare> _m_impl;

public:
	static node_allocator nodeAlloc;

	rbTree() {}
	~rbTree() {}

	iterator				begin()		  	{ return iterator(_m_impl._header.left);}
	const_iterator			begin() const 	{ return const_iterator(_m_impl._header.left);}
	iterator 				end()		  	{ return iterator(&_m_impl._header);}
	const_iterator			end() const	  	{ return const_iterator(&_m_impl._header);}
	reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }
	reverse_iterator		rend() 			{ return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const 	{ return const_reverse_iterator(begin()); }

	bool			empty() const				{ return _m_impl._nodeCount == 0; }
	size_type		size() const				{ return _m_impl._nodeCount; }
	size_type		max_size() const throw()	{ return nodeAlloc.max_size(); }

	allocator_type get_allocator() const throw(){ return allocator_type();}

	void insert_unique(const value_type& v)
	{
		_m_insert(v);
	}

	template <typename _InputIterator>
	void insert_range_unique(_InputIterator first, _InputIterator last)
	{
		(void)first;
		(void)last;
		// while( first != end)
	}
	void erase(iterator position) {(void)position;}
	void erase(iterator first, iterator last) {(void)first;(void)last;}
	void erase_unique(const _Key& k) {(void)k;}

	void swap(rbTree& other)	{(void)other;}
	void clear() {}

	_Compare	key_comp() const { return _m_impl._m_key_compare;}

	iterator		find(const _Key& k)					{(void)k; return begin(); }
	const_iterator	find(const _Key& k)const			{(void)k; return begin(); }
	size_type		count_unique(const _Key& k)const 	{(void)k; return begin(); }
	iterator		lower_bound(const _Key& k)		 	{(void)k; return begin(); }
	const_iterator	lower_bound(const _Key& k)const		{(void)k; return begin(); }
	iterator		upper_bound(const _Key& k)		 	{(void)k; return begin(); }
	const_iterator	upper_bound(const _Key& k)const		{(void)k; return begin(); }

	pair<iterator,iterator>    equal_range(const _Key& k)
		{(void)k; return make_pair<iterator, iterator>(begin(), begin());}
	pair<const_iterator,const_iterator>    equal_range(const _Key& k) const
		{(void)k; return make_pair<const_iterator, const_iterator>(begin(), begin());}



private:
	base_ptr				_m_root()					throw() { return _m_impl._header.parent;}
	const_base_ptr			_m_root()const				throw() { return _m_impl._header.parent;}
	
	base_ptr				_m_leftmost()				throw() { return _m_impl._header.parent->left;}
	const_base_ptr			_m_leftmost()const			throw() { return _m_impl._header.parent->left;}
	
	base_ptr				_m_rightmost()				throw() { return _m_impl._header.parent->right;}
	const_base_ptr			_m_rightmost()const			throw() { return _m_impl._header.parent->right;}
	
	link_type				_m_begin()					throw() { return static_cast<link_type>(_m_impl._header.parent);}
	const_link_type			_m_begin()const				throw() { return static_cast<const_link_type>(_m_impl._header.parent);}
	
	link_type				_m_end()					throw() { return static_cast<link_type>(&_m_impl._header);}
	const_link_type			_m_end()const 				throw() { return static_cast<const_link_type>(&_m_impl._header);}

	static const _Key&		_s_key(const_link_type x) 	throw()	{ return *x->_m_dataPtr();}
	static const _Key&		_s_key(const_base_ptr x)  	throw()	{ return _s_key(static_cast<const_link_type>(x)) ;}

	static link_type		_s_left(base_ptr x)		 	throw() { return static_cast<link_type>(x->left);}
	static const_link_type	_s_left(const_base_ptr x)	throw() { return static_cast<const_link_type>(x->left);}

	static link_type		_s_right(base_ptr x)		throw()	{ return static_cast<link_type>(x->right);}
	static const_link_type	_s_right(const_base_ptr x)	throw()	{ return static_cast<const_link_type>(x->right);}

	static base_ptr 		_s_minimum(base_ptr x)		throw()	{ return node_base::_s_minimum(x); }
	static const_base_ptr 	_s_minimum(const_base_ptr x)throw()	{ return node_base::_s_minimum(x); }

	static base_ptr 		_s_maximum(base_ptr x)		throw()	{ return node_base::_s_maximum(x); }
	static const_base_ptr 	_s_maximum(const_base_ptr x)throw()	{ return node_base::_s_maximum(x); }

	// base_ptr		_m_header()	{ return &_header;} // remove at the end ???

	pair<base_ptr, base_ptr> _m_get_insert_pos(const value_type& v)
	{
		base_ptr x = static_cast<link_type>(_m_begin());
		base_ptr y = _m_end();
		bool comp = true;
		while (x != NULL)
		{
			y = x;
			comp = _m_impl._m_key_compare(v, _s_key(x));
			x = comp ? _s_left(x) : _s_right(x);
		}
		iterator j(y);
		if (comp) // if comp true (v < parent node), then additional check 
		{
			if (j == begin()) // if parent of v  is actually the min node
				return pair<base_ptr, base_ptr>(x, y);
			else //else decrease to then check if --j.value < v 
				--j;
		}
		if (_m_impl._m_key_compare(_s_key(j._node), v)) //if false then, there is already a node with same value
			return pair<base_ptr, base_ptr>(x, y);
		return pair<base_ptr, base_ptr>(j._node, 0);
	}

	void _m_insert(const value_type& v)
	{
		// ++_m_impl._nodeCount;
		
		link_type z = nodeAlloc.allocate(1);
		nodeAlloc.construct(z, v);


		////////////////////////////////////
		////////////////////////////////////
		base_ptr y = _m_end();
		base_ptr x = static_cast<link_type>(_m_begin());
		while (x != NULL)
		{
			y = x;
			x = _m_impl._m_key_compare(v, _s_key(x)) ? _s_left(x) : _s_right(x);
		}
		z->parent = y;
		if (y == &_m_impl._header) // if first node 
		{
			_m_impl._header.left = z;	//maintain leftmost pointing to min node
			_m_impl._header.right = z;	// maintain rightmost
			_m_impl._header.parent = z;
		}
		else if (_m_impl._m_key_compare(_s_key(z), _s_key(y)))
			y->left = z;
		else
			y->right = z;
		z->left = 0;
		z->right = 0;
		z->color = kRed;

		_rebalance(y, z);
	}

	void _rebalance(base_ptr y, link_type z)
	{
		while (z->parent->color == kRed)
		{
			if (z->parent == z->parent->parent->left)
			{
				y = z->parent->parent->right;
				if (y->color == kRed)
				{
					z->parent->color = kBlack;
					y->color = kBlack;
					z->parent->parent->color = kRed;
					z = static_cast<link_type>(z->parent->parent);
				}
				else 
				{
					if (z == z->parent->right)
					{
						z = z.p;
						_leftRotate(y, _m_root());
					}
					z->parent->color = kBlack;
					z->parent->parent->color = kRed;
					_rightRotate(y->parent->parent, _m_root());
				}
			}
			else
			{
				y = z->parent->parent->left;
				if (y->color == kRed)
				{
					z->parent->color = kBlack;
					y->color = kBlack;
					z->parent->parent->color = kRed;
					z = static_cast<link_type>(z->parent->parent);
				}
				else 
				{
					if (z == z->parent->left)
					{
						z = z.p;
						_rightRotate(y, _m_root());
					}
					z->parent->color = kBlack;
					z->parent->parent->color = kRed;
					_leftRotate(y->parent->parent, _m_root());
				}
			}
		}
		_m_begin()->color = kBlack;

		// while (current->color == kRed && current->parent != NULL)
		// {
		// 	bool isRight = (current == current->parent->right);
		// 	base_ptr uncle = isRight ? current->parent->left : current->parent->right;

		// 	if (uncle == NULL)
		// 	{
		// 		current->color = kBlack;
		// 		current->parent->color = kRed;
		// 		if (uncle == current->parent->right)
		// 		{
		// 			_rightRotate(current->parent);
		// 		}
		// 		else
		// 		{
		// 			_leftRotate(current->parent);
		// 		}
		// 		break;
		// 	}
		// 	else if (uncle->color == kRed)
		// 	{
		// 		current->color = kBlack;
		// 		uncle->color = kBlack;
		// 		current->parent->color = kRed;
		// 		current = current->parent;
		// 	}
		// 	else
		// 	{
		// 		current->color = kBlack;
		// 		current->parent->color = kRed;

		// 		if (isRight)
		// 		{
		// 			if (newNode == current->left)
		// 			{
		// 				_rightRotate(current);
		// 				current = newNode;
		// 			}
		// 			_leftRotate(current->parent);
		// 		}
		// 		else
		// 		{
		// 			if (newNode == current->right)
		// 			{
		// 				_leftRotate(current);
		// 				current = newNode;
		// 			}
		// 			_rightRotate(current->parent);
		// 		}
		// 	}
			// _getRoot()->color = kBlack;
		// }
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

		if (x->parent == root)
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
	
		if (x->parent == root)
			root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x; // put x on y’s left
		x->parent = y;
	}

public:
	bool __rb_verify() const
	{
		if (_m_impl._nodeCount == 0 || begin() == end())
			return _m_impl._nodeCount == 0 && begin() == end()
				&& _m_impl._header.left == _m_end() && _m_impl._header.right == _m_end();

		size_t len = _rb_tree_black_count(_m_leftmost(), _m_root());
		const_iterator it = begin();
		while (it != end())
		{
			const_link_type x = static_cast<const_link_type>(it._node);
			const_link_type left = _s_left(x);
			const_link_type right = _s_right(x);

			// check if adjacent nodes are not red when parent is already red
			if (x->color == kRed)
			{
				if (left && left->color == kRed)
					return false;
				if (right && right->color == kRed)
					return false;
			}
			// check parent and child order is okay
			if (left && this->_m_impl._m_key_compare(_s_key(x), _s_key(left)))
				return false;
			if (right && this->_m_impl._m_key_compare(_s_key(right), _s_key(x)))
				return false;

			// check if number of black nodes are equal no matter the node we're in
			if (!left && !right && _rb_tree_black_count(x, _m_root()) != len)
				return false;
			++it;
		}
		// check if leftmost and rightmost correspond to min/max of root node
		if (_m_leftmost() != node_base::_s_minimum(_m_root()) )
				return false;
		if (_m_rightmost() != node_base::_s_maximum(_m_root()) )
				return false;
		return true;
	}

}; /* class rbTree */


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






template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc >
typename	rbTree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::node_allocator 
			rbTree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::nodeAlloc;

} /* namespace ft */
#endif /* RB_TREE */







	// int _compare(const T &one, const T &two)
	// {
	// 	if (one < two)
	// 		return -1;
	// 	if (one > two)
	// 		return 1;
	// 	return 0;
	// }
