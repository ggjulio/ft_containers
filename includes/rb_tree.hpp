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

namespace ft
{

enum color { kBlack = false,	kRed = true, };



struct node_base
{
	typedef node_base		*base_ptr;
	typedef const node_base *const_base_ptr;

	enum color color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	base_ptr minimum(base_ptr iterator)
	{
		while (iterator->left)
			iterator = iterator->left;
		return iterator;
	}
	base_ptr maximum(base_ptr iterator)
	{
		while (iterator->right)
			iterator = iterator->right;
		return iterator;
	}
	const_base_ptr minimum(const_base_ptr iterator)
	{
		while (iterator->left)
			iterator = iterator->left;
		return iterator;
	}
	const_base_ptr maximum(const_base_ptr iterator)
	{
		while (iterator->right)
			iterator = iterator->right;
		return iterator;
	}
}; /* struct node_base */

template <class T>
struct node : public node_base
{
	typedef node<T> *link_type;
	T data;

	T* dataPtr()		{return &data;}
	const T* dataPtr() const 	{return &data;}
}; /* struct node */


template <typename T>
struct RbTree_iterator
{
	typedef T value_type;
	typedef T &reference;
	typedef T *pointer;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

	typedef RbTree_iterator<T> Self;
	typedef node<T> *link_type;

	RbTree_iterator() : _node() {}

	RbTree_iterator(link_type ptr) throw() : _node(ptr) {}

	reference operator*() const throw()
	{
		return *static_cast<link_type>(_node)->dataPtr();
	}

	pointer operator->() const throw()
	{
		return static_cast<link_type>(_node)->getDataPtr();
	}

	Self &operator++() throw()
	{
		_node = _increment(_node);
		return *this;
	}

	Self operator++(int) throw()
	{
		Self tmp = *this;
		_node = _increment(_node);
		return tmp;
	}

	Self &operator--() throw()
	{
		_node = _decrement(_node);
		return *this;
	}

	Self operator--(int) throw()
	{
		Self __tmp = *this;
		_node = _decrement(_node);
		return __tmp;
	}

	friend bool operator==(const Self &x, const Self &y) throw()
	{
		return x._node == y._node;
	}
	friend bool operator!=(const Self &x, const Self &y) throw()
	{
		return !(x._node == y._node);
	}

	link_type _node;

private:
	link_type _increment(link_type x)
	{
		if (x->right != 0)
		{
			x = x->right;
			while (x->left != 0)
				x = x->left;
		}
		else
		{
			link_type y = x->parent;
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

	link_type _decrement(link_type x)
	{
		if (x->_M_color == kRed && x->parent->parent == x)
			x = x->right;
		else if (x->left != 0)
		{
			link_type y = x->left;
			while (y->right != 0)
				y = y->right;
			x = y;
		}
		else
		{
			link_type y = x->parent;
			while (x == y->left)
			{
				x = y;
				y = y->parent;
			}
			x = y;
		}
		return x;
	}

}; /* struct RbTree_iterator */

struct rb_tree_header
{
	node_base header;
	size_t	nodeCount;

	rb_tree_header() throw()
	{
		header.color = kRed;
		reset();
	}

	void reset() throw()
	{
		header.parent = NULL;
		header.left = &header;
		header.right = &header;
		nodeCount = 0;
	}

};

// template<typename _Key, typename _Val, typename _KeyOfValue,
//        typename _Compare, typename _Alloc = ::std::allocator<_Val> >
template<typename _Key, typename _Val,
       typename _Compare, typename _Alloc = std::allocator<_Val> >
class rbTree : public rb_tree_header
{
public:
	typedef _Val 				value_type;
	typedef _Val 				value_compare;
	typedef _Alloc				allocator_type;
private:
    typedef std::allocator_traits<allocator_type>      _alloc_traits;
public:
	typedef _Key 									key_type;

	typedef typename _alloc_traits::pointer			*pointer;
	typedef typename _alloc_traits::const_pointer	*const_pointer;
	typedef typename _alloc_traits::size_type		size_type;
	typedef typename _alloc_traits::difference_type	difference_type;

	typedef value_type								&reference;
	typedef const value_type						&const_reference;
	
	typedef RbTree_iterator<value_type> iterator;
	// typedef RbTree_const_iterator<value_type> const_iterator;

protected:
	typedef node_base			*base_ptr;
	typedef const node_base 	*const_base_ptr;

	typedef node<_Val>			*link_type;
	typedef const node<_Val>	*const_link_type;

	typedef typename _Alloc::template rebind<link_type>				node_allocator;
    typedef std::allocator_traits<node_allocator>      node_traits;

public:
	static node_allocator nodeAlloc;

	rbTree() {}
	~rbTree() {}

	iterator begin()	{ return header.left;}
	iterator end()		{ return header;}




	allocator_type get_allocator() const throw(){ return allocator_type();}

	void insert(const value_type& v)
	{
		(void)v;
		// _insert(root(), header, v);
	}

protected:
	base_ptr root()			{ return header.parent;}
	const_base_ptr root()const	{ return header.parent;}

	void _insert(base_ptr x, base_ptr y, const value_type& v)
	{
		++nodeCount;
		(void)x;
		(void)y;
		
		link_type toInsert = nodeAlloc.allocate(1);
		nodeAlloc.allocate(toInsert, v);
		
		if (root() == NULL)
		{
			header.parent = toInsert;
			toInsert->color = kRed;
			return;
		}

		// // find the position of new node
		// base_ptr current = root();
		// while (current->left != NULL && current->right != NULL)
		// 	current = (_compare(obj, current->data) == -1) ? current->left : current->right;

		// // link it with the parent
		// newNode->parent = current;
		// if (_compare(obj, current->data) == -1)
		// 	current->left = newNode;
		// else
		// 	current->right = newNode;

		// _rebalance(current, newNode);
	}

	// void _rebalance(node<T> *current, node<T> *newNode)
	// {
	// 	while (current->color == kRed && current->parent != NULL)
	// 	{
	// 		bool isRight = (current == current->parent->right);
	// 		base_ptr uncle = isRight ? current->parent->left : current->parent->right;

	// 		if (uncle == NULL)
	// 		{
	// 			current->color = kBlack;
	// 			current->parent->color = kRed;
	// 			if (uncle == current->parent->right)
	// 			{
	// 				_rightRotate(current->parent);
	// 			}
	// 			else
	// 			{
	// 				_leftRotate(current->parent);
	// 			}
	// 			break;
	// 		}
	// 		else if (uncle->color == kRed)
	// 		{
	// 			current->color = kBlack;
	// 			uncle->color = kBlack;
	// 			current->parent->color = kRed;
	// 			current = current->parent;
	// 		}
	// 		else
	// 		{
	// 			current->color = kBlack;
	// 			current->parent->color = kRed;

	// 			if (isRight)
	// 			{
	// 				if (newNode == current->left)
	// 				{
	// 					_rightRotate(current);
	// 					current = newNode;
	// 				}
	// 				_leftRotate(current->parent);
	// 			}
	// 			else
	// 			{
	// 				if (newNode == current->right)
	// 				{
	// 					_leftRotate(current);
	// 					current = newNode;
	// 				}
	// 				_rightRotate(current->parent);
	// 			}
	// 		}
	// 		_getRoot()->color = kBlack;
	// 	}
	// }

	/*      y   right rotate     x
	/      / \  ------------>   / \ 
	/     x	  c                 a   y 
	/    / \     left rotate       / \ 
	/   a   b   <------------     b   c
	*/
	// void _leftRotate(node<T> *node)
	// {
	// 	assert(node->right != NULL);
	// 	ft::node<T> *tmp = node->right;

	// 	// update the two nodes
	// 	node->right = tmp->left;
	// 	if (tmp->left != NULL)
	// 		tmp->left->parent = node;
	// 	tmp->left = node;
	// 	tmp->parent = node->parent;
	// 	node->parent = tmp;

	// 	// update the parent
	// 	if (_root() == node)
	// 	{
	// 		header.parent = tmp;
	// 		return;
	// 	}
	// 	if (tmp->parent->left == node)
	// 		tmp->parent->left = tmp;
	// 	else
	// 		tmp->parent->right = tmp;
	// }

	// void _rightRotate(node<T> *node)
	// {
	// 	assert( node->left != nullptr);
	// 	// ft::node<T> *tmp = node->left;
	// 	base_ptr tmp = node->left;

	// 	// update the two nodes
	// 	node->left = tmp->right;
	// 	if (tmp->right != NULL)
	// 		tmp->right->parent = node;
	// 	tmp->right = node;
	// 	tmp->parent = node->parent;
	// 	node->parent = tmp;

	// 	// update the parent
	// 	if (_root == node)
	// 	{
	// 		_root = tmp;
	// 		return;
	// 	}
	// 	if (tmp->parent->left == node)
	// 		tmp->parent->left = tmp;
	// 	else
	// 		tmp->parent->right = tmp;
	// }


}; /* class rbTree */


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
