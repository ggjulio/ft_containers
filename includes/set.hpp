#ifndef SET_HPP
#define SET_HPP

#include <set>

#include "rb_tree.hpp"

namespace ft 
{

template < class _T,                        // set::key_type/value_type
           class _Compare = std::less<_T>,        // set::key_compare/value_compare
           class _Alloc = std::allocator<_T>      // set::allocator_type
           >
class set
{
public:
	typedef _T					key_type;
	typedef _T					value_type;
	typedef _Compare			key_compare;
	typedef _Compare			value_compare;
	typedef _Alloc				allocator_type;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;

private:
	typedef rbTree<value_type, value_compare, allocator_type> __tree;

	__tree _tree;
public:
	typedef typename __tree::pointer						pointer;
	typedef typename __tree::const_pointer					const_pointer;
	typedef typename __tree::size_type						size_type;
	typedef typename __tree::difference_type				difference_type ;
	typedef typename __tree::const_iterator 				iterator;
	typedef typename __tree::const_iterator 				const_iterator;
	// typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	set(const value_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	: _tree(comp, alloc) {}

	template <class InputIterator>
	set(InputIterator first, InputIterator last,
		const value_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	: _tree(comp, alloc)
	{
		insert(first, last);
	}

	set(const set& other): _tree(other._tree) {}
};

} /* namespace ft */

#endif /* SET_HPP */