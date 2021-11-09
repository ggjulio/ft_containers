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
#include <iomanip>
#include <string>

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

void 				_leftRotate(node_base *x, node_base*& root);
void				_rightRotate(node_base *x, node_base*& root);

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
	pointer operator->() const throw()	{ return static_cast<link_type>(_node)->_m_dataPtr(); }

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
	pointer operator->() const throw()	{ return static_cast<link_type>(_node)->_m_dataPtr(); }

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

	template <typename __Compare>
	struct rbTree_impl
		: public rb_tree_header,
		  public rb_tree_key_compare<__Compare>
	{
		rb_tree_key_compare<_Compare> comp;

		rbTree_impl() {}
		rbTree_impl(const __Compare& c): rb_tree_key_compare<__Compare>(c) {}

		~rbTree_impl() {}

	};
	rbTree_impl<_Compare> _m_impl;

	static node_allocator _nodeAlloc;
public:

	rbTree() {}
	rbTree(const _Compare& comp, const allocator_type& alloc = allocator_type())
		: _m_impl(comp) { (void)alloc;}
	rbTree(const rbTree& other)
		: _m_impl(other._m_impl)
	{
		// do deep copy
	}
	~rbTree() {
		_m_erase(_m_begin());
	}

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
	size_type		max_size() const throw()	{ return _nodeAlloc.max_size(); }

	allocator_type get_allocator() const throw(){ return allocator_type();}

	pair<iterator, bool> insert_unique(const value_type& v)
	{
		return _m_insert_unique(v);
	}

	template <typename _InputIterator>
	void insert_range_unique(_InputIterator first, _InputIterator last)
	{
		while( first != last)
		{
			_m_insert_unique(*first);
			++first;
		}
	}
	void erase(iterator position)
	{
		_m_erase_and_fix(position);
	}
	void erase(iterator first, iterator last) {(void)first;(void)last;}
	void erase_unique(const _Key& k) {(void)k;}

	void swap(rbTree& other)	{(void)other;}
	void clear() {
		_m_erase(_m_begin());
		_m_impl.reset();
	}

	_Compare	key_comp() const { return _m_impl._m_key_compare;}

	iterator		find(const _Key& k)	{
		iterator res = _m_lower_bound(_m_begin(), _m_end(), k);
		return _m_impl._m_key_compare(k, _s_key(res._node)) ? end() : res;
	}
	const_iterator	find(const _Key& k) const			{
		const_iterator res = _m_lower_bound(_m_begin(), _m_end(), k);
		return _m_impl._m_key_compare(k, _s_key(res._node)) ? end() : res;
	}
	iterator		lower_bound(const _Key& k)		 	{ return _m_lower_bound(_m_begin(), _m_end(), k); }
	const_iterator	lower_bound(const _Key& k)const		{ return _m_lower_bound(_m_begin(), _m_end(), k); }
	iterator		upper_bound(const _Key& k)		 	{ return _m_upper_bound(_m_begin(), _m_end(), k); }
	const_iterator	upper_bound(const _Key& k)const		{ return _m_upper_bound(_m_begin(), _m_end(), k); }

	pair<iterator,iterator>    equal_range(const _Key& k)
		{ return make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }
	pair<const_iterator,const_iterator>    equal_range(const _Key& k) const
		{ return make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }

private:
	base_ptr&				_m_root()					throw() { return _m_impl._header.parent;}
	const_base_ptr			_m_root()const				throw() { return _m_impl._header.parent;}
	
	base_ptr&				_m_leftmost()				throw() { return _m_impl._header.left;}
	const_base_ptr			_m_leftmost()const			throw() { return _m_impl._header.left;}
	
	base_ptr&				_m_rightmost()				throw() { return _m_impl._header.right;}
	const_base_ptr			_m_rightmost()const			throw() { return _m_impl._header.right;}
	
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

	pair<iterator, bool> _m_insert_unique(const value_type& v)
	{
		pair<base_ptr, base_ptr> result = _m_get_insert_pos(v);

		if (result.second)
			return pair<iterator, bool>(
						_m_insert_(result.first, result.second, v),
						true);
		return pair<iterator, bool>(result.first, false);
	}

	iterator _m_insert_(base_ptr x, base_ptr parent, const value_type& v)
	{
		(void)x;
		(void)parent;
		link_type z = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(z, v);
		
		_m_tree_insert_and_rebalance(z, parent);

		++_m_impl._nodeCount;
		return z;
	}

	// z is the node to insert
	void _m_tree_insert_and_rebalance(base_ptr z, base_ptr parent)
	{
		z->parent = parent;
		z->left = 0;
		z->right = 0;
		z->color = kRed;

		bool insertLeft = 
				parent == _m_end()
				|| !_m_impl._m_key_compare(_s_key(parent), _s_key(z));
		// The first inserted node is always left.
		// condition to maintain leftmost, rightmost and root links
		if (insertLeft)
		{
			parent->left = z;
			if (parent == &_m_impl._header)
			{
				_m_impl._header.parent = z;
				_m_impl._header.right = z;
			}
			else if (parent == _m_impl._header.left)
				_m_impl._header.left = z;
		}
		else
		{
			parent->right = z;
			if (parent == _m_impl._header.right)
				_m_impl._header.right = z;
		}


		// rebalance the tree
		while (z != _m_root() && z->parent->color == kRed)
		{
			if (z->parent == z->parent->parent->left)
			{
				base_ptr y = z->parent->parent->right;
				if (y && y->color == kRed)
				{
					z->parent->color = kBlack;
					y->color = kBlack;
					z->parent->parent->color = kRed;
					z = z->parent->parent;
				}
				else 
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						_leftRotate(z, _m_root());
					}
					z->parent->color = kBlack;
					z->parent->parent->color = kRed;
					_rightRotate(z->parent->parent, _m_root());
				}
			}
			else
			{
				base_ptr y = z->parent->parent->left;
				if (y && y->color == kRed)
				{
					z->parent->color = kBlack;
					y->color = kBlack;
					z->parent->parent->color = kRed;
					z = z->parent->parent;
				}
				else 
				{
					if (z == z->parent->left)
					{
						z = z->parent;
						_rightRotate(z, _m_root());
					}
					z->parent->color = kBlack;
					z->parent->parent->color = kRed;
					_leftRotate(z->parent->parent, _m_root());
				}
			}
		}
		_m_root()->color = kBlack;
	}

	// erase node n and his childs without rebalance.
	void _m_erase(link_type n)
	{
		while (n)
		{
			_m_erase(_s_right(n));
			link_type x = _s_left(n);
			_nodeAlloc.destroy(n);
			_nodeAlloc.deallocate(n, 1);
			n = x;
		}
	}

	void _m_transplant(base_ptr u, base_ptr v, node_base header)
	{
		if (u->parent == header.parent)
			header.parent = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	void _m_erase_and_fix(iterator position)
	{
		base_ptr z = position._node;
		base_ptr y = z;
		base_ptr x = NULL;

		enum color yPrevColor = y->color;
		if (z->left == NULL)
		{
			x = z->right;
			_m_transplant(z, z->right, _m_impl._header);
		}
		else if (z->right == NULL)
		{
			x = z->left;
			_m_transplant(z, z->left, _m_impl._header);
		}
		else
		{
			y = _s_minimum(z->right);
			yPrevColor = y->color;
			x = y->right;
			if (y->parent != z)
			{
				x->parent = y;
			}
			else
			{
				_m_transplant(y, y->right, _m_impl._header);
				y->right = z->right;
				y->right->parent = y;
			}
			_m_transplant(z, y, _m_impl._header);
			y->left = z->left;
			y->left->parent = y;
			y->color = x->color;
		}
		// if black, fix eventual violation of rb tree rules
		if (yPrevColor == kBlack)
		{
			while (x != _m_root() && x->color == Black)
			{
				if (x == x->parent->left)
				{
					auto w = x->parent->right;
					if (w->color == kRed)
					{
						w->color = kBlack;
						x->parent->color = kRed;
						_leftRotate(x->parent, _m_root());
						w = x->parent->right;
					}
					if (w->left->color == kBlack and w->right->color == kBlack)
					{
						w->color = kRed;
						x = x->parent;
					}
					else if (w->right->color == kBlack)
					{
						w->left->color = kBlack
					}
				}
				else
				{
					
				}
				
			}
		}
	}


	iterator _m_lower_bound(link_type x, base_ptr y, const _Key& k) 
	{
		while (x != NULL)
		{
			if (_m_impl._m_key_compare(_s_key(x), k))
				x = _s_right(x);
			else
			{
				y = x;
				x = _s_left(x);
			}
		}
		return iterator(y);
	}

	const_iterator _m_lower_bound(link_type x, base_ptr y, const _Key& k) const
	{
		while (x != NULL)
		{
			if (_m_impl._m_key_compare(_s_key(x), k))
				x = _s_right(x);
			else
				y = x, x = _s_left(x);
		}
		return const_iterator(y);
	}
	
	iterator _m_upper_bound(link_type x, base_ptr y, const _Key& k) 
	{
		while (x != NULL)
		{
			if (!_m_impl._m_key_compare(k, _s_key(x)))
				x = _s_right(x);
			else
			{
				y = x;
				x = _s_left(x);
			}
		}
		return iterator(y);
	}

	const_iterator _m_upper_bound(link_type x, base_ptr y, const _Key& k) const
	{
		while (x != NULL)
		{
			if (!_m_impl._m_key_compare(k, _s_key(x)))
				x = _s_right(x);
			else
				y = x, x = _s_left(x);
		}
		return const_iterator(y);
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

	void __rb_tree_print()
	{
		__rb_tree_print(static_cast<link_type>(_m_root()), NULL, false);
	}

private:

	struct Trunk
	{
		Trunk *prev;
		std::string str;
	
		Trunk(Trunk *prev, std::string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};

	void showTrunks(Trunk *p)
	{
		if (p == NULL) {
			return;
		}
	
		showTrunks(p->prev);
		std::cout << p->str;
	}

	void __rb_tree_print(link_type root, Trunk *prev, bool isLeft)
	{
		if (root == NULL) {
			return;
		}
	
		std::string prev_str = "    ";
		Trunk *trunk = new Trunk(prev, prev_str);
	
		__rb_tree_print(static_cast<link_type>(root->right), trunk, true);
	
		if (!prev) {
			trunk->str = "———";
		}
		else if (isLeft)
		{
			trunk->str = ".———";
			prev_str = "   |";
		}
		else {
			trunk->str = "`———";
			prev->str = prev_str;
		}
	
		showTrunks(trunk);
		std::cout << root->data << std::endl;
	
		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = "   |";
	
		__rb_tree_print(static_cast<link_type>(root->left), trunk, false);
	}
}; /* class rbTree */

size_t _rb_tree_black_count(const node_base *node, const node_base *root) throw();

template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc >
typename	rbTree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::node_allocator 
			rbTree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_nodeAlloc;


} /* namespace ft */

#endif /* RB_TREE */
